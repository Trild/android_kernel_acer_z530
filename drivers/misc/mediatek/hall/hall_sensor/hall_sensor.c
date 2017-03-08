#include <linux/module.h>
#include <linux/init.h>
#include <linux/platform_device.h>
#include <linux/irqreturn.h>
#include <linux/workqueue.h>
#include <linux/interrupt.h>
#include <mach/mt_gpio.h>
#include <mach/eint.h>
#include <cust_eint.h>
#include <mach/mt_typedefs.h>
#include <mach/mt_boot.h>
#include <linux/delay.h>
#include <linux/slab.h>
#include "hall_sensor.h"
#include <linux/switch.h>

extern void mt_eint_unmask(unsigned int eint_num);
extern void mt_eint_mask(unsigned int eint_num);
extern void mt_eint_registration(unsigned int eint_num, unsigned int flag, void (EINT_FUNC_PTR)(void), unsigned int is_auto_umask);

static DEFINE_MUTEX(hall_eint_irq_sync_mutex);

static int hall_sync_flag = 0;
static int debug_enable = 1;
static bool hall_suspend = false;

struct bu52054_hall *hall;
static struct platform_driver bu52054_platform_driver;
struct input_dev *hall_input_dev = NULL;
static int old_INT_state = 1;

static ssize_t show_hall_value(struct device_driver *device, char *buf)
{
	int hall_v = -1;

	hall_v = mt_get_gpio_in(GPIO_HALL_1_PIN);

	return snprintf(buf, PAGE_SIZE, "%d\n",  hall_v);
}

static DRIVER_ATTR(hall_output, S_IWUSR | S_IRUGO, show_hall_value,  NULL);
/*----------------------------------------------------------------------------*/
static struct driver_attribute *bu52054_attr_list[] = {
	&driver_attr_hall_output,     /*hall output pin information*/
};
/*----------------------------------------------------------------------------*/

static int bu52054_create_attr(struct device_driver *driver)
{
	int idx, err = 0;
	int num = (int)(sizeof(bu52054_attr_list)/sizeof(bu52054_attr_list[0]));

	if (driver == NULL)
	{
		return -EINVAL;
	}

	for(idx = 0; idx < num; idx++)
	{
		if(0 != (err = driver_create_file(driver, bu52054_attr_list[idx]))) {
			HALL_DEBUG(" (%s) = %d\n", bu52054_attr_list[idx]->attr.name, err);
			break;
		}
	}

	return err;
}

static int bu52054_delete_attr(struct device_driver *driver)
{
	int idx ,err = 0;
	int num = (int)(sizeof(bu52054_attr_list)/sizeof(bu52054_attr_list[0]));

	if(driver == NULL)
		return -EINVAL;

	for(idx = 0; idx < num; idx++) {
		driver_remove_file(driver, bu52054_attr_list[idx]);
	}

	return err;
}

static void bu52054_work_cbf(struct work_struct *work)
{
	hall->state = mt_get_gpio_in(GPIO_HALL_1_PIN);
	HALL_DEBUG(" hall_state:%d old_state:%d\n", hall->state, old_INT_state);

	if (hall->state != old_INT_state) {
		if(hall->state == 0 && old_INT_state == 1 ) {
			mt_eint_set_polarity(CUST_EINT_HALL_1_NUM,  1);
			/*To Do - Send power key event depends on customer's requirement */
			//input_report_key(hall_input_dev, KEY_POWER, 0);
			//input_sync(hall_input_dev);
			HALL_DEBUG(" hall_out  (1 -> 0 ) \n");
		} else if (hall->state == 1 && old_INT_state == 0 ) {
			mt_eint_set_polarity(CUST_EINT_HALL_1_NUM,  0);
			/*To Do - Send power key event depends on customer's requirement */
			//input_report_key(hall_input_dev, KEY_POWER, 1);
			//input_sync(hall_input_dev);
			HALL_DEBUG(" hall_out  (0 -> 1) \n");
		} else
			HALL_DEBUG("error -  hall_state:%d old_state:%d\n", hall->state, old_INT_state);
	}

	/* Lock process until flag was updated */
	mutex_lock(&hall_eint_irq_sync_mutex);
	old_INT_state = hall->state;
        switch_set_state(&hall->sdev,hall->state);
	hall_sync_flag = 1;
	mutex_unlock(&hall_eint_irq_sync_mutex);

	if(1 == hall_sync_flag) {
		hall_sync_flag = 0;
		/* Enable eint handler */
		mt_eint_unmask(CUST_EINT_HALL_1_NUM);
	}
}

static void bu52054_eint_handler(unsigned long data)
{
	/* Disable eint handler  */
	mt_eint_mask(CUST_EINT_HALL_1_NUM);
	schedule_delayed_work(&hall->bu52054_work, 0);
}

