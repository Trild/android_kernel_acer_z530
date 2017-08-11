#include <linux/pm.h>
#include <linux/module.h>
#include <linux/proc_fs.h>
#include <linux/seq_file.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/delay.h>
#include <linux/gpio.h>
#include <linux/spinlock.h>
#include <linux/interrupt.h>
#include <linux/types.h>
#include <linux/xlog.h>

#include <asm/io.h>
#include <asm/uaccess.h>

#include "mach/irqs.h"
#include "mach/sync_write.h"
#include "mach/mt_reg_base.h"
#include "mach/mt_typedefs.h"
#include "mach/mt_spm.h"
#include "mach/mt_sleep.h"
#include "mach/mt_dcm.h"
#include "mach/mt_clkmgr.h"
#include "mach/mt_cpufreq.h"
#include "mach/mt_gpufreq.h"
#include "mach/mt_dormant.h"
#include "mach/mt_cpuidle.h"
#include "mach/mt_clkbuf_ctl.h"
#include "mach/mt_chip.h"




#define pminit_write(addr, val)         mt_reg_sync_writel((val), ((void *)(addr)))
#define pminit_read(addr)               __raw_readl(IOMEM(addr))

extern int mt_clkmgr_init(void);
extern void mt_idle_init(void);
extern void mt_power_off(void);
extern void mt_dcm_init(void);

/* HW/PROJECT ID Detection */
int cci_hw_id = 0;
int cci_rf_id = 0;
int cci_sim_id = 0;

unsigned char cci_country_code[16];

static char *cid_list[] = {
    "11111111",
    "AIS____1",
    "BGCS___1",
    "CHT____1",
    "GBS____1",
    "JPNS___1",
    "PA_____1",
    "PA_____2",
    "PA_____3",
    "PAS____1",
    "PAS____2",
    "PAS____3",
    "SUN____1",
    "TLNS__SR",
    "TMO___PL",
    "TMO___RO",
    "TMOS__HR",
    "TMOS__MK",
    "TMOS__NL",
    "WW_____1",
    "WW_____2",
    "WW_____3",
    "WW_____4",
    "WW_____5",
    "WW_____6",
    "WW_____7",
    "WWS____1",
    "WWS____2",
    "WWS____3",
    "WWS____4",
    "WWS____5",
    "WWS____6",
    "WWS____7",
};

int get_cci_hw_id(void)
{
        return cci_hw_id;
}
EXPORT_SYMBOL(get_cci_hw_id);

int get_cci_rf_id(void)
{
        return cci_rf_id;
}
EXPORT_SYMBOL(get_cci_rf_id);

int get_cci_sim_id(void)
{
        return cci_sim_id;
}
EXPORT_SYMBOL(get_cci_sim_id);
/* HW/PROJECT ID Detection */

static int __init cci_hw_id_from_cmdline(char *cci_hwid)
{
        sscanf(cci_hwid, "%d", &cci_hw_id);
        printk(KERN_ERR "Read CCI HW ID =%d from cmdline!!\n",cci_hw_id);

        return 1;
}
__setup("CCI_HW_ID=", cci_hw_id_from_cmdline);

static int __init cci_rf_id_from_cmdline(char *cci_rfid)
{
        sscanf(cci_rfid, "%d", &cci_rf_id);
        printk(KERN_ERR "Read CCI RF ID =%d from cmdline!!\n",cci_rf_id);

        return 1;
}
__setup("CCI_RF_ID=", cci_rf_id_from_cmdline);

static int __init cci_sim_id_from_cmdline(char *cci_simid)
{
        sscanf(cci_simid, "%d", &cci_sim_id);
        printk(KERN_ERR "Read CCI SIM ID =%d from cmdline!!\n",cci_sim_id);

        return 1;
}
__setup("CCI_SIM_ID=", cci_sim_id_from_cmdline);

