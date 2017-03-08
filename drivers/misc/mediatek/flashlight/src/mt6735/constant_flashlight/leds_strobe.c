#include <linux/kernel.h> //constant xx
#include <linux/module.h>
#include <linux/init.h>
#include <linux/types.h>
#include <linux/wait.h>
#include <linux/slab.h>
#include <linux/fs.h>
#include <linux/sched.h>
#include <linux/poll.h>
#include <linux/device.h>
#include <linux/interrupt.h>
#include <linux/delay.h>
#include <linux/platform_device.h>
#include <linux/cdev.h>
#include <linux/errno.h>
#include <linux/time.h>
#include "kd_flashlight.h"
#include <asm/io.h>
#include <asm/uaccess.h>
#include "kd_camera_hw.h"
#include <cust_gpio_usage.h>
#include <linux/hrtimer.h>
#include <linux/ktime.h>
#include <linux/xlog.h>
#include <linux/version.h>

#if (LINUX_VERSION_CODE >= KERNEL_VERSION(2,6,37))
#include <linux/mutex.h>
#else
#if LINUX_VERSION_CODE >= KERNEL_VERSION(2,6,27)
#include <linux/semaphore.h>
#else
#include <asm/semaphore.h>
#endif
#endif

#include <linux/spinlock.h>

/******************************************************************************
 * Debug configuration
******************************************************************************/
// availible parameter
// ANDROID_LOG_ASSERT
// ANDROID_LOG_ERROR
// ANDROID_LOG_WARNING
// ANDROID_LOG_INFO
// ANDROID_LOG_DEBUG
// ANDROID_LOG_VERBOSE
#define TAG_NAME "leds_strobe.c"
#define PK_DBG_NONE(fmt, arg...)    do {} while (0)
#define PK_DBG_FUNC(fmt, arg...)    xlog_printk(ANDROID_LOG_DEBUG  , TAG_NAME, KERN_INFO  "%s: " fmt, __FUNCTION__ ,##arg)
#define PK_WARN(fmt, arg...)        xlog_printk(ANDROID_LOG_WARNING, TAG_NAME, KERN_WARNING  "%s: " fmt, __FUNCTION__ ,##arg)
#define PK_NOTICE(fmt, arg...)      xlog_printk(ANDROID_LOG_DEBUG  , TAG_NAME, KERN_NOTICE  "%s: " fmt, __FUNCTION__ ,##arg)
#define PK_INFO(fmt, arg...)        xlog_printk(ANDROID_LOG_INFO   , TAG_NAME, KERN_INFO  "%s: " fmt, __FUNCTION__ ,##arg)
#define PK_TRC_FUNC(f)              xlog_printk(ANDROID_LOG_DEBUG  , TAG_NAME,  "<%s>\n", __FUNCTION__);
#define PK_TRC_VERBOSE(fmt, arg...) xlog_printk(ANDROID_LOG_VERBOSE, TAG_NAME,  fmt, ##arg)
#define PK_ERROR(fmt, arg...)       xlog_printk(ANDROID_LOG_ERROR  , TAG_NAME, KERN_ERR "%s: " fmt, __FUNCTION__ ,##arg)


#define DEBUG_LEDS_STROBE
#ifdef  DEBUG_LEDS_STROBE
	#define PK_DBG PK_DBG_FUNC
	#define PK_VER PK_TRC_VERBOSE
	#define PK_ERR PK_ERROR
#else
	#define PK_DBG(a,...)
	#define PK_VER(a,...)
	#define PK_ERR(a,...)
#endif

/******************************************************************************
 * local variables
******************************************************************************/

static DEFINE_SPINLOCK(g_strobeSMPLock); /* cotta-- SMP proection */


static u32 strobe_Res = 0;
static u32 strobe_Timeus = 0;
static BOOL g_strobe_On = 0;

static int g_duty=-1;
static int g_timeOutTimeMs=0;

#if (LINUX_VERSION_CODE >= KERNEL_VERSION(2,6,37))
static DEFINE_MUTEX(g_strobeSem);
#else
static DECLARE_MUTEX(g_strobeSem);
#endif

static DEFINE_SPINLOCK(strobe_drv_lock);

#define STROBE_DEVICE_ID 0x60


static struct work_struct workTimeOut;

/*****************************************************************************
Functions
*****************************************************************************/
#define GPIO_CTRL GPIO_CAMERA_FLASH_EN_PIN
//#define GPIO_TX GPIO_FLASH_SEL
#define GPIO_STROBE GPIO_CAMERA_FLASH_MODE_PIN


    /*CAMERA-FLASH-EN */