static int bu52054_gpio_init(void)
{
	HALL_DEBUG("enter\n");

	/*configure to GPIO function, external interrupt*/
	mt_set_gpio_mode(GPIO_HALL_1_PIN, GPIO_HALL_1_PIN_M_EINT);
	mt_set_gpio_dir(GPIO_HALL_1_PIN, GPIO_DIR_IN);

	/* To enable GPIO PULL. */
	mt_set_gpio_pull_enable(GPIO_HALL_1_PIN, GPIO_PULL_ENABLE);
	mt_set_gpio_pull_select(GPIO_HALL_1_PIN, GPIO_PULL_UP);

	/* Set eint trigger type to Level and set Low_active */
	mt_eint_set_sens(CUST_EINT_HALL_1_NUM, MT_LEVEL_SENSITIVE);
	mt_eint_registration(CUST_EINT_HALL_1_NUM, EINTF_TRIGGER_LOW,
			bu52054_eint_handler, 0);

	/* Enable eint handler */
	mt_eint_unmask(CUST_EINT_HALL_1_NUM);

	return 0;
}

static int bu52054_setup_input_device(struct platform_device *pdev)
{
        int err;

        hall_input_dev = input_allocate_device();
        if (!hall_input_dev) {
		HALL_DEBUG(" failed\n");
		return -ENOMEM;
        }

	__set_bit(EV_KEY, hall_input_dev->evbit);
	__set_bit(KEY_POWER, hall_input_dev->keybit);

	hall_input_dev->name = pdev->name;
	hall_input_dev->id.bustype = BUS_HOST;
	hall_input_dev->dev.parent = &pdev->dev;

        err = input_register_device(hall_input_dev);
        if (err) {
                HALL_DEBUG("err = %d\n", err);
                input_free_device(hall_input_dev);
                return err;
        }

        return 0;
}

static ssize_t show_hall_value_switch(struct device *dev,struct device_attribute *attr, char *buf)
{
        int state;

        state = switch_get_state(&hall->sdev);
        return sprintf(buf, "%d\n", state);
}


static DEVICE_ATTR(hall_value, 0664, show_hall_value_switch,NULL);

static int bu52054_probe(struct platform_device *pdev)
{
	int  ret = 0;

	HALL_DEBUG( "enter\n");

	/* Allocate driver structure */
	hall =  kzalloc(sizeof(*hall), GFP_KERNEL);

	if (!hall) {
		HALL_DEBUG("Out of memory\n");
		ret = -ENOMEM;
		goto no_memory;
	}

	/* Initialize GPIO */
	bu52054_gpio_init();

        hall->sdev.name = "hall_gpio";
	/* Initialize work*/
	INIT_DELAYED_WORK(&hall->bu52054_work, bu52054_work_cbf);

	/* Initialize input event */
	ret = bu52054_setup_input_device(pdev);
	if(ret)
		goto no_memory;
        ret = switch_dev_register(&hall->sdev);
        if (ret < 0)
                goto no_memory;

	/* Create sysfs */
	if(0 != (ret = bu52054_create_attr(&bu52054_platform_driver.driver))) {
		HALL_DEBUG(" err = %d\n", ret);
		goto no_memory;
	}
        ret = device_create_file(&(pdev->dev), &dev_attr_hall_value);
        if (ret) {
                HALL_DEBUG("sensor_probe: driver_create_file fail!!! \n");
        }

	platform_set_drvdata(pdev, hall);

	HALL_DEBUG("done\n");

	return 0;

no_memory:
	HALL_DEBUG("exit with %d\n", ret);

	return ret;
}

static int bu52054_remove(struct platform_device *pdev)
{
	int err;
	struct bu52054_hall *hall = platform_get_drvdata(pdev);

	/* Delete sysfs */
	if(0 != (err = bu52054_delete_attr(&bu52054_platform_driver.driver))) {
		HALL_DEBUG("delete_attr fail: %d\n", err);
	}

	/* Free input device */
	input_free_device(hall_input_dev);

	/* Release driver struct */
	devres_free(hall);

	return 0;
}

static struct platform_driver bu52054_platform_driver = {
	.probe      = bu52054_probe,
	.remove     = bu52054_remove,
	.driver     = {
		.name  = BU52054_NAME,
		.owner = THIS_MODULE,
	}
};

static struct platform_device bu52054_device = {
    .name = BU52054_NAME,
    .id = 0,
    .dev = {}
};

static void hall_early_suspend(struct early_suspend *h)
{
	hall_suspend = true;
	HALL_DEBUG(" status(%d)\n", hall_suspend);
}

static void hall_early_resume(struct early_suspend *h)
{
	hall_suspend = false;
	HALL_DEBUG(" status (%d)\n", hall_suspend);
}

static struct early_suspend hall_early_suspend_desc = {
	.level = EARLY_SUSPEND_LEVEL_BLANK_SCREEN + 1,
	.suspend = hall_early_suspend,
	.resume = hall_early_resume,
};

static int bu52054_init(void)
{
	int ret;

	if(platform_device_register(&bu52054_device)){
                HALL_DEBUG("failed to register hall_device\n");
                return -ENODEV;
        }

	ret = platform_driver_register(&bu52054_platform_driver);
	if (ret) {
		HALL_DEBUG("platform_driver_register error:(%d)\n", ret);
		return ret;
	}

	register_early_suspend(&hall_early_suspend_desc);
	HALL_DEBUG(" done!\n");

	return 0;
}

static void __exit bu52054_exit(void)
{
	platform_driver_unregister(&bu52054_platform_driver);
}

late_initcall(bu52054_init);
module_exit(bu52054_exit);

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Hall sensor BU52054 driver");
MODULE_AUTHOR("Livet_Chen@compal.com");