static int __init cci_country_code_from_cmdline(char *cci_countrycode)
{
	int i, cid_support;
	char input_cci_country_code[16];

    if (cci_countrycode == NULL){
        memset(cci_country_code,0x31,8);
	    printk(KERN_ERR "CCI COUNTRY CODE from cmdline is NULL\n");
	    printk(KERN_ERR "Assign CCI_COUNTRY_CODE=11111111\n");
	    return 1;
	} else {
	    sscanf(cci_countrycode, "%s", input_cci_country_code);
	}

	for (i = 0; i < sizeof(cid_list)/sizeof(cid_list[0]); i++) {
            if (!strncmp(input_cci_country_code, cid_list[i],8)) {
                cid_support = 1;
                break;
            }
            cid_support = 0;
        }

        if (cid_support != 1){
            memset(cci_country_code,0x31,8);
	    printk(KERN_ERR "CCI COUNTRY CODE from cmdline=%s, is not in cid_list\n", input_cci_country_code);
	    printk(KERN_ERR "Assign CCI_COUNTRY_CODE=11111111\n");
        } else {
            memcpy(cci_country_code, input_cci_country_code, 8);
	    printk(KERN_ERR "Read CCI COUNTRY CODE =%s from cmdline!!\n", cci_country_code);
	}

    return 1;
}
__setup("CCI_COUNTRY_CODE=", cci_country_code_from_cmdline);

static char *hwid_string[] = {"EVT1", "DVT1", "DVT2", "DVT3", "PVT1", "MP"} ;
static char *hwid_invalid[] = {"HW_ID_INVALID"} ;
static char *rfid_string[] = {"UR30", "UR31", "UR32", "UR33", "UR34", "UR35", "UR36", "UR37"} ;
static char *rfid_invalid[] = {"RF_ID_INVALID"} ;
static char *simid_string[] = {"SIM_DS","SIM_SS"} ;
static char *simid_invalid[] = {"SIM_ID_INVALID"} ;

static const char *cci_hw_id_read(void)
{

	if (cci_hw_id >= 0 && cci_hw_id < ARRAY_SIZE(hwid_string)) {
		return hwid_string[cci_hw_id];
	}
	else {
		return hwid_invalid[0];
	}
}

static const char *cci_rf_id_read(void)
{

	if (cci_rf_id >= 0 && cci_rf_id < ARRAY_SIZE(rfid_string)) {
		return rfid_string[cci_rf_id];
	}
	else {
		return rfid_invalid[0];
	}
}

static const char *cci_sim_id_read(void)
{

	if (cci_sim_id >= 0 && cci_sim_id < ARRAY_SIZE(simid_string)) {
		return simid_string[cci_sim_id];
	}
	else {
		return simid_invalid[0];
	}
}

static const char *cci_country_code_read(void)
{
        printk(KERN_EMERG "Got an invalid Country code = %s\n", cci_country_code);

        return cci_country_code;
}

#define TOPCK_LDVT

#ifdef TOPCK_LDVT
/***************************
*For TOPCKGen Meter LDVT Test
****************************/
static unsigned int ckgen_meter(int val)
{
    int output = 0;
    int i =0;
    unsigned int temp, clk26cali_0, clk_cfg_9, clk_misc_cfg_1;

    clk26cali_0 = DRV_Reg32(CLK26CALI_0);
    DRV_WriteReg32(CLK26CALI_0, clk26cali_0 | 0x80); // enable fmeter_en

    clk_misc_cfg_1 = DRV_Reg32(CLK_MISC_CFG_1);
    DRV_WriteReg32(CLK_MISC_CFG_1, 0x00FFFFFF); // select divider

    clk_cfg_9 = DRV_Reg32(CLK_CFG_9);
    DRV_WriteReg32(CLK_CFG_9, (val << 16)); // select ckgen_cksw

    temp = DRV_Reg32(CLK26CALI_0);
    DRV_WriteReg32(CLK26CALI_0, temp | 0x10); // start fmeter

    /* wait frequency meter finish */
    while (DRV_Reg32(CLK26CALI_0) & 0x10)
    {
        mdelay(10);
        i++;
        if(i > 10)
        	break;
    }

    temp = DRV_Reg32(CLK26CALI_2) & 0xFFFF;

    output = (temp * 26000) / 1024; // Khz

    DRV_WriteReg32(CLK_CFG_9, clk_cfg_9);
    DRV_WriteReg32(CLK_MISC_CFG_1, clk_misc_cfg_1);
    DRV_WriteReg32(CLK26CALI_0, clk26cali_0);

    if(i>10)
        return 0;
    else
        return output;
}