extern int iWriteRegI2C(u8 *a_pSendData , u16 a_sizeSendData, u16 i2cId);
extern int iReadRegI2C(u8 *a_pSendData , u16 a_sizeSendData, u8 * a_pRecvData, u16 a_sizeRecvData, u16 i2cId);
static void work_timeOutFunc(struct work_struct *data);

#define SEND_LOW() do {\
	mt_set_gpio_out(GPIO_CTRL,GPIO_OUT_ZERO); \
		udelay(80);\
	mt_set_gpio_out(GPIO_CTRL,GPIO_OUT_ONE); \
		udelay(40);\
} while(0)

#define SEND_HIGH() do {\
	mt_set_gpio_out(GPIO_CTRL,GPIO_OUT_ZERO); \
		udelay(40);\
	mt_set_gpio_out(GPIO_CTRL,GPIO_OUT_ONE); \
		udelay(80);\
} while(0)

void FL_sendData(const unsigned char data)
{
    unsigned long int_flags;
    struct timeval tv1,tv2;
    PK_DBG(" Start: data=%2X\n", data);
    do_gettimeofday(&tv1);
    spin_lock_irqsave(&strobe_drv_lock, int_flags);
    mt_set_gpio_out(GPIO_CTRL,GPIO_OUT_ONE);
    udelay(30); // TDS: data start. typical 10 us
    // fill the data.
    if (data&0x80) SEND_HIGH(); else SEND_LOW();
    if (data&0x40) SEND_HIGH(); else SEND_LOW();
    if (data&0x20) SEND_HIGH(); else SEND_LOW();
    if (data&0x10) SEND_HIGH(); else SEND_LOW();
    if (data&0x08) SEND_HIGH(); else SEND_LOW();
    if (data&0x04) SEND_HIGH(); else SEND_LOW();
    if (data&0x02) SEND_HIGH(); else SEND_LOW();
    if (data&0x01) SEND_HIGH(); else SEND_LOW();
    // fill EOD
    mt_set_gpio_out(GPIO_CTRL,GPIO_OUT_ZERO);
    udelay(20); //typical val: 2 us
    mt_set_gpio_out(GPIO_CTRL,GPIO_OUT_ONE);
    udelay(1000); //typical val: 350 us
    spin_unlock_irqrestore(&strobe_drv_lock, int_flags);
    do_gettimeofday(&tv2);
    PK_DBG(" End: tv: (%d)us\n", tv2.tv_usec - tv1.tv_usec);
}

int FL_Enable(void)
{
	PK_DBG("g_duty=%d\n",g_duty);
	 if(g_duty<=11)
    {
        PK_DBG(" FL_Enable: STROBE\n");
        //Enable Movie Mode
       mt_set_gpio_out(GPIO_CTRL,GPIO_OUT_ZERO);
		mt_set_gpio_out(GPIO_STROBE,GPIO_OUT_ZERO);
		mt_set_gpio_out(GPIO_CTRL,GPIO_OUT_ONE);
		udelay(100);
       int current_count=0;
		for (current_count=0;current_count<g_duty;current_count++)
			{
			SEND_HIGH();
		};
		//FL_sendData(0xA1);
    }
    else
    {
        PK_DBG(" FL_Enable: TROCH\n");
        //Enable Flash Mode
       mt_set_gpio_out(GPIO_STROBE,GPIO_OUT_ZERO);
		mt_set_gpio_out(GPIO_STROBE,GPIO_OUT_ONE);
        //FL_sendData(0xA2);
        //mt_set_gpio_out(GPIO_STROBE,GPIO_OUT_ONE);
        //msleep(100);
        //mt_set_gpio_out(GPIO_STROBE,GPIO_OUT_ZERO);
    }

    return 0;
}

int FL_Disable(void)
{
    PK_DBG(" FL_Disable \n");
    //Disables Movie/Flash Mode
   mt_set_gpio_out(GPIO_CTRL,GPIO_OUT_ZERO);
   mt_set_gpio_out(GPIO_STROBE,GPIO_OUT_ZERO);
	//FL_sendData(0xA0);

    return 0;
}

int FL_dim_duty(kal_uint32 duty)
{
	g_duty=duty;
	PK_DBG(" FL_dim_duty duty=%d\n",duty);
    return 0;
}


