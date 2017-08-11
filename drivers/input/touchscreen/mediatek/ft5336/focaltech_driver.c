#include "../tpd.h"
#include <linux/interrupt.h>
#include <cust_eint.h>
#include <linux/i2c.h>
#include <linux/sched.h>
#include <linux/kthread.h>
#include <linux/rtpm_prio.h>
#include <linux/wait.h>
#include <linux/time.h>
#include <linux/delay.h>


#include "tpd_custom_fts.h"

#include <mach/mt_pm_ldo.h>
#include <mach/mt_typedefs.h>
#include <mach/mt_boot.h>

#include <linux/input.h>
#include <linux/input/mt.h>

#include "cust_gpio_usage.h"
//dma
#include <linux/dma-mapping.h>

#include "internal.h"

#define MT_PROTOCOL_B
//#define TPD_PROXIMITY
#define FTS_GESTRUE					//if need gestrue wake up
#define TPD_AUTO_UPGRADE				// if need upgrade CTP FW when POWER ON,pls enable this MACRO

#define FTS_CTL_IIC
#define SYSFS_DEBUG
#define FTS_APK_DEBUG


#ifdef FTS_CTL_IIC
#include "focaltech_ctl.h"
#endif
#ifdef SYSFS_DEBUG
#include "focaltech_ex_fun.h"
#endif


#ifdef TPD_PROXIMITY
#include <linux/hwmsensor.h>
#include <linux/hwmsen_dev.h>
#include <linux/sensors_io.h>
#endif

#ifdef TPD_PROXIMITY

#define APS_ERR(fmt,arg...)           	printk("<<proximity>> "fmt"\n",##arg)

#define TPD_PROXIMITY_DEBUG(fmt,arg...) printk("<<proximity>> "fmt"\n",##arg)

#define TPD_PROXIMITY_DMESG(fmt,arg...) printk("<<proximity>> "fmt"\n",##arg)

static u8 tpd_proximity_flag 			= 0;

static u8 tpd_proximity_flag_one 		= 0; //add for tpd_proximity by wangdongfang

static u8 tpd_proximity_detect 		= 1;//0-->close ; 1--> far away


#endif

#ifdef FTS_GESTRUE
/*#define  KEY_GESTURE_U KEY_U
#define  KEY_GESTURE_UP KEY_UP
#define  KEY_GESTURE_DOWN KEY_DOWN
#define  KEY_GESTURE_LEFT KEY_LEFT
#define  KEY_GESTURE_RIGHT KEY_RIGHT
#define  KEY_GESTURE_O KEY_O
#define  KEY_GESTURE_E KEY_E
#define  KEY_GESTURE_C KEY_C
//#define  KEY_GESTURE_M KEY_M
//#define  KEY_GESTURE_L KEY_L
//#define  KEY_GESTURE_W KEY_W
//#define  KEY_GESTURE_S KEY_S
#define  KEY_GESTURE_V KEY_V
#define  KEY_GESTURE_Z KEY_Z
*/


#define GESTURE_LEFT		0x20
#define GESTURE_RIGHT		0x21
#define GESTURE_UP		0x22
#define GESTURE_DOWN		0x23
//#define GESTURE_DOUBLECLICK	0x24
#define GESTURE_O		0x30
//#define GESTURE_W		0x31
//#define GESTURE_M		0x32
//#define GESTURE_E		0x33
#define GESTURE_C		0x34
//#define GESTURE_L		0x44
//#define GESTURE_S		0x46
#define GESTURE_V		0x54
#define GESTURE_Z		0x41

#include "ft_gesture_lib.h"

#define FTS_GESTRUE_POINTS 255
#define FTS_GESTRUE_POINTS_ONETIME  62
#define FTS_GESTRUE_POINTS_HEADER 8
#define FTS_GESTURE_OUTPUT_ADRESS 0xD3
#define FTS_GESTURE_OUTPUT_UNIT_LENGTH 4

unsigned short coordinate_x[150] = {0};
unsigned short coordinate_y[150] = {0};
#endif

extern struct tpd_device *tpd;

int current_touchs;
char *returned_str="00000";
struct i2c_client *i2c_client = NULL;
struct task_struct *thread = NULL;

#define DEFAULT_CHIP_ID	6

struct Upgrade_Info fts_updateinfo[] =
{
	{0x55,"FT5x06",TPD_MAX_POINTS_5,AUTO_CLB_NEED,50, 30, 0x79, 0x03, 10, 2000},
	{0x08,"FT5606",TPD_MAX_POINTS_5,AUTO_CLB_NEED,50, 10, 0x79, 0x06, 100, 2000},
	{0x0a,"FT5x16",TPD_MAX_POINTS_5,AUTO_CLB_NEED,50, 30, 0x79, 0x07, 10, 1500},
	{0x06,"FT6x06",TPD_MAX_POINTS_2,AUTO_CLB_NONEED,100, 30, 0x79, 0x08, 10, 2000},
	{0x36,"FT6x36",TPD_MAX_POINTS_2,AUTO_CLB_NONEED,10, 10, 0x79, 0x18, 10, 2000},
	{0x55,"FT5x06i",TPD_MAX_POINTS_5,AUTO_CLB_NEED,50, 30, 0x79, 0x03, 10, 2000},
	{0x14,"FT5336",TPD_MAX_POINTS_5,AUTO_CLB_NONEED,30, 30, 0x79, 0x11, 10, 2000},
	{0x13,"FT3316",TPD_MAX_POINTS_5,AUTO_CLB_NONEED,30, 30, 0x79, 0x11, 10, 2000},
	{0x12,"FT5436i",TPD_MAX_POINTS_5,AUTO_CLB_NONEED,30, 30, 0x79, 0x11, 10, 2000},
	{0x11,"FT5336i",TPD_MAX_POINTS_5,AUTO_CLB_NONEED,30, 30, 0x79, 0x11, 10, 2000},
	{0x54,"FT5x46",TPD_MAX_POINTS_5,AUTO_CLB_NONEED,2, 2, 0x54, 0x2c, 10, 2000},
};

struct Upgrade_Info fts_updateinfo_curr;
#define FTS_RESET_PIN	GPIO_CTP_RST_PIN

struct fts_touch_info{
	u8 x_msb:4, rev:2, event:2;
	u8 x_lsb;
	u8 y_msb:4, id:4;
	u8 y_lsb;
	u8 weight;
	u8 speed:2, direction:2, area:4;
};

struct fts_packet_info{
	u8 gesture;
	u8 fingers:4, frame:4;
	struct fts_touch_info touch[CFG_MAX_TOUCH_POINTS];
};

static DECLARE_WAIT_QUEUE_HEAD(waiter);
static void tpd_eint_interrupt_handler(void);
extern void mt_eint_mask(unsigned int eint_num);
extern char * fts_get_gestureset(void);
extern void mt_eint_unmask(unsigned int eint_num);
extern void mt_eint_set_hw_debounce(unsigned int eint_num, unsigned int ms);
extern void mt_eint_set_polarity(unsigned int eint_num, unsigned int pol);
extern unsigned int mt_eint_set_sens(unsigned int eint_num, unsigned int sens);
extern void mt_eint_registration(unsigned int eint_num, unsigned int flow, void (EINT_FUNC_PTR)(void), unsigned int is_auto_umask);
static int tpd_probe(struct i2c_client *client, const struct i2c_device_id *id);
static int tpd_detect(struct i2c_client *client, struct i2c_board_info *info);
static int tpd_remove(struct i2c_client *client);
static int touch_event_handler(void *unused);


static int tpd_flag = 0;
static int tpd_halt=0;
static int point_num = 0;
static int p_point_num = 0;
static int i2c_driver_need_delet = 0;


#define __MSG_DMA_MODE__  //
#ifdef __MSG_DMA_MODE__
u8 *g_dma_buff_va = NULL;    //
u8 *g_dma_buff_pa = NULL;    //
#endif