static unsigned int abist_meter(int val)
{
    int output = 0;
    int i =0;
    unsigned int temp, clk26cali_0, clk_cfg_8, clk_misc_cfg_1;

    clk26cali_0 = DRV_Reg32(CLK26CALI_0);
    DRV_WriteReg32(CLK26CALI_0, clk26cali_0 | 0x80); // enable fmeter_en

    clk_misc_cfg_1 = DRV_Reg32(CLK_MISC_CFG_1);
    DRV_WriteReg32(CLK_MISC_CFG_1, 0xFFFFFF00); // select divider

    clk_cfg_8 = DRV_Reg32(CLK_CFG_8);
    DRV_WriteReg32(CLK_CFG_8, (val << 8)); // select abist_cksw

    temp = DRV_Reg32(CLK26CALI_0);
    DRV_WriteReg32(CLK26CALI_0, temp | 0x1); // start fmeter

    /* wait frequency meter finish */
    while (DRV_Reg32(CLK26CALI_0) & 0x1)
    {
        mdelay(10);
        i++;
        if(i > 10)
            break;
    }

    temp = DRV_Reg32(CLK26CALI_1) & 0xFFFF;

    output = (temp * 26000) / 1024; // Khz

    DRV_WriteReg32(CLK_CFG_8, clk_cfg_8);
    DRV_WriteReg32(CLK_MISC_CFG_1, clk_misc_cfg_1);
    DRV_WriteReg32(CLK26CALI_0, clk26cali_0);

    if(i>10)
        return 0;
    else
        return output;
}


#if defined(CONFIG_ARCH_MT6753)
const char *ckgen_array[] = 
{
    "hf_faxi_ck", "hd_faxi_ck", "hf_fdpi0_ck", "hf_fddrphycfg_ck", "hf_fmm_ck", 
    "f_fpwm_ck", "hf_fvdec_ck", "hf_fmfg_ck", "hf_fcamtg_ck", "f_fuart_ck", 
    "hf_fspi_ck", "f_fusb20_ck", "hf_fmsdc30_0_ck", "hf_fmsdc30_1_ck", "hf_fmsdc30_2_ck",
    "hf_faudio_ck", "hf_faud_intbus_ck", "hf_fpmicspi_ck", "f_frtc_ck", "f_f26m_ck", 
    "f_f32k_md1_ck", "f_frtc_conn_ck", "hf_fmsdc30_3_ck", "hg_fmipicfg_ck", "NULL", 
    "hd_qaxidcm_ck", "NULL", "hf_fscam_ck", "f_fckbus_scan", " f_fckrtc_scan",
    "hf_fatb_ck", "hf_faud_1_ck", "hf_faud_2_ck", "hf_fmsdc50_0_ck", "hf_firda_ck",
    " hf_firtx_ck", "hf_fdisppwm_ck", "hs_fmfg13m_ck"
};
#else
const char *ckgen_array[] = 
{
    "hf_faxi_ck", "hd_faxi_ck", "hf_fdpi0_ck", "hf_fddrphycfg_ck", "hf_fmm_ck", 
    "f_fpwm_ck", "hf_fvdec_ck", "hf_fmfg_ck", "hf_fcamtg_ck", "f_fuart_ck", 
    "hf_fspi_ck", "f_fusb20_ck", "hf_fmsdc30_0_ck", "hf_fmsdc30_1_ck", "hf_fmsdc30_2_ck",
    "hf_faudio_ck", "hf_faud_intbus_ck", "hf_fpmicspi_ck", "f_frtc_ck", "f_f26m_ck", 
    "f_f32k_md1_ck", "f_frtc_conn_ck", "f_fusb20p1_ck", "hg_fmipicfg_ck", "NULL", 
    "hd_qaxidcm_ck", "NULL", "hf_fscam_ck", "f_fckbus_scan", " f_fckrtc_scan",
    "hf_fatb_ck", "hf_faud_1_ck", "hf_faud_2_ck", "hf_fmsdc50_0_ck", "hf_firda_ck",
    " hf_firtx_ck", "hf_fdisppwm_ck", "hs_fmfg13m_ck"
};
#endif

