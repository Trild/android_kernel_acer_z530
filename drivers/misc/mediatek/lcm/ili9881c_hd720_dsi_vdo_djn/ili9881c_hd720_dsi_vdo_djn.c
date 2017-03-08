#ifndef BUILD_LK
#include <linux/string.h>
#endif
#include "lcm_drv.h"

#ifdef BUILD_LK
	#include <platform/mt_gpio.h>
        #include <platform/mt_i2c.h>
#elif defined(BUILD_UBOOT)
	#include <asm/arch/mt_gpio.h>
#else
	#include <mach/mt_gpio.h>
#endif

// ---------------------------------------------------------------------------
//  Local Constants
// ---------------------------------------------------------------------------

#define FRAME_WIDTH	    (720)
#define FRAME_HEIGHT	    (1280)
#define PHYSICAL_WIDTH	    (62)
#define PHYSICAL_HEIGHT	    (110)

//#define LCM_ID			(0x69)
//#define LCM_ID_R63315_TIANMA		(0x90)
#define REGFLAG_DELAY			0XFE
#define REGFLAG_END_OF_TABLE		0XFD   // END OF REGISTERS MARKER


// ---------------------------------------------------------------------------
//  Local Variables
// ---------------------------------------------------------------------------

static LCM_UTIL_FUNCS lcm_util = {0};

#define SET_RESET_PIN(v)	(lcm_util.set_reset_pin((v)))
#define SET_GPIO_OUT(n, v)	(lcm_util.set_gpio_out((n), (v)))
#define UDELAY(n)		(lcm_util.udelay(n))
#define MDELAY(n)		(lcm_util.mdelay(n))


// ---------------------------------------------------------------------------
//  Local Functions
// ---------------------------------------------------------------------------

#define dsi_set_cmdq_V2(cmd, count, ppara, force_update)	lcm_util.dsi_set_cmdq_V2(cmd, count, ppara, force_update)
#define dsi_set_cmdq(pdata, queue_size, force_update)		lcm_util.dsi_set_cmdq(pdata, queue_size, force_update)
#define wrtie_cmd(cmd)						lcm_util.dsi_write_cmd(cmd)
#define write_regs(addr, pdata, byte_nums)			lcm_util.dsi_write_regs(addr, pdata, byte_nums)
#define read_reg(cmd)						lcm_util.dsi_dcs_read_lcm_reg(cmd)
#define read_reg_v2(cmd, buffer, buffer_size)			lcm_util.dsi_dcs_read_lcm_reg_v2(cmd, buffer, buffer_size)


//#define   LCM_DSI_CMD_MODE							1


struct LCM_setting_table {
    unsigned char cmd;
    unsigned char count;
    unsigned char para_list[64];
};