#ifdef __MSG_DMA_MODE__
static void msg_dma_alloct(struct i2c_client *client)
{
	//g_dma_buff_va = (u8 *)dma_alloc_coherent(&client->dev, 256, &g_dma_buff_pa, GFP_KERNEL);//64 bit

	g_dma_buff_va = (u8 *)dma_alloc_coherent(NULL, 256, &g_dma_buff_pa, GFP_KERNEL);//32 bit
	if(!g_dma_buff_va)
	{
		TPD_DMESG("[DMA][Error] Allocate DMA I2C Buffer failed!\n");
	}
}
static void msg_dma_release()
{
	if(g_dma_buff_va)
	{
		//dma_free_coherent(&i2c_client->dev, 256, g_dma_buff_va, g_dma_buff_pa);//64 bit
		dma_free_coherent(NULL, 256, g_dma_buff_va, g_dma_buff_pa);//32 bit
		g_dma_buff_va = NULL;
		g_dma_buff_pa = NULL;
		TPD_DMESG("[DMA][release] Allocate DMA I2C Buffer release!\n");
	}
}
#endif


#define TPD_OK 0
//register define

#define DEVICE_MODE 0x00
#define GEST_ID 0x01
#define TD_STATUS 0x02

#define TOUCH1_XH 0x03
#define TOUCH1_XL 0x04
#define TOUCH1_YH 0x05
#define TOUCH1_YL 0x06

#define TOUCH2_XH 0x09
#define TOUCH2_XL 0x0A
#define TOUCH2_YH 0x0B
#define TOUCH2_YL 0x0C

#define TOUCH3_XH 0x0F
#define TOUCH3_XL 0x10
#define TOUCH3_YH 0x11
#define TOUCH3_YL 0x12
//register define

#define TPD_RESET_ISSUE_WORKAROUND

#define TPD_MAX_RESET_COUNT 3


struct ts_event
{
	u16 au16_x[CFG_MAX_TOUCH_POINTS];	/*x coordinate */
	u16 au16_y[CFG_MAX_TOUCH_POINTS];	/*y coordinate */
	u8 au8_touch_event[CFG_MAX_TOUCH_POINTS];	/*touch event:
							  0 -- down; 1-- up; 2 -- contact */
	u8 au8_finger_id[CFG_MAX_TOUCH_POINTS];	/*touch ID */
	u16 pressure;
	u8 touch_point;
};


#ifdef TPD_HAVE_BUTTON
static int tpd_keys_local[TPD_KEY_COUNT] = TPD_KEYS;
static int tpd_keys_dim_local[TPD_KEY_COUNT][4] = TPD_KEYS_DIM;
#endif
#if (defined(TPD_WARP_START) && defined(TPD_WARP_END))
static int tpd_wb_start_local[TPD_WARP_CNT] = TPD_WARP_START;
static int tpd_wb_end_local[TPD_WARP_CNT]   = TPD_WARP_END;
#endif
#if (defined(TPD_HAVE_CALIBRATION) && !defined(TPD_CUSTOM_CALIBRATION))
static int tpd_calmat_local[8]     = TPD_CALIBRATION_MATRIX;
static int tpd_def_calmat_local[8] = TPD_CALIBRATION_MATRIX;
#endif

static DEFINE_MUTEX(i2c_rw_access);
//#define VELOCITY_CUSTOM_fts
#ifdef VELOCITY_CUSTOM_fts
#include <linux/device.h>
#include <linux/miscdevice.h>
#include <asm/uaccess.h>

// for magnify velocity********************************************

#ifndef TPD_VELOCITY_CUSTOM_X
#define TPD_VELOCITY_CUSTOM_X 10
#endif
#ifndef TPD_VELOCITY_CUSTOM_Y
#define TPD_VELOCITY_CUSTOM_Y 10
#endif

#define TOUCH_IOC_MAGIC 'A'

#define TPD_GET_VELOCITY_CUSTOM_X _IO(TOUCH_IOC_MAGIC,0)
#define TPD_GET_VELOCITY_CUSTOM_Y _IO(TOUCH_IOC_MAGIC,1)

int g_v_magnify_x =TPD_VELOCITY_CUSTOM_X;
int g_v_magnify_y =TPD_VELOCITY_CUSTOM_Y;

static DEFINE_MUTEX(i2c_rw_access);

static int tpd_misc_open(struct inode *inode, struct file *file)
{
	return nonseekable_open(inode, file);
}
/*----------------------------------------------------------------------------*/
static int tpd_misc_release(struct inode *inode, struct file *file)
{
	return 0;
}
/*----------------------------------------------------------------------------*/

static long tpd_unlocked_ioctl(struct file *file, unsigned int cmd,
		unsigned long arg)
{
	void __user *data;
	long err = 0;

	if(_IOC_DIR(cmd) & _IOC_READ)
	{
		err = !access_ok(VERIFY_WRITE, (void __user *)arg, _IOC_SIZE(cmd));
	}
	else if(_IOC_DIR(cmd) & _IOC_WRITE)
	{
		err = !access_ok(VERIFY_READ, (void __user *)arg, _IOC_SIZE(cmd));
	}

	if(err)
	{
		printk("tpd: access error: %08X, (%2d, %2d)\n", cmd, _IOC_DIR(cmd), _IOC_SIZE(cmd));
		return -EFAULT;
	}

	switch(cmd)
	{
		case TPD_GET_VELOCITY_CUSTOM_X:
			data = (void __user *) arg;

			if(data == NULL)
			{
				err = -EINVAL;
				break;
			}

			if(copy_to_user(data, &g_v_magnify_x, sizeof(g_v_magnify_x)))
			{
				err = -EFAULT;
				break;
			}

			break;

		case TPD_GET_VELOCITY_CUSTOM_Y:
			data = (void __user *) arg;

			if(data == NULL)
			{
				err = -EINVAL;
				break;
			}

			if(copy_to_user(data, &g_v_magnify_y, sizeof(g_v_magnify_y)))
			{
				err = -EFAULT;
				break;
			}

			break;

		default:
			printk("tpd: unknown IOCTL: 0x%08x\n", cmd);
			err = -ENOIOCTLCMD;
			break;
	}

	return err;
}


static struct file_operations tpd_fops =
{
	//	.owner = THIS_MODULE,
	.open = tpd_misc_open,
	.release = tpd_misc_release,
	.unlocked_ioctl = tpd_unlocked_ioctl,
};
/*----------------------------------------------------------------------------*/
static struct miscdevice tpd_misc_device =
{
	.minor = MISC_DYNAMIC_MINOR,
	.name = "touch",
	.fops = &tpd_fops,
};

//**********************************************
#endif

struct touch_info
{
	int y[10];
	int x[10];
	int p[10];
	int id[10];
	int count;
};

static const struct i2c_device_id fts_tpd_id[] = {{"fts",0},{}};

static struct i2c_board_info __initdata fts_i2c_tpd= { I2C_BOARD_INFO("fts", (0x70>>1))};


static struct i2c_driver tpd_i2c_driver =
{
	.driver = {
		.name = "fts",
		//.owner = THIS_MODULE,
	},
	.probe = tpd_probe,
	.remove = (tpd_remove),
	.id_table = fts_tpd_id,
	.detect = tpd_detect,

};


