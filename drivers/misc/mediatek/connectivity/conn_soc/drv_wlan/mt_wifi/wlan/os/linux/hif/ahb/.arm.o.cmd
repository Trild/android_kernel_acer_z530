cmd_drivers/misc/mediatek/connectivity/conn_soc/drv_wlan/mt_wifi/wlan/os/linux/hif/ahb/arm.o := /home/necoman51/linaro-4.9/bin/arm-eabi-gcc -Wp,-MD,drivers/misc/mediatek/connectivity/conn_soc/drv_wlan/mt_wifi/wlan/os/linux/hif/ahb/.arm.o.d  -nostdinc -isystem /home/necoman51/linaro-4.9/bin/../lib/gcc/arm-eabi/4.9.4/include -I/home/necoman51/kernel/arch/arm/include -Iarch/arm/include/generated  -Iinclude -I/home/necoman51/kernel/arch/arm/include/uapi -Iarch/arm/include/generated/uapi -I/home/necoman51/kernel/include/uapi -Iinclude/generated/uapi -include /home/necoman51/kernel/include/linux/kconfig.h -D__KERNEL__ -mlittle-endian -I/home/necoman51/kernel/drivers/misc/mediatek/mach/mt6735/include -Wall -Wundef -Wstrict-prototypes -Wno-trigraphs -fno-strict-aliasing -fno-common -Werror-implicit-function-declaration -Wno-format-security -fno-delete-null-pointer-checks -Werror=format -Werror=int-to-pointer-cast -Werror=pointer-to-int-cast -O2 -fno-dwarf2-cfi-asm -fno-omit-frame-pointer -mapcs -mno-sched-prolog -fstack-protector -mabi=aapcs-linux -mno-thumb-interwork -marm -D__LINUX_ARM_ARCH__=7 -march=armv7-a -msoft-float -Uarm -Wframe-larger-than=1400 -Wno-unused-but-set-variable -fno-omit-frame-pointer -fno-optimize-sibling-calls -fno-var-tracking-assignments -g -Wdeclaration-after-statement -Wno-pointer-sign -fno-strict-overflow -fconserve-stack -DCC_HAVE_ASM_GOTO -I/home/necoman51/kernel/drivers/misc/mediatek/mach/mt6735/include -D WMT_IDC_SUPPORT=1 -I/home/necoman51/kernel/drivers/misc/mediatek/mach/mt6735/include -D MTK_WCN_WMT_STP_EXP_SYMBOL_ABSTRACT -D MTK_WCN_REMOVE_KERNEL_MODULE -DLINUX -DMT6628 -DCFG_SUPPORT_AGPS_ASSIST=1 -DCFG_SUPPORT_TSF_USING_BOOTTIME=1 -DCFG_P2P_LEGACY_COEX_REVISE=1 -DCFG_SUPPORT_WAPI=1 -DCFG_SUPPORT_MCC=1 -DCFG_SUPPORT_XLOG=1 -DCFG_SUPPORT_AEE=1 -DCFG_SUPPORT_HOTSPOT_2_0=1 -DCFG_HS20_DEBUG=1 -DCFG_ENABLE_GTK_FRAME_FILTER=1 -DCFG_SUPPORT_MET_PROFILING=1 -DCFG_TC1_FEATURE=0 -DCFG_SRAM_SIZE_OPTION=1 -D_HIF_SDIO=1 -DDBG=0 -Idrivers/misc/mediatek/connectivity/conn_soc/drv_wlan/mt_wifi/wlan/os -Idrivers/misc/mediatek/connectivity/conn_soc/drv_wlan/mt_wifi/wlan/os/linux/include -Idrivers/misc/mediatek/connectivity/conn_soc/drv_wlan/mt_wifi/wlan/os/linux/hif/ahb/include -Idrivers/misc/mediatek/connectivity/conn_soc/drv_wlan/mt_wifi/wlan/include -Idrivers/misc/mediatek/connectivity/conn_soc/drv_wlan/mt_wifi/wlan/include/nic -Idrivers/misc/mediatek/connectivity/conn_soc/drv_wlan/mt_wifi/wlan/include/mgmt -I/home/necoman51/kernel/drivers/misc/mediatek/mach/mt6735/include -I/home/necoman51/kernel/drivers/misc/mediatek/mach/mt6735/include/mach -I/home/necoman51/kernel/drivers/misc/mediatek/mach/mt6735/cci6735_35u_l1/accdet -I/home/necoman51/kernel/drivers/misc/mediatek/mach/mt6735/cci6735_35u_l1/core -I/home/necoman51/kernel/drivers/misc/mediatek/mach/mt6735/cci6735_35u_l1/camera/camera -I/home/necoman51/kernel/drivers/misc/mediatek/mach/mt6735/cci6735_35u_l1/common -I/home/necoman51/kernel/drivers/misc/mediatek/mach/mt6735/cci6735_35u_l1/dct/dct -I/home/necoman51/kernel/drivers/misc/mediatek/mach/mt6735/cci6735_35u_l1/hdmi -I/home/necoman51/kernel/drivers/misc/mediatek/mach/mt6735/cci6735_35u_l1/imgsensor/inc -I/home/necoman51/kernel/drivers/misc/mediatek/mach/mt6735/cci6735_35u_l1/keypad -I/home/necoman51/kernel/drivers/misc/mediatek/mach/mt6735/cci6735_35u_l1/leds/mt65xx -I/home/necoman51/kernel/drivers/misc/mediatek/mach/mt6735/cci6735_35u_l1/power -I/home/necoman51/kernel/drivers/misc/mediatek/mach/mt6735/cci6735_35u_l1/rtc -I/home/necoman51/kernel/drivers/misc/mediatek/mach/mt6735/cci6735_35u_l1/sound/inc -I/home/necoman51/kernel/drivers/misc/mediatek/mach/mt6735/cci6735_35u_l1/touchpanel/ft5336 -I/home/necoman51/kernel/drivers/misc/mediatek/mach/mt6735/cci6735_35u_l1/vibrator -I/home/necoman51/kernel/drivers/misc/mediatek/mach/mt6735/cci6735_35u_l1/nand -I/home/necoman51/kernel/drivers/misc/mediatek/mach/mt6735/cci6735_35u_l1/dct/dct/inc -I/home/necoman51/kernel/drivers/misc/mediatek/accdet/mt6735 -I/home/necoman51/kernel/drivers/misc/mediatek/accelerometer/inc -I/home/necoman51/kernel/drivers/misc/mediatek/alsps/inc -I/home/necoman51/kernel/drivers/misc/mediatek/hdmi/inc -I/home/necoman51/kernel/drivers/misc/mediatek/barometer/inc -I/home/necoman51/kernel/drivers/misc/mediatek/auxadc/mt6735 -I/home/necoman51/kernel/drivers/misc/mediatek/cam_cal/inc -I/home/necoman51/kernel/drivers/misc/mediatek/camera/mt6735 -I/home/necoman51/kernel/drivers/misc/mediatek/cmdq/mt6735 -I/home/necoman51/kernel/drivers/misc/mediatek/devinfo/mt6735 -I/home/necoman51/kernel/drivers/misc/mediatek/dispsys/mt6735 -I/home/necoman51/kernel/drivers/misc/mediatek/dual_ccci/mt6735/include -I/home/necoman51/kernel/drivers/misc/mediatek/dual_ccci/include -I/home/necoman51/kernel/drivers/misc/mediatek/flashlight/inc -I/home/necoman51/kernel/drivers/misc/mediatek/hall/ -I/home/necoman51/kernel/drivers/misc/mediatek/gyroscope/inc -I/home/necoman51/kernel/drivers/misc/mediatek/step_counter -I/home/necoman51/kernel/drivers/misc/mediatek/pedometer -I/home/necoman51/kernel/drivers/misc/mediatek/activity_sensor -I/home/necoman51/kernel/drivers/misc/mediatek/in_pocket_sensor -I/home/necoman51/kernel/drivers/misc/mediatek/face_down_sensor -I/home/necoman51/kernel/drivers/misc/mediatek/pick_up_sensor -I/home/necoman51/kernel/drivers/misc/mediatek/shake_sensor -I/home/necoman51/kernel/drivers/misc/mediatek/heart_rate_sensor -I/home/necoman51/kernel/drivers/misc/mediatek/tilt_detector_sensor -I/home/necoman51/kernel/drivers/misc/mediatek/wake_gesture_sensor -I/home/necoman51/kernel/drivers/misc/mediatek/glance_gesture_sensor -I/home/necoman51/kernel/drivers/misc/mediatek/i2c/mt6735 -I/home/necoman51/kernel/drivers/misc/mediatek/imgsensor/inc -I/home/necoman51/kernel/drivers/misc/mediatek/eeprom/inc -I/home/necoman51/kernel/drivers/misc/mediatek/leds/mt6735 -I/home/necoman51/kernel/drivers/misc/mediatek/lens/inc -I/home/necoman51/kernel/drivers/misc/mediatek/magnetometer/inc -I/home/necoman51/kernel/drivers/misc/mediatek/met/platform/mt6735 -I/home/necoman51/kernel/drivers/misc/mediatek/met/mt6735 -I/home/necoman51/kernel/drivers/misc/mediatek/sensorHub/inc -I/home/necoman51/kernel/drivers/misc/mediatek/smi/mt6735 -I/home/necoman51/kernel/drivers/misc/mediatek/ssw/inc -I/home/necoman51/kernel/drivers/misc/mediatek/sync -I/home/necoman51/kernel/drivers/misc/mediatek/uart/mt6735 -I/home/necoman51/kernel/drivers/misc/mediatek/vibrator/mt6735 -I/home/necoman51/kernel/drivers/misc/mediatek/video/mt6735 -I/home/necoman51/kernel/drivers/misc/mediatek/video -I/home/necoman51/kernel/drivers/misc/mediatek/wdk -I/home/necoman51/kernel/drivers/misc/mediatek/mjc/mt6735 -I/home/necoman51/kernel/drivers/misc/mediatek/lcm -I/home/necoman51/kernel/drivers/misc/mediatek/lcm/inc -I/home/necoman51/kernel/drivers/misc/mediatek/multibridge/mt6735/mt8193/inc -I/home/necoman51/kernel/drivers/misc/mediatek/dum-char/mt6735 -I/home/necoman51/kernel/drivers/misc/mediatek/lens/mt6735/inc -DCONSTANT_FLASHLIGHT -DILI9881C_HD720_DSI_VDO_DJN -DOV8858_MIPI_RAW -DOV8858S_MIPI_RAW -I/home/necoman51/kernel/PTGEN/inc -I/home/necoman51/kernel/drivers/misc/mediatek/ptgen/mt6735 -I/home/necoman51/kernel/drivers/misc/mediatek/m4u/mt6735/mt6735/    -D"KBUILD_STR(s)=\#s" -D"KBUILD_BASENAME=KBUILD_STR(arm)"  -D"KBUILD_MODNAME=KBUILD_STR(wlan_mt)" -c -o drivers/misc/mediatek/connectivity/conn_soc/drv_wlan/mt_wifi/wlan/os/linux/hif/ahb/arm.o drivers/misc/mediatek/connectivity/conn_soc/drv_wlan/mt_wifi/wlan/os/linux/hif/ahb/arm.c

source_drivers/misc/mediatek/connectivity/conn_soc/drv_wlan/mt_wifi/wlan/os/linux/hif/ahb/arm.o := drivers/misc/mediatek/connectivity/conn_soc/drv_wlan/mt_wifi/wlan/os/linux/hif/ahb/arm.c

deps_drivers/misc/mediatek/connectivity/conn_soc/drv_wlan/mt_wifi/wlan/os/linux/hif/ahb/arm.o := \

drivers/misc/mediatek/connectivity/conn_soc/drv_wlan/mt_wifi/wlan/os/linux/hif/ahb/arm.o: $(deps_drivers/misc/mediatek/connectivity/conn_soc/drv_wlan/mt_wifi/wlan/os/linux/hif/ahb/arm.o)

$(deps_drivers/misc/mediatek/connectivity/conn_soc/drv_wlan/mt_wifi/wlan/os/linux/hif/ahb/arm.o):