static int ckgen_meter_read(struct seq_file *m, void *v)
{
    int i;

    for(i=1; i<39; i++)
        seq_printf(m, "%s: %d\n", ckgen_array[i-1], ckgen_meter(i));

    return 0;
}

static ssize_t ckgen_meter_write(struct file *file, const char __user *buffer,
                size_t count, loff_t *data)
{
    char desc[128];
    int len = 0;
    int val;

    len = (count < (sizeof(desc) - 1)) ? count : (sizeof(desc) - 1);
    if (copy_from_user(desc, buffer, len)) {
        return 0;
    }
    desc[len] = '\0';

    if (sscanf(desc, "%d", &val) == 1) {
        printk("ckgen_meter %d is %d\n", val, ckgen_meter(val));
    }
    return count;
}


static int abist_meter_read(struct seq_file *m, void *v)
{
	int i;

	for(i=1; i<59; i++)
    	seq_printf(m, "%d\n", abist_meter(i));

    return 0;
}
static ssize_t abist_meter_write(struct file *file, const char __user *buffer,
                size_t count, loff_t *data)
{
    char desc[128];
    int len = 0;
    int val;

    len = (count < (sizeof(desc) - 1)) ? count : (sizeof(desc) - 1);
    if (copy_from_user(desc, buffer, len)) {
        return 0;
    }
    desc[len] = '\0';

    if (sscanf(desc, "%d", &val) == 1) {
        printk("abist_meter %d is %d\n", val, abist_meter(val));
    }
    return count;
}

static int proc_abist_meter_open(struct inode *inode, struct file *file)
{
    return single_open(file, abist_meter_read, NULL);
}
static const struct file_operations abist_meter_fops = {
    .owner = THIS_MODULE,
    .open  = proc_abist_meter_open,
    .read  = seq_read,
    .write = abist_meter_write,
};

static int proc_ckgen_meter_open(struct inode *inode, struct file *file)
{
    return single_open(file, ckgen_meter_read, NULL);
}
static const struct file_operations ckgen_meter_fops = {
    .owner = THIS_MODULE,
    .open  = proc_ckgen_meter_open,
    .read  = seq_read,
    .write = ckgen_meter_write,
};

#endif

/*********************************************************************
 * FUNCTION DEFINATIONS
 ********************************************************************/

static unsigned int mt_get_emi_freq(void)
{
    int output = 0;
    int i =0;
    unsigned int temp, clk26cali_0, clk_cfg_8, clk_misc_cfg_1;

    clk26cali_0 = DRV_Reg32(CLK26CALI_0);
    DRV_WriteReg32(CLK26CALI_0, clk26cali_0 | 0x80); // enable fmeter_en

    clk_misc_cfg_1 = DRV_Reg32(CLK_MISC_CFG_1);
    DRV_WriteReg32(CLK_MISC_CFG_1, 0xFFFFFF00); // select divider

    clk_cfg_8 = DRV_Reg32(CLK_CFG_8);
    DRV_WriteReg32(CLK_CFG_8, (14 << 8)); // select abist_cksw

    temp = DRV_Reg32(CLK26CALI_0);
    DRV_WriteReg32(CLK26CALI_0, temp | 0x1); // start fmeter

    /* wait frequency meter finish */
    while (DRV_Reg32(CLK26CALI_0) & 0x1)
    {
        mdelay(10);
        i++;
        if(i > 10)
            break;
    }

    temp = DRV_Reg32(CLK26CALI_1) & 0xFFFF;

    output = (temp * 26000) / 1024; // Khz

    DRV_WriteReg32(CLK_CFG_8, clk_cfg_8);
    DRV_WriteReg32(CLK_MISC_CFG_1, clk_misc_cfg_1);
    DRV_WriteReg32(CLK26CALI_0, clk26cali_0);

    if(i>10)
        return 0;
    else
        return output;
}
EXPORT_SYMBOL(mt_get_emi_freq);