int fts_i2c_Read(struct i2c_client *client, char *writebuf,int writelen, char *readbuf, int readlen)
{
	int ret,i;
	// for DMA I2c transfer
	mutex_lock(&i2c_rw_access);

	if(writelen!=0)
	{
		//DMA Write
		memcpy(g_dma_buff_va, writebuf, writelen);
		client->addr = client->addr & I2C_MASK_FLAG | I2C_DMA_FLAG;

		if((ret=i2c_master_send(client, (unsigned char *)g_dma_buff_pa, writelen))!=writelen)
			dev_err(&client->dev, "###%s i2c write len=%x,buffaddr=%p\n", __func__,ret,g_dma_buff_pa);

		client->addr = client->addr & I2C_MASK_FLAG &(~ I2C_DMA_FLAG);
	}

	//DMA Read

	if(readlen!=0)
	{
		client->addr = client->addr & I2C_MASK_FLAG | I2C_DMA_FLAG;
		ret = i2c_master_recv(client, (unsigned char *)g_dma_buff_pa, readlen);
		memcpy(readbuf, g_dma_buff_va, readlen);
		client->addr = client->addr & I2C_MASK_FLAG &(~ I2C_DMA_FLAG);
	}

	mutex_unlock(&i2c_rw_access);
	return ret;
}

/*write data by i2c*/
int fts_i2c_Write(struct i2c_client *client, char *writebuf, int writelen)
{
	int ret;
	int i = 0;
	mutex_lock(&i2c_rw_access);

	if(writelen!=0)
	{
		memcpy(g_dma_buff_va, writebuf, writelen);
		client->addr = client->addr & I2C_MASK_FLAG | I2C_DMA_FLAG;

		if((ret=i2c_master_send(client, (unsigned char *)g_dma_buff_pa, writelen))!=writelen)
			dev_err(&client->dev, "###%s i2c write len=%x,buffaddr=%p\n", __func__,ret,g_dma_buff_pa);

		client->addr = client->addr & I2C_MASK_FLAG &(~ I2C_DMA_FLAG);
	}

	mutex_unlock(&i2c_rw_access);
	return ret;
}

int fts_write_reg(struct i2c_client *client, u8 regaddr, u8 regvalue)
{
	unsigned char buf[2] = {0};
	buf[0] = regaddr;
	buf[1] = regvalue;
	return fts_i2c_Write(client, buf, sizeof(buf));
}

int fts_read_reg(struct i2c_client *client, u8 regaddr, u8 *regvalue)
{
	return fts_i2c_Read(client, &regaddr, 1, regvalue, 1);
}

void focaltech_get_upgrade_array(void)
{
	u8 chip_id;
	u32 i;
	i2c_smbus_read_i2c_block_data(i2c_client,FTS_REG_CHIP_ID,1,&chip_id);
	//	chip_id=0x14;
	printk("%s chip_id = %x\n", __func__, chip_id);

	for(i=0; i<sizeof(fts_updateinfo)/sizeof(struct Upgrade_Info); i++)
	{
		if(chip_id==fts_updateinfo[i].CHIP_ID)
		{
			memcpy(&fts_updateinfo_curr, &fts_updateinfo[i], sizeof(struct Upgrade_Info));
			break;
		}
	}

	if(i >= sizeof(fts_updateinfo)/sizeof(struct Upgrade_Info))
	{
		memcpy(&fts_updateinfo_curr, &fts_updateinfo[DEFAULT_CHIP_ID], sizeof(struct Upgrade_Info));
	}
}

static  void tpd_down(int x, int y, int p)
{
	if(x > TPD_RES_X)
	{
		TPD_DEBUG("warning: IC have sampled wrong value.\n");;
		return;
	}

	input_report_key(tpd->dev, BTN_TOUCH, 1);
	input_report_abs(tpd->dev, ABS_MT_TOUCH_MAJOR, 20);
	input_report_abs(tpd->dev, ABS_MT_PRESSURE, 0x3f);
	input_report_abs(tpd->dev, ABS_MT_POSITION_X, x);
	input_report_abs(tpd->dev, ABS_MT_POSITION_Y, y);
	//printk("tpd:D[%4d %4d %4d] ", x, y, p);
	/* track id Start 0 */
	//input_report_abs(tpd->dev, ABS_MT_TRACKING_ID, p);
	input_mt_sync(tpd->dev);

	if(FACTORY_BOOT == get_boot_mode()|| RECOVERY_BOOT == get_boot_mode())
	{
		tpd_button(x, y, 1);
	}

	if(y > TPD_RES_Y) //virtual key debounce to avoid android ANR issue
	{
		//msleep(50);
		printk("D virtual key \n");
	}

	TPD_EM_PRINT(x, y, x, y, p-1, 1);
}

static  void tpd_up(int x, int y,int *count)
{
	input_report_key(tpd->dev, BTN_TOUCH, 0);
	//printk("U[%4d %4d %4d] ", x, y, 0);
	input_mt_sync(tpd->dev);
	TPD_EM_PRINT(x, y, x, y, 0, 0);

	if(FACTORY_BOOT == get_boot_mode()|| RECOVERY_BOOT == get_boot_mode())
	{
		tpd_button(x, y, 0);
	}
}

static int tpd_touchinfo(struct touch_info *cinfo, struct touch_info *pinfo)
{
	int i = 0;
	char data[128] = {0};
	u16 high_byte,low_byte,reg;
	u8 report_rate =0;
	p_point_num = point_num;

	if(tpd_halt)
	{
		TPD_DMESG("tpd_touchinfo return ..\n");
		return false;
	}

	reg = 0x00;
	fts_i2c_Read(i2c_client, &reg, 1, data, 64);
	/*get the number of the touch points*/
	point_num= data[2] & 0x0f;

	for(i = 0; i < point_num; i++)
	{
		cinfo->p[i] = data[3+6*i] >> 6; //event flag
		cinfo->id[i] = data[3+6*i+2]>>4; //touch id
		/*get the X coordinate, 2 bytes*/
		high_byte = data[3+6*i];
		high_byte <<= 8;
		high_byte &= 0x0f00;
		low_byte = data[3+6*i + 1];
		cinfo->x[i] = high_byte |low_byte;
		high_byte = data[3+6*i+2];
		high_byte <<= 8;
		high_byte &= 0x0f00;
		low_byte = data[3+6*i+3];
		cinfo->y[i] = high_byte |low_byte;
	}

	return true;
};

/*
 *report the point information
 */

/*
   static int fts_read_Touchdata(struct ts_event *pinfo)
   {
   u8 buf[POINT_READ_BUF] = { 0 };
   int ret = -1;
   int i = 0;
   u8 pointid = FT_MAX_ID;

   if(tpd_halt)
   {
   TPD_DMESG("tpd_touchinfo return ..\n");
   return false;
   }

   ret = fts_i2c_Read(i2c_client, buf, 1, buf, POINT_READ_BUF);

   if(ret < 0)
   {
   dev_err(&i2c_client->dev, "%s read touchdata failed.\n",__func__);
   return ret;
   }

   memset(pinfo, 0, sizeof(struct ts_event));
   pinfo->touch_point = 0;

   for(i = 0; i < fts_updateinfo_curr.TPD_MAX_POINTS; i++)
   {
   pointid = (buf[FT_TOUCH_ID_POS + FT_TOUCH_STEP * i]) >> 4;

   if(pointid >= FT_MAX_ID)
   break;
   else
   pinfo->touch_point++;

   pinfo->au16_x[i] =
   (s16)(buf[FT_TOUCH_X_H_POS + FT_TOUCH_STEP * i] & 0x0F) <<
   8 | (s16) buf[FT_TOUCH_X_L_POS + FT_TOUCH_STEP * i];
   pinfo->au16_y[i] =
   (s16)(buf[FT_TOUCH_Y_H_POS + FT_TOUCH_STEP * i] & 0x0F) <<
   8 | (s16) buf[FT_TOUCH_Y_L_POS + FT_TOUCH_STEP * i];
   pinfo->au8_touch_event[i] =
   buf[FT_TOUCH_EVENT_POS + FT_TOUCH_STEP * i] >> 6;
   pinfo->au8_finger_id[i] =
   (buf[FT_TOUCH_ID_POS + FT_TOUCH_STEP * i]) >> 4;
   }

   return 0;
   }
 */