static struct LCM_setting_table lcm_initialization_setting[] =
{
//CMD_PAGE 3
	{0xFF,3,{0x98,0x81,0x03}},

//GIP_1
	{0x01,1,{0x00}},
	{0x02,1,{0x00}},
	{0x03,1,{0x72}},
	{0x04,1,{0x00}},
	{0x05,1,{0x00}},
	{0x06,1,{0x09}},
	{0x07,1,{0x00}},
	{0x08,1,{0x00}},
	{0x09,1,{0x01}},
	{0x0A,1,{0x00}},
	{0x0B,1,{0x00}},
	{0x0C,1,{0x01}},
	{0x0D,1,{0x00}},
	{0x0E,1,{0x00}},
	{0x0F,1,{0x00}},
	{0x10,1,{0x00}},
	{0x11,1,{0x00}},
	{0x12,1,{0x00}},
	{0x13,1,{0x00}},
	{0x14,1,{0x00}},
	{0x15,1,{0x00}},
	{0x16,1,{0x00}},
	{0x17,1,{0x00}},
	{0x18,1,{0x00}},
	{0x19,1,{0x00}},
	{0x1A,1,{0x00}},
	{0x1B,1,{0x00}},
	{0x1C,1,{0x00}},
	{0x1D,1,{0x00}},
	{0x1E,1,{0x40}},
	{0x1F,1,{0x80}},
	{0x20,1,{0x05}},
	{0x21,1,{0x02}},
	{0x22,1,{0x00}},
	{0x23,1,{0x00}},
	{0x24,1,{0x00}},
	{0x25,1,{0x00}},
	{0x26,1,{0x00}},
	{0x27,1,{0x00}},
	{0x28,1,{0x33}},
	{0x29,1,{0x02}},
	{0x2A,1,{0x00}},
	{0x2B,1,{0x00}},
	{0x2C,1,{0x00}},
	{0x2D,1,{0x00}},
	{0x2E,1,{0x00}},
	{0x2F,1,{0x00}},
	{0x30,1,{0x00}},
	{0x31,1,{0x00}},
	{0x32,1,{0x00}},
	{0x33,1,{0x00}},
	{0x34,1,{0x04}},
	{0x35,1,{0x00}},
	{0x36,1,{0x00}},
	{0x37,1,{0x00}},
	{0x38,1,{0x3C}},
	{0x39,1,{0x00}},
	{0x3A,1,{0x40}},
	{0x3B,1,{0x40}},
	{0x3C,1,{0x00}},
	{0x3D,1,{0x00}},
	{0x3E,1,{0x00}},
	{0x3F,1,{0x00}},
	{0x40,1,{0x00}},
	{0x41,1,{0x00}},
	{0x42,1,{0x00}},
	{0x43,1,{0x00}},
	{0x44,1,{0x00}},

//GIP_2
	{0x50,1,{0x01}},
	{0x51,1,{0x23}},
	{0x52,1,{0x45}},
	{0x53,1,{0x67}},
	{0x54,1,{0x89}},
	{0x55,1,{0xAB}},
	{0x56,1,{0x01}},
	{0x57,1,{0x23}},
	{0x58,1,{0x45}},
	{0x59,1,{0x67}},
	{0x5A,1,{0x89}},
	{0x5B,1,{0xAB}},
	{0x5C,1,{0xCD}},
	{0x5D,1,{0xEF}},

//GIP_3
	{0x5E,1,{0x11}},
	{0x5F,1,{0x01}},
	{0x60,1,{0x00}},
	{0x61,1,{0x15}},
	{0x62,1,{0x14}},
	{0x63,1,{0x0E}},
	{0x64,1,{0x0F}},
	{0x65,1,{0x0C}},
	{0x66,1,{0x0D}},
	{0x67,1,{0x06}},
	{0x68,1,{0x02}},
	{0x69,1,{0x07}},
	{0x6A,1,{0x02}},
	{0x6B,1,{0x02}},
	{0x6C,1,{0x02}},
	{0x6D,1,{0x02}},
	{0x6E,1,{0x02}},
	{0x6F,1,{0x02}},
	{0x70,1,{0x02}},
	{0x71,1,{0x02}},
	{0x72,1,{0x02}},
	{0x73,1,{0x02}},
	{0x74,1,{0x02}},
	{0x75,1,{0x01}},
	{0x76,1,{0x00}},
	{0x77,1,{0x14}},
	{0x78,1,{0x15}},
	{0x79,1,{0x0E}},
	{0x7A,1,{0x0F}},
	{0x7B,1,{0x0C}},
	{0x7C,1,{0x0D}},
	{0x7D,1,{0x06}},
	{0x7E,1,{0x02}},
	{0x7F,1,{0x07}},
	{0x80,1,{0x02}},
	{0x81,1,{0x02}},
	{0x82,1,{0x02}},
	{0x83,1,{0x02}},
	{0x84,1,{0x02}},
	{0x85,1,{0x02}},
	{0x86,1,{0x02}},
	{0x87,1,{0x02}},
	{0x88,1,{0x02}},
	{0x89,1,{0x02}},
	{0x8A,1,{0x02}},

//CMD_PAGE 4
	{0xFF,3,{0x98,0x81,0x04}},
	{0x00,1,{0x80}},               ///3 lane     80峈侐籵耋
	{0x6C,1,{0x15}},                //SEt VCORE voltAgE =1.5V
	{0x6E,1,{0x2A}},                //Di_pwr_rEg=0 For powEr moDE 2A //VGH ClAmp 15V
	{0x6F,1,{0x33}},                // rEg vCl + pumping rAtio VGH=3x VGL=-2.5x
	{0x3A,1,{0x94}},                //POWER SAVING
	{0x8D,1,{0x1A}},               //VGL ClAmp -11V
	{0x87,1,{0xBA}},               //ESD
	{0x26,1,{0x76}},
	{0xB2,1,{0xD1}},
	{0xB5,1,{0x06}},



//CMD_PAGE 1
	{0xFF,3,{0x98,0x81,0x01}},
	{0x22,1,{0x0A}},	//BGR,0x SS
	{0x31,1,{0x00}},	//Column invErsion
	{0x53,1,{0x8C}},	//VCOM1
	{0x55,1,{0x8F}},	//VCOM2
	{0x50,1,{0xC0}},	//VREG1OUT=5V
	{0x51,1,{0xC0}},	//VREG2OUT=-5V
	{0x60,1,{0x08}},               //SDT