unsigned int mt_get_bus_freq(void)
{
    int output = 0;
    int i=0;
    unsigned int temp, clk26cali_0, clk_cfg_9, clk_misc_cfg_1;

    clk26cali_0 = DRV_Reg32(CLK26CALI_0);
    DRV_WriteReg32(CLK26CALI_0, clk26cali_0 | 0x80); // enable fmeter_en

    clk_misc_cfg_1 = DRV_Reg32(CLK_MISC_CFG_1);
    DRV_WriteReg32(CLK_MISC_CFG_1, 0x00FFFFFF); // select divider

    clk_cfg_9 = DRV_Reg32(CLK_CFG_9);
    DRV_WriteReg32(CLK_CFG_9, (1 << 16)); // select ckgen_cksw

    temp = DRV_Reg32(CLK26CALI_0);
    DRV_WriteReg32(CLK26CALI_0, temp | 0x10); // start fmeter

    /* wait frequency meter finish */
    while (DRV_Reg32(CLK26CALI_0) & 0x10)
    {
        udelay(10);
        i++;
        if(i > 1000)
            break;
    }

    temp = DRV_Reg32(CLK26CALI_2) & 0xFFFF;

    output = (temp * 26000) / 1024; // Khz

    DRV_WriteReg32(CLK_CFG_9, clk_cfg_9);
    DRV_WriteReg32(CLK_MISC_CFG_1, clk_misc_cfg_1);
    DRV_WriteReg32(CLK26CALI_0, clk26cali_0);

    if(i>1000)
        return 0;
    else
        return output;
}
EXPORT_SYMBOL(mt_get_bus_freq);

static unsigned int mt_get_cpu_freq(void)
{
    int output = 0;
    int i =0;
    unsigned int temp, clk26cali_0, clk_cfg_8, clk_misc_cfg_1;

    clk26cali_0 = DRV_Reg32(CLK26CALI_0);
    DRV_WriteReg32(CLK26CALI_0, clk26cali_0 | 0x80); // enable fmeter_en

    clk_misc_cfg_1 = DRV_Reg32(CLK_MISC_CFG_1);
    DRV_WriteReg32(CLK_MISC_CFG_1, 0xFFFF0300); // select divider

    clk_cfg_8 = DRV_Reg32(CLK_CFG_8);
    DRV_WriteReg32(CLK_CFG_8, (39 << 8)); // select abist_cksw

    temp = DRV_Reg32(CLK26CALI_0);
    DRV_WriteReg32(CLK26CALI_0, temp | 0x1); // start fmeter

    /* wait frequency meter finish */
    while (DRV_Reg32(CLK26CALI_0) & 0x1)
    {
        mdelay(10);
        i++;
        if(i > 10)
        	break;
    }

    temp = DRV_Reg32(CLK26CALI_1) & 0xFFFF;

    output = ((temp * 26000) / 1024) * 4; // Khz

    DRV_WriteReg32(CLK_CFG_8, clk_cfg_8);
    DRV_WriteReg32(CLK_MISC_CFG_1, clk_misc_cfg_1);
    DRV_WriteReg32(CLK26CALI_0, clk26cali_0);

    if(i>10)
        return 0;
    else
        return output;
}
EXPORT_SYMBOL(mt_get_cpu_freq);