/*
 *report the point information
 */
static void fts_report_value(struct ts_event *data)
{

	int ret = -1;
	int touchs = 0;
	u8 addr = 0x01;
	struct fts_packet_info buf;
	struct fts_touch_info *touch;
	int i, x, y;

	ret = fts_i2c_Read(i2c_client, &addr, 1, &buf, sizeof(struct fts_packet_info));

	if(ret < 0) {
		dev_err(&i2c_client->dev, "%s read touchdata failed.\n",__func__);
		return ret;
	}

	touch = &buf.touch[0];

	for (i = 0; i < (buf.fingers) && (i < MT_MAX_TOUCH_POINTS); i++, touch++) {

		x = (u16)(touch->x_msb << 8) | (u16)touch->x_lsb;
		y = (u16)(touch->y_msb << 8) | (u16)touch->y_lsb;

		input_mt_slot(tpd->dev, touch->id);

		//type B touch event,touch down is touch->event=0, touch move is touch->event=2
		if (touch->event == 0 || touch->event == 2) {
			input_mt_report_slot_state(tpd->dev, MT_TOOL_FINGER,true);
			//input_report_abs(tpd->dev, ABS_MT_PRESSURE,data->pressure[i]/*0x3f*/);
			input_report_abs(tpd->dev, ABS_MT_TOUCH_MAJOR, 0x80/*0x05*/);
			input_report_abs(tpd->dev, ABS_MT_POSITION_X, x);
			input_report_abs(tpd->dev, ABS_MT_POSITION_Y, y);
			touchs |= BIT(touch->id);
			current_touchs |= BIT(touch->id);
		}
		else {
			input_mt_report_slot_state(tpd->dev, MT_TOOL_FINGER,false);
			current_touchs &= ~BIT(touch->id);
		}
	}

	if (unlikely(current_touchs ^ touchs)) {
		for(i = 0; i < CFG_MAX_TOUCH_POINTS; i++) {
			if(BIT(i) & (current_touchs ^ touchs)) {
				input_mt_slot(tpd->dev, i);
				input_mt_report_slot_state(tpd->dev, MT_TOOL_FINGER, false);
			}
		}
	}

	current_touchs = touchs;

	if(touchs)
		input_report_key(tpd->dev, BTN_TOUCH, 1);
	else
		input_report_key(tpd->dev, BTN_TOUCH, 0);

	input_sync(tpd->dev);

}

#ifdef TPD_PROXIMITY
int tpd_read_ps(void)
{
	tpd_proximity_detect;
	return 0;
}

static int tpd_get_ps_value(void)
{
	return tpd_proximity_detect;
}

static int tpd_enable_ps(int enable)
{
	u8 state;
	int ret = -1;
	i2c_smbus_read_i2c_block_data(i2c_client, 0xB0, 1, &state);
	printk("[proxi_fts]read: 999 0xb0's value is 0x%02X\n", state);

	if(enable)
	{
		state |= 0x01;
		tpd_proximity_flag = 1;
		TPD_PROXIMITY_DEBUG("[proxi_fts]ps function is on\n");
	}
	else
	{
		state &= 0x00;
		tpd_proximity_flag = 0;
		TPD_PROXIMITY_DEBUG("[proxi_fts]ps function is off\n");
	}

	ret = i2c_smbus_write_i2c_block_data(i2c_client, 0xB0, 1, &state);
	TPD_PROXIMITY_DEBUG("[proxi_fts]write: 0xB0's value is 0x%02X\n", state);
	return 0;
}

int tpd_ps_operate(void *self, uint32_t command, void *buff_in, int size_in,

		void *buff_out, int size_out, int *actualout)
{
	int err = 0;
	int value;
	hwm_sensor_data *sensor_data;
	TPD_DEBUG("[proxi_fts]command = 0x%02X\n", command);

	switch(command)
	{
		case SENSOR_DELAY:
			if((buff_in == NULL) || (size_in < sizeof(int)))
			{
				APS_ERR("Set delay parameter error!\n");
				err = -EINVAL;
			}

			// Do nothing
			break;

		case SENSOR_ENABLE:
			if((buff_in == NULL) || (size_in < sizeof(int)))
			{
				APS_ERR("Enable sensor parameter error!\n");
				err = -EINVAL;
			}
			else
			{
				value = *(int *)buff_in;

				if(value)
				{
					if((tpd_enable_ps(1) != 0))
					{
						APS_ERR("enable ps fail: %d\n", err);
						return -1;
					}
				}
				else
				{
					if((tpd_enable_ps(0) != 0))
					{
						APS_ERR("disable ps fail: %d\n", err);
						return -1;
					}
				}
			}

			break;

		case SENSOR_GET_DATA:
			if((buff_out == NULL) || (size_out< sizeof(hwm_sensor_data)))
			{
				APS_ERR("get sensor data parameter error!\n");
				err = -EINVAL;
			}
			else
			{
				sensor_data = (hwm_sensor_data *)buff_out;

				if((err = tpd_read_ps()))
				{
					err = -1;;
				}
				else
				{
					sensor_data->values[0] = tpd_get_ps_value();
					TPD_PROXIMITY_DEBUG("huang sensor_data->values[0] 1082 = %d\n", sensor_data->values[0]);
					sensor_data->value_divide = 1;
					sensor_data->status = SENSOR_STATUS_ACCURACY_MEDIUM;
				}
			}

			break;

		default:
			APS_ERR("proxmy sensor operate function no this parameter %d!\n", command);
			err = -1;
			break;
	}

	return err;
}
#endif