	{0xA0,1,{0x08}},	//VP255	GAmmA P
	{0xA1,1,{0x19}},  //VP251
	{0xA2,1,{0x26}},  //VP247
	{0xA3,1,{0x1A}},  //VP243
	{0xA4,1,{0x1D}},  //VP239
	{0xA5,1,{0x2C}},  //VP231
	{0xA6,1,{0x21}},  //VP219
	{0xA7,1,{0x22}},  //VP203
	{0xA8,1,{0x7C}},  //VP175
	{0xA9,1,{0x21}},  //VP144
	{0xAA,1,{0x2E}},  //VP111
	{0xAB,1,{0x66}},  //VP80
	{0xAC,1,{0x1C}},  //VP52
	{0xAD,1,{0x18}},  //VP36
	{0xAE,1,{0x4E}},  //VP24
	{0xAF,1,{0x1A}},  //VP16
	{0xB0,1,{0x22}},  //VP12
	{0xB1,1,{0x49}},  //VP8
	{0xB2,1,{0x56}},  //VP4
	{0xB3,1,{0x39}},  //VP0

	{0xC0,1,{0x08}},  //VN255 GAMMA N
	{0xC1,1,{0x1A}},  //VN251
	{0xC2,1,{0x26}},  //VN247
	{0xC3,1,{0x0B}},  //VN243
	{0xC4,1,{0x0E}},  //VN239
	{0xC5,1,{0x24}},  //VN231
	{0xC6,1,{0x18}},  //VN219
	{0xC7,1,{0x1B}},  //VN203
	{0xC8,1,{0x85}},  //VN175
	{0xC9,1,{0x17}},  //VN144
	{0xCA,1,{0x23}},  //VN111
	{0xCB,1,{0x79}},  //VN80
	{0xCC,1,{0x1C}},  //VN52
	{0xCD,1,{0x1F}},  //VN36
	{0xCE,1,{0x50}},  //VN24
	{0xCF,1,{0x2D}},  //VN16
	{0xD0,1,{0x31}},  //VN12
	{0xD1,1,{0x49}},  //VN8
	{0xD2,1,{0x57}},  //VN4
	{0xD3,1,{0x39}},  //VN0

//CMD_PAGE 0
	{0xFF,3,{0x98,0x81,0x00}},
	{REGFLAG_END_OF_TABLE, 0x00, {}}
};


static struct LCM_setting_table lcm_sleep_out_setting[] = {
	// TE on
	{0x35, 1, {0x00}},
	// Sleep Out
	{0x11, 1, {0x00}},
        {REGFLAG_DELAY, 120, {}},
	// Display ON
	{0x29, 1, {0x00}},
	{REGFLAG_DELAY, 10, {}},

	{REGFLAG_END_OF_TABLE, 0x00, {}}
};


static struct LCM_setting_table lcm_deep_sleep_mode_in_setting[] = {
	// Display off sequence
	{0x28, 1, {0x00}},
        {REGFLAG_DELAY, 10, {}},

	 // Sleep Mode On
	 {0x10, 1, {0x00}},
         {REGFLAG_DELAY, 120, {}},

	 {REGFLAG_END_OF_TABLE, 0x00, {}}
};