#if 0
unsigned int mt_get_mmclk_freq(void)
{
    int output = 0;
    unsigned int temp, clk26cali_0, clk_dbg_cfg, clk_misc_cfg_0, clk26cali_1;

    clk_dbg_cfg = DRV_Reg32(CLK_DBG_CFG);
    pminit_write(CLK_DBG_CFG, 0x501); //sel ckgen_cksw and enable freq meter sel ckgen

    clk_misc_cfg_0 = DRV_Reg32(CLK_MISC_CFG_0);
    DRV_WriteReg32(CLK_MISC_CFG_0, (clk_misc_cfg_0 & 0x00FFFFFF) | (0x07 << 24)); // select divider

    clk26cali_1 = DRV_Reg32(CLK26CALI_1);
    pminit_write(CLK26CALI_1, 0x00ff0000); // 

    clk26cali_0 = DRV_Reg32(CLK26CALI_0);
    pminit_write(CLK26CALI_0, 0x1000);
    pminit_write(CLK26CALI_0, 0x1010);

    /* wait frequency meter finish */
    while (DRV_Reg32(CLK26CALI_0) & 0x10)
    {
        printk("wait for frequency meter finish, CLK26CALI = 0x%x\n", DRV_Reg32(CLK26CALI_0));
        //mdelay(10);
    }

    temp = DRV_Reg32(CLK26CALI_1) & 0xFFFF;

    output = (((temp * 26000) ) / 256)*8; // Khz

    pminit_write(CLK_DBG_CFG, clk_dbg_cfg);
    pminit_write(CLK_MISC_CFG_0, clk_misc_cfg_0);
    pminit_write(CLK26CALI_0, clk26cali_0);
    pminit_write(CLK26CALI_1, clk26cali_1);

    printk("CLK26CALI = 0x%x, bus frequency = %d Khz\n", temp, output);

    return output;
}
EXPORT_SYMBOL(mt_get_mmclk_freq);

unsigned int mt_get_mfgclk_freq(void)
{
    int output = 0;
    unsigned int temp, clk26cali_0, clk_dbg_cfg, clk_misc_cfg_0, clk26cali_1;

    clk_dbg_cfg = DRV_Reg32(CLK_DBG_CFG);
    pminit_write(CLK_DBG_CFG, 0x1801); //sel ckgen_cksw and enable freq meter sel ckgen

    clk_misc_cfg_0 = DRV_Reg32(CLK_MISC_CFG_0);
    DRV_WriteReg32(CLK_MISC_CFG_0, (clk_misc_cfg_0 & 0x00FFFFFF) | (0x07 << 24)); // select divider

    clk26cali_1 = DRV_Reg32(CLK26CALI_1);
    pminit_write(CLK26CALI_1, 0x00ff0000); // 

    clk26cali_0 = DRV_Reg32(CLK26CALI_0);
    pminit_write(CLK26CALI_0, 0x1000);
    pminit_write(CLK26CALI_0, 0x1010);

    /* wait frequency meter finish */
    while (DRV_Reg32(CLK26CALI_0) & 0x10)
    {
        printk("wait for frequency meter finish, CLK26CALI = 0x%x\n", DRV_Reg32(CLK26CALI_0));
        //mdelay(10);
    }

    temp = DRV_Reg32(CLK26CALI_1) & 0xFFFF;

    output = (((temp * 26000) ) / 256)*8; // Khz

    pminit_write(CLK_DBG_CFG, clk_dbg_cfg);
    pminit_write(CLK_MISC_CFG_0, clk_misc_cfg_0);
    pminit_write(CLK26CALI_0, clk26cali_0);
    pminit_write(CLK26CALI_1, clk26cali_1);

    //print("CLK26CALI = 0x%x, bus frequency = %d Khz\n", temp, output);

    return output;
}
EXPORT_SYMBOL(mt_get_mfgclk_freq);
#endif