#ifdef FTS_GESTRUE
static void check_gesture(int gesture_id)
{
	printk("fts gesture_id==0x%x\n ",gesture_id);

	switch(gesture_id)
	{
		case GESTURE_LEFT:
			if(returned_str[2] == '0')
				goto Gestur_Char_off;
			printk("fts report left\n");
			input_report_key(tpd->dev, KEY_GESTURE_LEFT, 1);
			input_sync(tpd->dev);
			input_report_key(tpd->dev, KEY_GESTURE_LEFT, 0);
			input_sync(tpd->dev);
			break;

		case GESTURE_RIGHT:
			if(returned_str[2] == '0')
				goto Gestur_Char_off;
			printk("fts report right\n");
			input_report_key(tpd->dev, KEY_GESTURE_RIGHT, 1);
			input_sync(tpd->dev);
			input_report_key(tpd->dev, KEY_GESTURE_RIGHT, 0);
			input_sync(tpd->dev);
			break;

		case GESTURE_UP:
			if(returned_str[1] == '0')
				goto Gestur_Char_off;
			printk("fts report up\n");
			input_report_key(tpd->dev, KEY_GESTURE_UP, 1);
			input_sync(tpd->dev);
			input_report_key(tpd->dev, KEY_GESTURE_UP, 0);
			input_sync(tpd->dev);
			break;

		case GESTURE_DOWN:
			if(returned_str[1] == '0')
				goto Gestur_Char_off;
			printk("fts report down\n");
			input_report_key(tpd->dev, KEY_GESTURE_DOWN, 1);
			input_sync(tpd->dev);
			input_report_key(tpd->dev, KEY_GESTURE_DOWN, 0);
			input_sync(tpd->dev);
			break;

			/*		case GESTURE_DOUBLECLICK:
					input_report_key(tpd->dev, KEY_GESTURE_U, 1);
					input_sync(tpd->dev);
					input_report_key(tpd->dev, KEY_GESTURE_U, 0);
					input_sync(tpd->dev);
					break;
			 */
		case GESTURE_O:
			if(returned_str[2] == '0')
				goto Gestur_Char_off;
			printk("fts report O\n");
			input_report_key(tpd->dev, KEY_GESTURE_O, 1);
			input_sync(tpd->dev);
			input_report_key(tpd->dev, KEY_GESTURE_O, 0);
			input_sync(tpd->dev);
			break;

			/*		case GESTURE_W:
					input_report_key(tpd->dev, KEY_GESTURE_W, 1);
					input_sync(tpd->dev);
					printk("fts report W\n");
					input_report_key(tpd->dev, KEY_GESTURE_W, 0);
					input_sync(tpd->dev);
					break;

					case GESTURE_M:
					input_report_key(tpd->dev, KEY_GESTURE_M, 1);
					input_sync(tpd->dev);
					printk("fts report M\n");
					input_report_key(tpd->dev, KEY_GESTURE_M, 0);
					input_sync(tpd->dev);
					break;

					case GESTURE_E:
					input_report_key(tpd->dev, KEY_GESTURE_E, 1);
					printk("fts report E\n");
					input_sync(tpd->dev);
					input_report_key(tpd->dev, KEY_GESTURE_E, 0);
					input_sync(tpd->dev);
					break;

			 */		case GESTURE_C:
			if(returned_str[3] == '0')
				goto Gestur_Char_off;
			printk("fts report C\n");
			input_report_key(tpd->dev, KEY_GESTURE_C, 1);
			input_sync(tpd->dev);
			input_report_key(tpd->dev, KEY_GESTURE_C, 0);
			input_sync(tpd->dev);
			break;

			/*		case GESTURE_L:
					input_report_key(tpd->dev, KEY_GESTURE_L, 1);
					input_sync(tpd->dev);
					printk("fts report L\n");
					input_report_key(tpd->dev, KEY_GESTURE_L, 0);
					input_sync(tpd->dev);
					break;

					case GESTURE_S:
					input_report_key(tpd->dev, KEY_GESTURE_S, 1);
					printk("fts report S\n");
					input_sync(tpd->dev);
					input_report_key(tpd->dev, KEY_GESTURE_S, 0);
					input_sync(tpd->dev);
					break;

			 */		case GESTURE_V:
			if(returned_str[4] == '0')
				goto Gestur_Char_off;
			input_report_key(tpd->dev, KEY_GESTURE_V, 1);
			printk("fts report V\n");
			input_sync(tpd->dev);
			input_report_key(tpd->dev, KEY_GESTURE_V, 0);
			input_sync(tpd->dev);
			break;

		case GESTURE_Z:
			if(returned_str[2] == '0')
				goto Gestur_Char_off;
			printk("fts report Z\n");
			input_report_key(tpd->dev, KEY_GESTURE_Z, 1);
			input_sync(tpd->dev);
			input_report_key(tpd->dev, KEY_GESTURE_Z, 0);
			input_sync(tpd->dev);
			break;
Gestur_Char_off:
		default:
			break;
	}
}

static int fts_read_Gestruedata(void)
{
	unsigned char buf[FTS_GESTRUE_POINTS * 3] = { 0 };
	int ret = -1;
	int i = 0;
	buf[0] = 0xd3;
	int gestrue_id = 0;
	short pointnum = 0;
	pointnum = 0;
	ret = fts_i2c_Read(i2c_client, buf, 1, buf, FTS_GESTRUE_POINTS_HEADER);

	//printk( "tpd read FTS_GESTRUE_POINTS_HEADER.\n");
	if(ret < 0)
	{
		printk("%s read touchdata failed.\n", __func__);
		return ret;
	}

	/* FW */
	if(fts_updateinfo_curr.CHIP_ID==0x54)
	{
		gestrue_id = buf[0];
		pointnum = (short)(buf[1]) & 0xff;
		buf[0] = 0xd3;

		if((pointnum * 4 + 8)<255)
		{
			ret = fts_i2c_Read(i2c_client, buf, 1, buf, (pointnum * 4 + 8));
		}
		else
		{
			ret = fts_i2c_Read(i2c_client, buf, 1, buf, 255);
			ret = fts_i2c_Read(i2c_client, buf, 0, buf+255, (pointnum * 4 + 8) -255);
		}

		if(ret < 0)
		{
			printk("%s read touchdata failed.\n", __func__);
			return ret;
		}

		check_gesture(gestrue_id);

		for(i = 0; i < pointnum; i++)
		{
			coordinate_x[i] = (((s16) buf[0 + (4 * i)]) & 0x0F) <<
				8 | (((s16) buf[1 + (4 * i)])& 0xFF);
			coordinate_y[i] = (((s16) buf[2 + (4 * i)]) & 0x0F) <<
				8 | (((s16) buf[3 + (4 * i)]) & 0xFF);
		}

		return -1;
	}

	if(0x24 == buf[0])
	{
		gestrue_id = 0x24;
		check_gesture(gestrue_id);
		printk("tpd %d check_gesture gestrue_id.\n", gestrue_id);
		return -1;
	}

	pointnum = (short)(buf[1]) & 0xff;
	buf[0] = 0xd3;

	if((pointnum * 4 + 8)<255)
	{
		ret = fts_i2c_Read(i2c_client, buf, 1, buf, (pointnum * 4 + 8));
	}
	else
	{
		ret = fts_i2c_Read(i2c_client, buf, 1, buf, 255);
		ret = fts_i2c_Read(i2c_client, buf, 0, buf+255, (pointnum * 4 + 8) -255);
	}

	if(ret < 0)
	{
		printk("%s read touchdata failed.\n", __func__);
		return ret;
	}

	gestrue_id = fetch_object_sample(buf, pointnum);
	check_gesture(gestrue_id);
	printk("tpd %d read gestrue_id.\n", gestrue_id);

	for(i = 0; i < pointnum; i++)
	{
		coordinate_x[i] = (((s16) buf[0 + (4 * i)]) & 0x0F) <<
			8 | (((s16) buf[1 + (4 * i)])& 0xFF);
		coordinate_y[i] = (((s16) buf[2 + (4 * i)]) & 0x0F) <<
			8 | (((s16) buf[3 + (4 * i)]) & 0xFF);
	}

	return -1;
}
#endif