static void push_table(struct LCM_setting_table *table, unsigned int count, unsigned char force_update)
{
	unsigned int i;

    for(i = 0; i < count; i++) {

        unsigned cmd;
        cmd = table[i].cmd;

        switch (cmd) {

            case REGFLAG_DELAY :
                MDELAY(table[i].count);
                break;

            case REGFLAG_END_OF_TABLE :
                break;

            default:
				dsi_set_cmdq_V2(cmd, table[i].count, table[i].para_list, force_update);
       	}

    }

}

// ---------------------------------------------------------------------------
//  LCM Driver Implementations
// ---------------------------------------------------------------------------

static void lcm_set_util_funcs(const LCM_UTIL_FUNCS *util)
{
    memcpy(&lcm_util, util, sizeof(LCM_UTIL_FUNCS));
}


static void lcm_get_params(LCM_PARAMS *params)
{

	memset(params, 0, sizeof(LCM_PARAMS));

	params->type   = LCM_TYPE_DSI;

	params->width  = FRAME_WIDTH;
	params->height = FRAME_HEIGHT;

	params->physical_height = PHYSICAL_HEIGHT;
	params->physical_width = PHYSICAL_WIDTH;
#if (LCM_DSI_CMD_MODE)
	params->dsi.mode   = CMD_MODE;
#else
	params->dsi.mode   = BURST_VDO_MODE;
#endif

	// DSI
	/* Command mode setting */
	//1 Three lane or Four lane
	params->dsi.LANE_NUM				= LCM_FOUR_LANE;
	//The following defined the fomat for data coming from LCD engine.
	params->dsi.data_format.color_order = LCM_COLOR_ORDER_RGB;
	params->dsi.data_format.trans_seq   = LCM_DSI_TRANS_SEQ_MSB_FIRST;
	params->dsi.data_format.padding     = LCM_DSI_PADDING_ON_LSB;
	params->dsi.data_format.format      = LCM_DSI_FORMAT_RGB888;

	// Highly depends on LCD driver capability.
	// Not support in MT6573
	params->dsi.packet_size=256;

	// ESD recovery settings
	params->dsi.esd_check_enable = 1;
	params->dsi.customization_esd_check_enable = 1;
	params->dsi.lcm_esd_check_table[0].cmd = 0x0a;
	params->dsi.lcm_esd_check_table[0].count = 1;
	params->dsi.lcm_esd_check_table[0].para_list[0] = 0x9c;

	// Video mode setting
	params->dsi.intermediat_buffer_num = 0;//because DSI/DPI HW design change, this parameters should be 0 when video mode in MT658X; or memory leakage

	params->dsi.PS=LCM_PACKED_PS_24BIT_RGB888;
	params->dsi.word_count=1080*3;


	params->dsi.vertical_sync_active				= 16;
	params->dsi.vertical_backporch					= 18;
	params->dsi.vertical_frontporch					= 30;
	params->dsi.vertical_active_line				= FRAME_HEIGHT;

	params->dsi.horizontal_sync_active				= 100;
	params->dsi.horizontal_backporch				= 160;
	params->dsi.horizontal_frontporch				= 112;
	params->dsi.horizontal_active_pixel				= FRAME_WIDTH;

        params->dsi.HS_TRAIL = 15;

	// Bit rate calculation
	//1 Every lane speed (MHz)
	params->dsi.PLL_CLOCK = 275;

	params->dsi.ssc_disable = 1;
}

static void lcm_init(void)
{
	lcm_util.set_gpio_mode(GPIO_VCC_LCM_EN, GPIO_MODE_00);
	lcm_util.set_gpio_dir(GPIO_VCC_LCM_EN, GPIO_DIR_OUT);
	lcm_util.set_gpio_pull_enable(GPIO_VCC_LCM_EN, GPIO_PULL_DISABLE);
	SET_GPIO_OUT(GPIO_VCC_LCM_EN, 1);

        #ifdef BUILD_LK
		printf("%s, LK ili9881c_djn debug: lcm_init()\n", __func__);
        #else
		printk("%s, kernel ili9881c_djn debug: lcm_init()\n", __func__);
        #endif

        MDELAY(5);

        // Set reset pin to high
	SET_RESET_PIN(1);
        MDELAY(20);

        // Set reset pin to low
	SET_RESET_PIN(0);
        //SET_GPIO_OUT(GPIO_LCM_RST, 0);
        MDELAY(20);

        // Set reset pin to high
	SET_RESET_PIN(1);
        //SET_GPIO_OUT(GPIO_LCM_RST, 1);
	MDELAY(100);

	push_table(lcm_initialization_setting, sizeof(lcm_initialization_setting) / sizeof(struct LCM_setting_table), 1);
	push_table(lcm_sleep_out_setting, sizeof(lcm_sleep_out_setting) / sizeof(struct LCM_setting_table), 1);
}