int FL_Init(void)
{


    if(mt_set_gpio_mode(GPIO_CTRL,GPIO_MODE_00)){PK_DBG("[constant_flashlight] set gpio mode failed!! \n");}
    if(mt_set_gpio_dir(GPIO_CTRL,GPIO_DIR_OUT)){PK_DBG("[constant_flashlight] set gpio dir failed!! \n");}
    if(mt_set_gpio_out(GPIO_CTRL,GPIO_OUT_ZERO)){PK_DBG("[constant_flashlight] set gpio failed!! \n");}
    /*Init. to disable*/
    //if(mt_set_gpio_mode(GPIO_TX,GPIO_MODE_00)){PK_DBG("[constant_flashlight] set gpio mode failed!! \n");}
    //if(mt_set_gpio_dir(GPIO_TX,GPIO_DIR_OUT)){PK_DBG("[constant_flashlight] set gpio dir failed!! \n");}
    //if(mt_set_gpio_out(GPIO_TX,GPIO_OUT_ZERO)){PK_DBG("[constant_flashlight] set gpio failed!! \n");}
    
    if(mt_set_gpio_mode(GPIO_STROBE,GPIO_MODE_00)){PK_DBG("[constant_flashlight] set gpio mode failed!! \n");}
    if(mt_set_gpio_dir(GPIO_STROBE,GPIO_DIR_OUT)){PK_DBG("[constant_flashlight] set gpio dir failed!! \n");}
    if(mt_set_gpio_out(GPIO_STROBE,GPIO_OUT_ZERO)){PK_DBG("[constant_flashlight] set gpio failed!! \n");}

    INIT_WORK(&workTimeOut, work_timeOutFunc);
    PK_DBG(" FL_Init line=%d\n",__LINE__);
    //FL_sendData(0x00);  //Disable LVP Function
    return 0;
}


int FL_Uninit(void)
{
	FL_Disable();
    return 0;
}

/*****************************************************************************
User interface
*****************************************************************************/

static void work_timeOutFunc(struct work_struct *data)
{
    FL_Disable();
    PK_DBG("ledTimeOut_callback\n");
    //printk(KERN_ALERT "work handler function./n");
}



enum hrtimer_restart ledTimeOutCallback(struct hrtimer *timer)
{
    schedule_work(&workTimeOut);
    return HRTIMER_NORESTART;
}
static struct hrtimer g_timeOutTimer;
void timerInit(void)
{
	g_timeOutTimeMs=1000; //1s
	hrtimer_init( &g_timeOutTimer, CLOCK_MONOTONIC, HRTIMER_MODE_REL );
	g_timeOutTimer.function=ledTimeOutCallback;

}



static int constant_flashlight_ioctl(MUINT32 cmd, MUINT32 arg)
{
	int i4RetValue = 0;
	int ior_shift;
	int iow_shift;
	int iowr_shift;
	ior_shift = cmd - (_IOR(FLASHLIGHT_MAGIC,0, int));
	iow_shift = cmd - (_IOW(FLASHLIGHT_MAGIC,0, int));
	iowr_shift = cmd - (_IOWR(FLASHLIGHT_MAGIC,0, int));
	PK_DBG("constant_flashlight_ioctl() line=%d ior_shift=%d, iow_shift=%d iowr_shift=%d arg=%d\n",__LINE__, ior_shift, iow_shift, iowr_shift, arg);
    switch(cmd)
    {

		case FLASH_IOC_SET_TIME_OUT_TIME_MS:
			PK_DBG("FLASH_IOC_SET_TIME_OUT_TIME_MS: %d\n",arg);
			g_timeOutTimeMs=arg;
		break;


    	case FLASH_IOC_SET_DUTY :
    		PK_DBG("FLASHLIGHT_DUTY: %d\n",arg);
    		FL_dim_duty(arg);
    		break;


    	case FLASH_IOC_SET_STEP:
    		PK_DBG("FLASH_IOC_SET_STEP: %d\n",arg);

    		break;

    	case FLASH_IOC_SET_ONOFF :
    		PK_DBG("FLASHLIGHT_ONOFF: %d\n",arg);
    		if(arg==1)
    		{
				if(g_timeOutTimeMs!=0)
	            {
	            	ktime_t ktime;
					ktime = ktime_set( 0, g_timeOutTimeMs*1000000 );
					hrtimer_start( &g_timeOutTimer, ktime, HRTIMER_MODE_REL );
	            }
    			FL_Enable();
    		}
    		else
    		{
    			FL_Disable();
				hrtimer_cancel( &g_timeOutTimer );
    		}
    		break;
		default :
    		PK_DBG(" No such command \n");
    		i4RetValue = -EPERM;
    		break;
    }
    return i4RetValue;
}