static int cpu_speed_dump_read(struct seq_file *m, void *v)
{
    seq_printf(m, "%d\n", mt_get_cpu_freq());
    return 0;
}

//static int bigcpu_speed_dump_read(struct seq_file *m, void *v)
//{
//    seq_printf(m, "%d\n", mt_get_bigcpu_freq());
//    return 0;
//}

static int emi_speed_dump_read(struct seq_file *m, void *v)
{
    seq_printf(m, "%d\n", mt_get_emi_freq());
    return 0;
}

static int bus_speed_dump_read(struct seq_file *m, void *v)
{
    seq_printf(m, "%d\n", mt_get_bus_freq());
    return 0;
}

#if 0
static int mmclk_speed_dump_read(struct seq_file *m, void *v)
{
    seq_printf(m, "%d\n", mt_get_mmclk_freq());
    return 0;
}

static int mfgclk_speed_dump_read(struct seq_file *m, void *v)
{
    seq_printf(m, "%d\n", mt_get_mfgclk_freq());
    return 0;
}
#endif

static int proc_cpu_open(struct inode *inode, struct file *file)
{
    return single_open(file, cpu_speed_dump_read, NULL);
}
static const struct file_operations cpu_fops = {
    .owner = THIS_MODULE,
    .open  = proc_cpu_open,
    .read  = seq_read,
};

//static int proc_bigcpu_open(struct inode *inode, struct file *file)
//{
//    return single_open(file, bigcpu_speed_dump_read, NULL);
//}
//static const struct file_operations bigcpu_fops = {
//    .owner = THIS_MODULE,
//    .open  = proc_bigcpu_open,
//    .read  = seq_read,
//};

static int proc_emi_open(struct inode *inode, struct file *file)
{
    return single_open(file, emi_speed_dump_read, NULL);
}
static const struct file_operations emi_fops = {
    .owner = THIS_MODULE,
    .open  = proc_emi_open,
    .read  = seq_read,
};

static int proc_bus_open(struct inode *inode, struct file *file)
{
    return single_open(file, bus_speed_dump_read, NULL);
}
static const struct file_operations bus_fops = {
    .owner = THIS_MODULE,
    .open  = proc_bus_open,
    .read  = seq_read,
};

#if 0
static int proc_mmclk_open(struct inode *inode, struct file *file)
{
    return single_open(file, mmclk_speed_dump_read, NULL);
}
static const struct file_operations mmclk_fops = {
    .owner = THIS_MODULE,
    .open  = proc_mmclk_open,
    .read  = seq_read,
};

static int proc_mfgclk_open(struct inode *inode, struct file *file)
{
    return single_open(file, mfgclk_speed_dump_read, NULL);
}
static const struct file_operations mfgclk_fops = {
    .owner = THIS_MODULE,
    .open  = proc_mfgclk_open,
    .read  = seq_read,
};
#endif


static int hwid_dump_read(struct seq_file *m, void *v)
{
    seq_printf(m, "%s\n", cci_hw_id_read());
    return 0;
}

static int proc_hwid_open(struct inode *inode, struct file *file)
{
    return single_open(file, hwid_dump_read, NULL);
}

static const struct file_operations hwid_fops = {
    .owner = THIS_MODULE,
    .open  = proc_hwid_open,
    .read  = seq_read,
};

static int rfid_dump_read(struct seq_file *m, void *v)
{
    seq_printf(m, "%s\n", cci_rf_id_read());
    return 0;
}

static int proc_rfid_open(struct inode *inode, struct file *file)
{
    return single_open(file, rfid_dump_read, NULL);
}

static const struct file_operations rfid_fops = {
    .owner = THIS_MODULE,
    .open  = proc_rfid_open,
    .read  = seq_read,
};

static int simid_dump_read(struct seq_file *m, void *v)
{
    seq_printf(m, "%s\n", cci_sim_id_read());
    return 0;
}

static int proc_simid_open(struct inode *inode, struct file *file)
{
    return single_open(file, simid_dump_read, NULL);
}