static void lcm_suspend(void)
{
        #ifdef BUILD_LK
		printf("%s, LK r63315_tianma debug: lcm_suspend()\n", __func__);
        #else
		printk("%s, kernel r63315_tianma horse debug: lcm_suspend()\n", __func__);
        #endif

	push_table(lcm_deep_sleep_mode_in_setting, sizeof(lcm_deep_sleep_mode_in_setting) / sizeof(struct LCM_setting_table), 1);
}


static void lcm_resume(void)
{
        #ifdef BUILD_LK
		printf("%s, LK r63315_tianma debug: lcm_resume()\n", __func__);
        #else
		printk("%s, kernel r63315_tianma horse debug: lcm_resume()\n", __func__);
        #endif

	push_table(lcm_sleep_out_setting, sizeof(lcm_sleep_out_setting) / sizeof(struct LCM_setting_table), 1);
}


#if (LCM_DSI_CMD_MODE)
static void lcm_update(unsigned int x, unsigned int y,
                       unsigned int width, unsigned int height)
{
	unsigned int x0 = x;
	unsigned int y0 = y;
	unsigned int x1 = x0 + width - 1;
	unsigned int y1 = y0 + height - 1;

	unsigned char x0_MSB = ((x0>>8)&0xFF);
	unsigned char x0_LSB = (x0&0xFF);
	unsigned char x1_MSB = ((x1>>8)&0xFF);
	unsigned char x1_LSB = (x1&0xFF);
	unsigned char y0_MSB = ((y0>>8)&0xFF);
	unsigned char y0_LSB = (y0&0xFF);
	unsigned char y1_MSB = ((y1>>8)&0xFF);
	unsigned char y1_LSB = (y1&0xFF);

	unsigned int data_array[16];

	data_array[0]= 0x00053902;
	data_array[1]= (x1_MSB<<24)|(x0_LSB<<16)|(x0_MSB<<8)|0x2a;
	data_array[2]= (x1_LSB);
	dsi_set_cmdq(data_array, 3, 1);

	data_array[0]= 0x00053902;
	data_array[1]= (y1_MSB<<24)|(y0_LSB<<16)|(y0_MSB<<8)|0x2b;
	data_array[2]= (y1_LSB);
	dsi_set_cmdq(data_array, 3, 1);

	data_array[0]= 0x002c3909;
	dsi_set_cmdq(data_array, 1, 0);

}
#endif
/*
static unsigned int lcm_compare_id(void)
{
	unsigned int id=0;
	unsigned char buffer[2];
	unsigned int array[16];

	SET_RESET_PIN(1);
	SET_RESET_PIN(0);
	MDELAY(1);

	SET_RESET_PIN(1);
	MDELAY(20);

	array[0] = 0x00023700;// read id return two byte,version and id
	dsi_set_cmdq(array, 1, 1);

	read_reg_v2(0xF4, buffer, 2);
	id = buffer[0]; //we only need ID
    #ifdef BUILD_LK
		printf("%s, LK r63315_tianma debug: r63315_tianma id = 0x%08x\n", __func__, id);
    #else
		printk("%s, kernel r63315_tianma horse debug: r63315_tianma id = 0x%08x\n", __func__, id);
    #endif

    if(id == LCM_ID_R63315_TIANMA)
    	return 1;
    else
        return 0;

}
*/

LCM_DRIVER ili9881c_hd720_dsi_vdo_djn_lcm_drv =
{
	.name			= "ili9881c_hd720_dsi_vdo_djn",
	.set_util_funcs = lcm_set_util_funcs,
	.get_params     = lcm_get_params,
	.init           = lcm_init,
	.suspend        = lcm_suspend,
	.resume         = lcm_resume,
	//.compare_id     = lcm_compare_id,
#if (LCM_DSI_CMD_MODE)
	.update         = lcm_update,
#endif
};