static int touch_event_handler(void *unused)
{
	struct touch_info cinfo, pinfo;
	struct ts_event pevent;
	int i=0;
	int ret = 0;
	struct sched_param param = { .sched_priority = RTPM_PRIO_TPD };
	sched_setscheduler(current, SCHED_RR, &param);
#ifdef TPD_PROXIMITY
	int err;
	hwm_sensor_data sensor_data;
	u8 proximity_status;
#endif
	u8 state;

	do
	{
		mt_eint_unmask(CUST_EINT_TOUCH_PANEL_NUM);
		set_current_state(TASK_INTERRUPTIBLE);
		wait_event_interruptible(waiter,tpd_flag!=0);
		tpd_flag = 0;
		set_current_state(TASK_RUNNING);
		//printk("tpd touch_event_handler\n");
		//#ifdef FTS_GESTRUE
		if(returned_str[0] == '1')
		{
			i2c_smbus_read_i2c_block_data(i2c_client, 0xd0, 1, &state);

			//printk("tpd fts_read_Gestruedata state=%d\n",state);
			if(state ==1)
			{
				fts_read_Gestruedata();
				continue;
			}
		}
		//#endif
#ifdef TPD_PROXIMITY

		if(tpd_proximity_flag == 1)
		{
			i2c_smbus_read_i2c_block_data(i2c_client, 0xB0, 1, &state);
			TPD_PROXIMITY_DEBUG("proxi_fts 0xB0 state value is 1131 0x%02X\n", state);

			if(!(state&0x01))
			{
				tpd_enable_ps(1);
			}

			i2c_smbus_read_i2c_block_data(i2c_client, 0x01, 1, &proximity_status);
			TPD_PROXIMITY_DEBUG("proxi_fts 0x01 value is 1139 0x%02X\n", proximity_status);

			if(proximity_status == 0xC0)
			{
				tpd_proximity_detect = 0;
			}
			else if(proximity_status == 0xE0)
			{
				tpd_proximity_detect = 1;
			}

			TPD_PROXIMITY_DEBUG("tpd_proximity_detect 1149 = %d\n", tpd_proximity_detect);

			if((err = tpd_read_ps()))
			{
				TPD_PROXIMITY_DMESG("proxi_fts read ps data 1156: %d\n", err);
			}

			sensor_data.values[0] = tpd_get_ps_value();
			sensor_data.value_divide = 1;
			sensor_data.status = SENSOR_STATUS_ACCURACY_MEDIUM;
			//if ((err = hwmsen_get_interrupt_data(ID_PROXIMITY, &sensor_data)))
			//{
			//	TPD_PROXIMITY_DMESG(" proxi_5206 call hwmsen_get_interrupt_data failed= %d\n", err);
			//}
		}

#endif
#ifdef MT_PROTOCOL_B
		{
			//			ret = fts_read_Touchdata(&pevent);
			//			if(ret == 0)
			fts_report_value(&pevent);
		}
#else
		{
			if(tpd_touchinfo(&cinfo, &pinfo))
			{
				printk("tpd point_num = %d\n",point_num);
				TPD_DEBUG_SET_TIME;

				if(point_num >0)
				{
					for(i =0; i<point_num; i++)//only support 3 point
					{
						tpd_down(cinfo.x[i], cinfo.y[i], cinfo.id[i]);
					}

					input_sync(tpd->dev);
				}
				else
				{
					tpd_up(cinfo.x[0], cinfo.y[0],&cinfo.id[0]);
					//TPD_DEBUG("release --->\n");
					input_sync(tpd->dev);
				}
			}
		}
#endif
	}
	while(!kthread_should_stop());

	return 0;
}
/*
   void fts_reset_tp(int HighOrLow)
   {
   if(HighOrLow)
   {
   mt_set_gpio_mode(GPIO_CTP_RST_PIN, GPIO_CTP_RST_PIN_M_GPIO);
   mt_set_gpio_dir(GPIO_CTP_RST_PIN, GPIO_DIR_OUT);
   mt_set_gpio_out(GPIO_CTP_RST_PIN, GPIO_OUT_ONE);
   }
   else
   {
   mt_set_gpio_mode(GPIO_CTP_RST_PIN, GPIO_CTP_RST_PIN_M_GPIO);
   mt_set_gpio_dir(GPIO_CTP_RST_PIN, GPIO_DIR_OUT);
   mt_set_gpio_out(GPIO_CTP_RST_PIN, GPIO_OUT_ZERO);
   }
   }
 */

static int tpd_detect(struct i2c_client *client, struct i2c_board_info *info)
{
	strcpy(info->type, TPD_DEVICE);
	return 0;
}

static void tpd_eint_interrupt_handler(void)
{
	//TPD_DEBUG("TPD interrupt has been triggered\n");
	TPD_DEBUG_PRINT_INT;
	tpd_flag = 1;
	wake_up_interruptible(&waiter);
}
/*
   static int fts_init_gpio_hw(void)
   {
   int ret = 0;
   int i = 0;
   mt_set_gpio_mode(GPIO_CTP_RST_PIN, GPIO_CTP_RST_PIN_M_GPIO);
   mt_set_gpio_dir(GPIO_CTP_RST_PIN, GPIO_DIR_OUT);
   mt_set_gpio_out(GPIO_CTP_RST_PIN, GPIO_OUT_ONE);
   return ret;
   }
 */
static int fts_init_gpio_hw(void)
{
	int ret = 0;

	if(mt_set_gpio_mode(GPIO_CTP_EINT_PIN, GPIO_CTP_EINT_PIN_M_EINT)!=0)
	{
		printk("[FTS]mt_set_gpio_mode EINT_PIN error");
		mt_eint_mask(GPIO_CTP_EINT_PIN);
		return -1;
	}

	mt_set_gpio_dir(GPIO_CTP_EINT_PIN, GPIO_DIR_IN);
	mt_set_gpio_pull_enable(GPIO_CTP_EINT_PIN, GPIO_PULL_ENABLE);
	mt_set_gpio_pull_select(GPIO_CTP_EINT_PIN, GPIO_PULL_UP);


	if(mt_set_gpio_mode(GPIO_CTP_RST_PIN, GPIO_CTP_RST_PIN_M_GPIO)!=0)
	{

		printk("[FTS]mt_set_gpio_mode RST_PIN error");
		mt_eint_mask(GPIO_CTP_RST_PIN);
		return -1;
	}

	mt_set_gpio_dir(GPIO_CTP_RST_PIN, GPIO_DIR_OUT);
	mt_set_gpio_out(GPIO_CTP_RST_PIN, GPIO_OUT_ZERO);

	return ret;
}

void fts_reset_hw(void)
{

	mt_set_gpio_out(GPIO_CTP_RST_PIN, GPIO_OUT_ZERO);
	msleep(1);
	mt_set_gpio_out(GPIO_CTP_RST_PIN, GPIO_OUT_ONE);
	msleep(200);

}

static void tpd_power_down(void)
{

	mt_set_gpio_out(GPIO_CTP_RST_PIN, GPIO_OUT_ZERO);
	msleep(1);
	hwPowerDown(TPD_POWER_SOURCE_CUSTOM, "TP");
}