static int constant_flashlight_open(void *pArg)
{
    int i4RetValue = 0;
    PK_DBG("constant_flashlight_open line=%d\n", __LINE__);

	if (0 == strobe_Res)
	{
	    FL_Init();
		timerInit();
	}
	PK_DBG("constant_flashlight_open line=%d\n", __LINE__);
	spin_lock_irq(&g_strobeSMPLock);


    if(strobe_Res)
    {
        PK_ERR(" busy!\n");
        i4RetValue = -EBUSY;
    }
    else
    {
        strobe_Res += 1;
    }


    spin_unlock_irq(&g_strobeSMPLock);
    PK_DBG("constant_flashlight_open line=%d\n", __LINE__);

    return i4RetValue;

}


static int constant_flashlight_release(void *pArg)
{
    PK_DBG(" constant_flashlight_release\n");

    if (strobe_Res)
    {
        spin_lock_irq(&g_strobeSMPLock);

        strobe_Res = 0;
        strobe_Timeus = 0;

        /* LED On Status */
        g_strobe_On = FALSE;

        spin_unlock_irq(&g_strobeSMPLock);

    	FL_Uninit();
    }

    PK_DBG(" Done\n");

    return 0;

}


FLASHLIGHT_FUNCTION_STRUCT	constantFlashlightFunc=
{
	constant_flashlight_open,
	constant_flashlight_release,
	constant_flashlight_ioctl
};


MUINT32 constantFlashlightInit(PFLASHLIGHT_FUNCTION_STRUCT *pfFunc)
{
    if (pfFunc != NULL)
    {
        *pfFunc = &constantFlashlightFunc;
    }
    return 0;
}



/* LED flash control for high current capture mode*/
ssize_t strobe_VDIrq(void)
{

    return 0;
}

EXPORT_SYMBOL(strobe_VDIrq);

/*LT80, Bug 319, Louis, 20140415, Long press camera key to turn on/off flash light, Start*/
static int g_torch_state = 0;

static ssize_t FL_show_torch_state(struct device_driver *ddri, char *buf)
{
    PK_DBG("FL_show_torch_state = %d\n", g_torch_state);
    return sprintf(buf, "%u\n", g_torch_state);
}

static ssize_t FL_store_enable_torch(struct device_driver *ddri, const char *buf, size_t count)
{
    int enable_torch = 0;
    if (sscanf(buf, "%u", &enable_torch) != 1) {
        PK_DBG("FL_store_enable_torch: Invalid values\n");
        return -EINVAL;
    }

    if (0 == enable_torch)
    {
        FL_Disable();
        g_torch_state = 0;
    }
    else
    {
        //FL_sendData(0x00);  //Disable LVP Function
        g_duty = 0;
        FL_Enable();
        g_torch_state = 1;
    }

    return count;
}

static ssize_t FL_show_torch_on(struct device_driver *ddri, char *buf)
{
    PK_DBG("FL_show_torch_on \n");
    //FL_sendData(0x00);  //Disable LVP Function
    g_duty = 0;
    FL_Enable();
    g_torch_state = 1;
    return sprintf(buf, "%u\n", g_torch_state);
}

static ssize_t FL_show_torch_off(struct device_driver *ddri, char *buf)
{
    PK_DBG("FL_show_torch_off \n");
    FL_Disable();
    g_torch_state = 0;
    return sprintf(buf, "%u\n", g_torch_state);
}

static DRIVER_ATTR(torch_state, 0664, FL_show_torch_state, NULL);
static DRIVER_ATTR(enable_torch, 0664, NULL, FL_store_enable_torch);
static DRIVER_ATTR(torch_on, 0664, FL_show_torch_on, NULL);
static DRIVER_ATTR(torch_off, 0664, FL_show_torch_off, NULL);

static struct driver_attribute *torch_attr_list[] = {
    &driver_attr_torch_state,
    &driver_attr_enable_torch,
    &driver_attr_torch_on,
    &driver_attr_torch_off,
};

int FL_create_attr(struct device_driver *driver)
{
	int idx, err = 0;
	int num = (int)(sizeof(torch_attr_list)/sizeof(torch_attr_list[0]));
	if (driver == NULL)
	{
		return -EINVAL;
	}

	for(idx = 0; idx < num; idx++)
	{
		if((err = driver_create_file(driver, torch_attr_list[idx])))
		{
			PK_DBG("driver_create_file (%s) = %d\n", torch_attr_list[idx]->attr.name, err);
			break;
		}
	}
	return err;
}
/*LT80, Bug 319, Louis, 20140415, Long press camera key to turn on/off flash light, End*/