static const struct file_operations simid_fops = {
    .owner = THIS_MODULE,
    .open  = proc_simid_open,
    .read  = seq_read,
};

static int countrycode_dump_read(struct seq_file *m, void *v)
{
    seq_printf(m, "%s\n", cci_country_code_read());
    return 0;
}

static int proc_countrycode_open(struct inode *inode, struct file *file)
{
    return single_open(file, countrycode_dump_read, NULL);
}

static const struct file_operations countrycode_fops = {
    .owner = THIS_MODULE,
    .open  = proc_countrycode_open,
    .read  = seq_read,
};

static int __init mt_power_management_init(void)
{
    struct proc_dir_entry *entry = NULL;
    struct proc_dir_entry *pm_init_dir = NULL;
    unsigned int code = mt_get_chip_hw_code();

/* HW/PROJECT ID Detection */
	entry = proc_create("CCI_HW_ID", S_IRUGO, NULL, &hwid_fops);
	entry = proc_create("CCI_RF_ID", S_IRUGO, NULL, &rfid_fops);
	entry = proc_create("CCI_SIM_ID", S_IRUGO, NULL, &simid_fops);
/* HW/PROJECT ID Detection */
    entry = proc_create("CCI_COUNTRY_CODE", S_IRUGO, NULL, &countrycode_fops);


    pm_power_off = mt_power_off;

    #if !defined (CONFIG_MTK_FPGA)
     //FIXME: for FPGA early porting
    //printk(ANDROID_LOG_INFO, "Power/PM_INIT", "Bus Frequency = %d KHz\n", mt_get_bus_freq());

    //cpu dormant driver init
    mt_cpu_dormant_init();

    // SPM driver init
    spm_module_init();

    // Sleep driver init (for suspend)
    if (0x321 == code) {
       slp_module_init();
    } else if (0x335 == code) {
       slp_module_init();
    } else if (0x337 == code){
       slp_module_init();
    } else { 
       // unknown chip ID, error !!
    }


    mt_clkmgr_init();

    //mt_pm_log_init(); // power management log init

    //FIXME: for FPGA early porting

//    mt_dcm_init(); // dynamic clock management init


    pm_init_dir = proc_mkdir("pm_init", NULL);
    //pm_init_dir = proc_mkdir("pm_init", NULL);
    if (!pm_init_dir)
    {
        pr_err("[%s]: mkdir /proc/pm_init failed\n", __FUNCTION__);
    }
    else
    {
        entry = proc_create("cpu_speed_dump", S_IRUGO, pm_init_dir, &cpu_fops);

        //entry = proc_create("bigcpu_speed_dump", S_IRUGO, pm_init_dir, &bigcpu_fops);

        entry = proc_create("emi_speed_dump", S_IRUGO, pm_init_dir, &emi_fops);

        entry = proc_create("bus_speed_dump", S_IRUGO, pm_init_dir, &bus_fops);

        //entry = proc_create("mmclk_speed_dump", S_IRUGO, pm_init_dir, &mmclk_fops);

        //entry = proc_create("mfgclk_speed_dump", S_IRUGO, pm_init_dir, &mfgclk_fops);
#ifdef TOPCK_LDVT
        entry = proc_create("abist_meter_test", S_IRUGO|S_IWUSR, pm_init_dir, &abist_meter_fops);
        entry = proc_create("ckgen_meter_test", S_IRUGO|S_IWUSR, pm_init_dir, &ckgen_meter_fops);
#endif
    }

    #endif

    return 0;
}

arch_initcall(mt_power_management_init);


#if !defined (MT_DORMANT_UT)
static int __init mt_pm_late_init(void)
{
#ifndef CONFIG_MTK_FPGA
	mt_idle_init();
	clk_buf_init();
#endif
	return 0;
}

late_initcall(mt_pm_late_init);
#endif //#if !defined (MT_DORMANT_UT)


MODULE_DESCRIPTION("MTK Power Management Init Driver");
MODULE_LICENSE("GPL");