static void tpd_power_on(void)
{

	mt_set_gpio_out(GPIO_CTP_RST_PIN, GPIO_OUT_ZERO);
	if(mt_set_gpio_out(GPIO_CTP_RST_PIN, GPIO_OUT_ZERO)!=0)
	{
		printk("[FTS]mt_set_gpio_mode power on error");
		return -1;
	}

	msleep(1);

#ifdef TPD_POWER_SOURCE_1800
	hwPowerOn(TPD_POWER_SOURCE_1800, VOL_1800, "TP");
#endif

#ifdef TPD_POWER_SOURCE_CUSTOM
	hwPowerOn(TPD_POWER_SOURCE_CUSTOM, VOL_2800, "TP");
	fts_reset_hw();
#else
	hwPowerOn(MT65XX_POWER_LDO_VGP2, VOL_2800, "TP");
	fts_reset_hw();
#endif

	/*
#ifdef TPD_POWER_SOURCE_CUSTOM
hwPowerOn(TPD_POWER_SOURCE_CUSTOM, VOL_3300, "TP");
#else
hwPowerOn(MT65XX_POWER_LDO_VGP2, VOL_2800, "TP");
	//hwPowerOn(MT65XX_POWER_LDO_VGP1, VOL_3300, "TP");//Tommy
	//hwPowerOn(MT6323_POWER_LDO_VIBR, VOL_3300, "TP");//Tommy
#endif

#ifdef TPD_CLOSE_POWER_IN_SLEEP
hwPowerDown(TPD_POWER_SOURCE,"TP");
hwPowerOn(TPD_POWER_SOURCE,VOL_3300,"TP");
msleep(100);
#else
TPD_DMESG(" fts reset\n");
printk(" fts reset\n");
fts_reset_hw();
#endif
	 */
}
static int tpd_probe(struct i2c_client *client, const struct i2c_device_id *id)
{
	int retval = TPD_OK;
	char data;
	u8 report_rate=0;
	//int err=0;
	int reset_count = 0;
	unsigned char uc_reg_value;
	unsigned char uc_reg_addr;

#ifdef TPD_PROXIMITY
	int err;
	struct hwmsen_object obj_ps;
#endif

	i2c_client = client;

	//power on, need confirm with SA
	/*
#ifdef TPD_POWER_SOURCE_CUSTOM
hwPowerOn(TPD_POWER_SOURCE_CUSTOM, VOL_2800, "TP");
#else
hwPowerOn(MT65XX_POWER_LDO_VGP2, VOL_2800, "TP");
#endif

#ifdef TPD_POWER_SOURCE_1800
hwPowerOn(TPD_POWER_SOURCE_1800, VOL_1800, "TP");
#endif

#ifdef TPD_CLOSE_POWER_IN_SLEEP
hwPowerDown(TPD_POWER_SOURCE,"TP");
hwPowerOn(TPD_POWER_SOURCE,VOL_3300,"TP");
msleep(100);
#else
mt_set_gpio_mode(GPIO_CTP_RST_PIN, GPIO_CTP_RST_PIN_M_GPIO);
mt_set_gpio_dir(GPIO_CTP_RST_PIN, GPIO_DIR_OUT);
mt_set_gpio_out(GPIO_CTP_RST_PIN, GPIO_OUT_ZERO);
msleep(1);
TPD_DMESG(" fts reset\n");
printk(" fts reset\n");
mt_set_gpio_mode(GPIO_CTP_RST_PIN, GPIO_CTP_RST_PIN_M_GPIO);
mt_set_gpio_dir(GPIO_CTP_RST_PIN, GPIO_DIR_OUT);
mt_set_gpio_out(GPIO_CTP_RST_PIN, GPIO_OUT_ONE);
#endif
mt_set_gpio_mode(GPIO_CTP_EINT_PIN, GPIO_CTP_EINT_PIN_M_EINT);
mt_set_gpio_dir(GPIO_CTP_EINT_PIN, GPIO_DIR_IN);
mt_set_gpio_pull_enable(GPIO_CTP_EINT_PIN, GPIO_PULL_ENABLE);
mt_set_gpio_pull_select(GPIO_CTP_EINT_PIN, GPIO_PULL_UP);
	 */
	fts_init_gpio_hw();
	tpd_power_on();

	msg_dma_alloct(i2c_client);
	//	fts_init_gpio_hw();

	uc_reg_addr = FTS_REG_POINT_RATE;
	fts_i2c_Write(i2c_client, &uc_reg_addr, 1);
	fts_i2c_Read(i2c_client, &uc_reg_addr, 0, &uc_reg_value, 1);
	printk("mtk_tpd[FTS] report rate is %dHz.\n",uc_reg_value * 10);
	uc_reg_addr = FTS_REG_FW_VER;
	fts_i2c_Write(i2c_client, &uc_reg_addr, 1);
	fts_i2c_Read(i2c_client, &uc_reg_addr, 0, &uc_reg_value, 1);
	printk("mtk_tpd[FTS] Firmware version = 0x%x\n", uc_reg_value);
	uc_reg_addr = FTS_REG_CHIP_ID;
	fts_i2c_Write(i2c_client, &uc_reg_addr, 1);
	retval=fts_i2c_Read(i2c_client, &uc_reg_addr, 0, &uc_reg_value, 1);
	printk("mtk_tpd[FTS] chip id is %d.\n",uc_reg_value);

	if(retval<0)
	{
		printk("mtk_tpd[FTS] Read I2C error! driver NOt load!! CTP chip id is %d.\n",uc_reg_value);
		i2c_driver_need_delet = -1;

		return 0;
	}

	tpd_load_status = 1;
	mt_eint_registration(CUST_EINT_TOUCH_PANEL_NUM, EINTF_TRIGGER_FALLING, tpd_eint_interrupt_handler, 0);
	mt_eint_unmask(CUST_EINT_TOUCH_PANEL_NUM);

#ifdef VELOCITY_CUSTOM_fts
	if((err = misc_register(&tpd_misc_device)))
	{
		printk("mtk_tpd: tpd_misc_device register failed\n");
	}

#endif

	thread = kthread_run(touch_event_handler, 0, TPD_DEVICE);

	if(IS_ERR(thread))
	{
		retval = PTR_ERR(thread);
		TPD_DMESG(TPD_DEVICE " failed to create kernel thread: %d\n", retval);
		return 0;
	}

	focaltech_get_upgrade_array();
#ifdef SYSFS_DEBUG
	fts_create_sysfs(i2c_client);
#endif

#ifdef FTS_CTL_IIC
	if(ft_rw_iic_drv_init(i2c_client) < 0)
		dev_err(&client->dev, "%s:[FTS] create fts control iic driver failed\n",
				__func__);

#endif

#ifdef FTS_APK_DEBUG
	fts_create_apk_debug_channel(i2c_client);
#endif

#ifdef TPD_AUTO_UPGRADE
	printk("********************Enter CTP Auto Upgrade********************\n");
	fts_ctpm_auto_upgrade(i2c_client);
#endif

#ifdef TPD_PROXIMITY
	{
		obj_ps.polling = 1; //0--interrupt mode;1--polling mode;
		obj_ps.sensor_operate = tpd_ps_operate;

		if((err = hwmsen_attach(ID_PROXIMITY, &obj_ps)))
		{
			TPD_DEBUG("hwmsen attach fail, return:%d.", err);
		}
	}
#endif


#ifdef FTS_GESTRUE
	init_para(720,1280,60,0,0);
	input_set_capability(tpd->dev, EV_KEY, KEY_POWER);
	//	input_set_capability(tpd->dev, EV_KEY, KEY_GESTURE_U);
	input_set_capability(tpd->dev, EV_KEY, KEY_GESTURE_UP);
	input_set_capability(tpd->dev, EV_KEY, KEY_GESTURE_DOWN);
	input_set_capability(tpd->dev, EV_KEY, KEY_GESTURE_LEFT);
	input_set_capability(tpd->dev, EV_KEY, KEY_GESTURE_RIGHT);
	input_set_capability(tpd->dev, EV_KEY, KEY_GESTURE_O);
	//	input_set_capability(tpd->dev, EV_KEY, KEY_GESTURE_E);
	input_set_capability(tpd->dev, EV_KEY, KEY_GESTURE_C);
	//	input_set_capability(tpd->dev, EV_KEY, KEY_GESTURE_M);
	//	input_set_capability(tpd->dev, EV_KEY, KEY_GESTURE_L);
	//	input_set_capability(tpd->dev, EV_KEY, KEY_GESTURE_W);
	//	input_set_capability(tpd->dev, EV_KEY, KEY_GESTURE_S);
	input_set_capability(tpd->dev, EV_KEY, KEY_GESTURE_V);
	input_set_capability(tpd->dev, EV_KEY, KEY_GESTURE_Z);
	__set_bit(KEY_GESTURE_RIGHT, tpd->dev->keybit);
	__set_bit(KEY_GESTURE_LEFT, tpd->dev->keybit);
	__set_bit(KEY_GESTURE_UP, tpd->dev->keybit);
	__set_bit(KEY_GESTURE_DOWN, tpd->dev->keybit);
	//	__set_bit(KEY_GESTURE_U, tpd->dev->keybit);
	__set_bit(KEY_GESTURE_O, tpd->dev->keybit);
	//	__set_bit(KEY_GESTURE_E, tpd->dev->keybit);
	__set_bit(KEY_GESTURE_C, tpd->dev->keybit);
	//	__set_bit(KEY_GESTURE_M, tpd->dev->keybit);
	//	__set_bit(KEY_GESTURE_W, tpd->dev->keybit);
	//	__set_bit(KEY_GESTURE_L, tpd->dev->keybit);
	//	__set_bit(KEY_GESTURE_S, tpd->dev->keybit);
	__set_bit(KEY_GESTURE_V, tpd->dev->keybit);
	__set_bit(KEY_GESTURE_Z, tpd->dev->keybit);
#endif
#ifdef MT_PROTOCOL_B
	input_mt_init_slots(tpd->dev, CFG_MAX_TOUCH_POINTS,INPUT_MT_DIRECT);
	input_set_abs_params(tpd->dev, ABS_MT_TOUCH_MAJOR,0, 255, 0, 0);
	input_set_abs_params(tpd->dev, ABS_MT_POSITION_X, 0, TPD_RES_X, 0, 0);
	input_set_abs_params(tpd->dev, ABS_MT_POSITION_Y, 0, TPD_RES_Y, 0, 0);
	//	input_set_abs_params(tpd->dev, ABS_MT_PRESSURE, 0, 255, 0, 0);
#endif

	printk("fts Touch Panel Device Probe %s\n", (retval < TPD_OK) ? "FAIL" : "PASS");


	return 0;
}

static int tpd_remove(struct i2c_client *client)

{
	msg_dma_release();
#ifdef FTS_CTL_IIC
	ft_rw_iic_drv_exit();
#endif
#ifdef SYSFS_DEBUG
	fts_release_sysfs(client);
#endif
#ifdef FTS_APK_DEBUG
	fts_release_apk_debug_channel();
#endif
	TPD_DEBUG("TPD removed\n");
	return 0;
}

static int tpd_local_init(void)
{
	TPD_DMESG("Focaltech fts I2C Touchscreen Driver (Built %s @ %s)\n", __DATE__, __TIME__);

	if(i2c_add_driver(&tpd_i2c_driver)!=0)
	{
		TPD_DMESG("fts unable to add i2c driver.\n");
		return -1;
	}

	if(tpd_load_status == 0)
	{
		TPD_DMESG("fts add error touch panel driver.\n");

		if(i2c_driver_need_delet == 0)
			i2c_del_driver(&tpd_i2c_driver);

		return -1;
	}

#ifdef TPD_HAVE_BUTTON
	tpd_button_setting(TPD_KEY_COUNT, tpd_keys_local, tpd_keys_dim_local);// initialize tpd button data
#endif
#if (defined(TPD_WARP_START) && defined(TPD_WARP_END))
	TPD_DO_WARP = 1;
	memcpy(tpd_wb_start, tpd_wb_start_local, TPD_WARP_CNT*4);
	memcpy(tpd_wb_end, tpd_wb_start_local, TPD_WARP_CNT*4);
#endif
#if (defined(TPD_HAVE_CALIBRATION) && !defined(TPD_CUSTOM_CALIBRATION))
	memcpy(tpd_calmat, tpd_def_calmat_local, 8*4);
	memcpy(tpd_def_calmat, tpd_def_calmat_local, 8*4);
#endif
	TPD_DMESG("end %s, %d\n", __FUNCTION__, __LINE__);
	tpd_type_cap = 1;
	return 0;
}

static void tpd_resume(struct early_suspend *h)
{
	//returned_str = fts_get_gestureset();
	TPD_DMESG("[FTS]%c\n",returned_str[0]);
	TPD_DMESG("TPD wake up\n");
#ifdef TPD_PROXIMITY
	if(tpd_proximity_flag == 1)
	{
		if(tpd_proximity_flag_one == 1)
		{
			tpd_proximity_flag_one = 0;
			TPD_DMESG(TPD_DEVICE " tpd_proximity_flag_one \n");
			return;
		}
	}

#endif


	//#ifdef FTS_GESTRUE
	if(returned_str[0] == '1')
	{
		fts_reset_hw();

		fts_write_reg(i2c_client,0xD0,0x00);
		TPD_DMESG("TPD gesture  wake up\n");
	}
	else
		//#else
		/*
#ifdef TPD_CLOSE_POWER_IN_SLEEP
hwPowerOn(TPD_POWER_SOURCE,VOL_3300,"TP");
#else
mt_set_gpio_mode(GPIO_CTP_RST_PIN, GPIO_CTP_RST_PIN_M_GPIO);
mt_set_gpio_dir(GPIO_CTP_RST_PIN, GPIO_DIR_OUT);
mt_set_gpio_out(GPIO_CTP_RST_PIN, GPIO_OUT_ZERO);
msleep(1);
mt_set_gpio_mode(GPIO_CTP_RST_PIN, GPIO_CTP_RST_PIN_M_GPIO);
mt_set_gpio_dir(GPIO_CTP_RST_PIN, GPIO_DIR_OUT);
mt_set_gpio_out(GPIO_CTP_RST_PIN, GPIO_OUT_ONE);
#endif
		 */
		tpd_power_on();
	//#endif

	mt_eint_unmask(CUST_EINT_TOUCH_PANEL_NUM);
	msleep(30);
	tpd_halt = 0;
	TPD_DMESG("TPD wake up done\n");
}

static void tpd_suspend(struct early_suspend *h)
{
	static char data = 0x3;
	int i;
	//Get GESTURE_MODE setting
	returned_str = fts_get_gestureset();

	if(returned_str[0] == '0' )
	{
		tpd_power_down();
		mt_eint_mask(CUST_EINT_TOUCH_PANEL_NUM);
	}

	TPD_DMESG("TPD enter sleep\n");
#ifdef TPD_PROXIMITY

	if(tpd_proximity_flag == 1)
	{
		tpd_proximity_flag_one = 1;
		return;
	}

#endif

#ifdef MT_PROTOCOL_B
	if (unlikely(current_touchs)) {
		for(i = 0; i < CFG_MAX_TOUCH_POINTS; i++) {
			//type B release touch event
			if(BIT(i) & current_touchs) {
				input_mt_slot(tpd->dev, i);
				input_mt_report_slot_state(tpd->dev, MT_TOOL_FINGER, false);
			}
		}

		current_touchs = 0;

		input_report_key(tpd->dev, BTN_TOUCH, 0);
		input_sync(tpd->dev);
	}
#endif



	//#ifdef FTS_GESTRUE
	if(returned_str[0] == '1' )
	{
		fts_write_reg(i2c_client, 0xd0, 0x01);
		printk("[FTS]GESTURE_MODE ON suspend");
		if(fts_updateinfo_curr.CHIP_ID==0x54)
		{
			fts_write_reg(i2c_client, 0xd1, 0xff);
			fts_write_reg(i2c_client, 0xd2, 0xff);
			fts_write_reg(i2c_client, 0xd5, 0xff);
			fts_write_reg(i2c_client, 0xd6, 0xff);
			fts_write_reg(i2c_client, 0xd7, 0xff);
			fts_write_reg(i2c_client, 0xd8, 0xff);
		}
	}
//#else
	else
	{
		tpd_halt = 1;
		//mt_eint_mask(CUST_EINT_TOUCH_PANEL_NUM);
		//tpd_power_down();
		TPD_DMESG("TPD enter sleep done\n");
	}
/*
#ifdef TPD_CLOSE_POWER_IN_SLEEP
	hwPowerDown(TPD_POWER_SOURCE,"TP");
#else
	i2c_smbus_write_i2c_block_data(i2c_client, 0xA5, 1, &data);  //TP enter sleep mode
#endif
*/


//	TPD_DMESG("TPD enter sleep done\n");
//#endif

}


static struct tpd_driver_t tpd_device_driver =
{
	.tpd_device_name = "fts",
	.tpd_local_init = tpd_local_init,
	.suspend = tpd_suspend,
	.resume = tpd_resume,
#ifdef TPD_HAVE_BUTTON
	.tpd_have_button = 1,
#else
	.tpd_have_button = 0,
#endif
};
/* called when loaded into kernel */
static int __init tpd_driver_init(void)
{
	printk("MediaTek fts touch panel driver init\n");
	i2c_register_board_info(1, &fts_i2c_tpd, 1);

	if(tpd_driver_add(&tpd_device_driver) < 0)
		TPD_DMESG("add fts driver failed\n");

	return 0;
}

/* should never be called */
static void __exit tpd_driver_exit(void)
{
	TPD_DMESG("MediaTek fts touch panel driver exit\n");
	//input_unregister_device(tpd->dev);
	tpd_driver_remove(&tpd_device_driver);
}

module_init(tpd_driver_init);
module_exit(tpd_driver_exit);


