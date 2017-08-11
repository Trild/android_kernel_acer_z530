cmd_drivers/power/mediatek/linear_charging.o := /home/necoman51/linaro-4.9/bin/arm-eabi-gcc -Wp,-MD,drivers/power/mediatek/.linear_charging.o.d  -nostdinc -isystem /home/necoman51/linaro-4.9/bin/../lib/gcc/arm-eabi/4.9.4/include -I/home/necoman51/kernel/arch/arm/include -Iarch/arm/include/generated  -Iinclude -I/home/necoman51/kernel/arch/arm/include/uapi -Iarch/arm/include/generated/uapi -I/home/necoman51/kernel/include/uapi -Iinclude/generated/uapi -include /home/necoman51/kernel/include/linux/kconfig.h -D__KERNEL__ -mlittle-endian -I/home/necoman51/kernel/drivers/misc/mediatek/mach/mt6735/include -Wall -Wundef -Wstrict-prototypes -Wno-trigraphs -fno-strict-aliasing -fno-common -Werror-implicit-function-declaration -Wno-format-security -fno-delete-null-pointer-checks -Werror=format -Werror=int-to-pointer-cast -Werror=pointer-to-int-cast -O2 -fno-dwarf2-cfi-asm -fno-omit-frame-pointer -mapcs -mno-sched-prolog -fstack-protector -mabi=aapcs-linux -mno-thumb-interwork -marm -D__LINUX_ARM_ARCH__=7 -march=armv7-a -msoft-float -Uarm -Wframe-larger-than=1400 -Wno-unused-but-set-variable -fno-omit-frame-pointer -fno-optimize-sibling-calls -fno-var-tracking-assignments -g -Wdeclaration-after-statement -Wno-pointer-sign -fno-strict-overflow -fconserve-stack -DCC_HAVE_ASM_GOTO -I/home/necoman51/kernel/drivers/misc/mediatek/mach/mt6735/include -I/home/necoman51/kernel/drivers/misc/mediatek/mach/mt6735/include/mach -I/home/necoman51/kernel/drivers/misc/mediatek/mach/mt6735/cci6735_35u_l1/accdet -I/home/necoman51/kernel/drivers/misc/mediatek/mach/mt6735/cci6735_35u_l1/core -I/home/necoman51/kernel/drivers/misc/mediatek/mach/mt6735/cci6735_35u_l1/camera/camera -I/home/necoman51/kernel/drivers/misc/mediatek/mach/mt6735/cci6735_35u_l1/common -I/home/necoman51/kernel/drivers/misc/mediatek/mach/mt6735/cci6735_35u_l1/dct/dct -I/home/necoman51/kernel/drivers/misc/mediatek/mach/mt6735/cci6735_35u_l1/hdmi -I/home/necoman51/kernel/drivers/misc/mediatek/mach/mt6735/cci6735_35u_l1/imgsensor/inc -I/home/necoman51/kernel/drivers/misc/mediatek/mach/mt6735/cci6735_35u_l1/keypad -I/home/necoman51/kernel/drivers/misc/mediatek/mach/mt6735/cci6735_35u_l1/leds/mt65xx -I/home/necoman51/kernel/drivers/misc/mediatek/mach/mt6735/cci6735_35u_l1/power -I/home/necoman51/kernel/drivers/misc/mediatek/mach/mt6735/cci6735_35u_l1/rtc -I/home/necoman51/kernel/drivers/misc/mediatek/mach/mt6735/cci6735_35u_l1/sound/inc -I/home/necoman51/kernel/drivers/misc/mediatek/mach/mt6735/cci6735_35u_l1/touchpanel/ft5336 -I/home/necoman51/kernel/drivers/misc/mediatek/mach/mt6735/cci6735_35u_l1/vibrator -I/home/necoman51/kernel/drivers/misc/mediatek/mach/mt6735/cci6735_35u_l1/nand -I/home/necoman51/kernel/drivers/misc/mediatek/mach/mt6735/cci6735_35u_l1/dct/dct/inc -I/home/necoman51/kernel/drivers/misc/mediatek/accdet/mt6735 -I/home/necoman51/kernel/drivers/misc/mediatek/accelerometer/inc -I/home/necoman51/kernel/drivers/misc/mediatek/alsps/inc -I/home/necoman51/kernel/drivers/misc/mediatek/hdmi/inc -I/home/necoman51/kernel/drivers/misc/mediatek/barometer/inc -I/home/necoman51/kernel/drivers/misc/mediatek/auxadc/mt6735 -I/home/necoman51/kernel/drivers/misc/mediatek/cam_cal/inc -I/home/necoman51/kernel/drivers/misc/mediatek/camera/mt6735 -I/home/necoman51/kernel/drivers/misc/mediatek/cmdq/mt6735 -I/home/necoman51/kernel/drivers/misc/mediatek/devinfo/mt6735 -I/home/necoman51/kernel/drivers/misc/mediatek/dispsys/mt6735 -I/home/necoman51/kernel/drivers/misc/mediatek/dual_ccci/mt6735/include -I/home/necoman51/kernel/drivers/misc/mediatek/dual_ccci/include -I/home/necoman51/kernel/drivers/misc/mediatek/flashlight/inc -I/home/necoman51/kernel/drivers/misc/mediatek/hall/ -I/home/necoman51/kernel/drivers/misc/mediatek/gyroscope/inc -I/home/necoman51/kernel/drivers/misc/mediatek/step_counter -I/home/necoman51/kernel/drivers/misc/mediatek/pedometer -I/home/necoman51/kernel/drivers/misc/mediatek/activity_sensor -I/home/necoman51/kernel/drivers/misc/mediatek/in_pocket_sensor -I/home/necoman51/kernel/drivers/misc/mediatek/face_down_sensor -I/home/necoman51/kernel/drivers/misc/mediatek/pick_up_sensor -I/home/necoman51/kernel/drivers/misc/mediatek/shake_sensor -I/home/necoman51/kernel/drivers/misc/mediatek/heart_rate_sensor -I/home/necoman51/kernel/drivers/misc/mediatek/tilt_detector_sensor -I/home/necoman51/kernel/drivers/misc/mediatek/wake_gesture_sensor -I/home/necoman51/kernel/drivers/misc/mediatek/glance_gesture_sensor -I/home/necoman51/kernel/drivers/misc/mediatek/i2c/mt6735 -I/home/necoman51/kernel/drivers/misc/mediatek/imgsensor/inc -I/home/necoman51/kernel/drivers/misc/mediatek/eeprom/inc -I/home/necoman51/kernel/drivers/misc/mediatek/leds/mt6735 -I/home/necoman51/kernel/drivers/misc/mediatek/lens/inc -I/home/necoman51/kernel/drivers/misc/mediatek/magnetometer/inc -I/home/necoman51/kernel/drivers/misc/mediatek/met/platform/mt6735 -I/home/necoman51/kernel/drivers/misc/mediatek/met/mt6735 -I/home/necoman51/kernel/drivers/misc/mediatek/sensorHub/inc -I/home/necoman51/kernel/drivers/misc/mediatek/smi/mt6735 -I/home/necoman51/kernel/drivers/misc/mediatek/ssw/inc -I/home/necoman51/kernel/drivers/misc/mediatek/sync -I/home/necoman51/kernel/drivers/misc/mediatek/uart/mt6735 -I/home/necoman51/kernel/drivers/misc/mediatek/vibrator/mt6735 -I/home/necoman51/kernel/drivers/misc/mediatek/video/mt6735 -I/home/necoman51/kernel/drivers/misc/mediatek/video -I/home/necoman51/kernel/drivers/misc/mediatek/wdk -I/home/necoman51/kernel/drivers/misc/mediatek/mjc/mt6735 -I/home/necoman51/kernel/drivers/misc/mediatek/lcm -I/home/necoman51/kernel/drivers/misc/mediatek/lcm/inc -I/home/necoman51/kernel/drivers/misc/mediatek/multibridge/mt6735/mt8193/inc -I/home/necoman51/kernel/drivers/misc/mediatek/dum-char/mt6735 -I/home/necoman51/kernel/drivers/misc/mediatek/lens/mt6735/inc -DCONSTANT_FLASHLIGHT -DILI9881C_HD720_DSI_VDO_DJN -DOV8858_MIPI_RAW -DOV8858S_MIPI_RAW -I/home/necoman51/kernel/PTGEN/inc -I/home/necoman51/kernel/drivers/misc/mediatek/ptgen/mt6735 -I/home/necoman51/kernel/drivers/misc/mediatek/m4u/mt6735/mt6735/    -D"KBUILD_STR(s)=\#s" -D"KBUILD_BASENAME=KBUILD_STR(linear_charging)"  -D"KBUILD_MODNAME=KBUILD_STR(linear_charging)" -c -o drivers/power/mediatek/linear_charging.o drivers/power/mediatek/linear_charging.c

source_drivers/power/mediatek/linear_charging.o := drivers/power/mediatek/linear_charging.c

deps_drivers/power/mediatek/linear_charging.o := \
    $(wildcard include/config/mtk/pump/express/support.h) \
    $(wildcard include/config/mtk/jeita/standard/support.h) \
    $(wildcard include/config/power/ext.h) \
    $(wildcard include/config/usb/if.h) \
  include/linux/kernel.h \
    $(wildcard include/config/lbdaf.h) \
    $(wildcard include/config/preempt/voluntary.h) \
    $(wildcard include/config/debug/atomic/sleep.h) \
    $(wildcard include/config/prove/locking.h) \
    $(wildcard include/config/ring/buffer.h) \
    $(wildcard include/config/tracing.h) \
    $(wildcard include/config/ftrace/mcount/record.h) \
  /home/necoman51/linaro-4.9/lib/gcc/arm-eabi/4.9.4/include/stdarg.h \
  include/linux/linkage.h \
  include/linux/compiler.h \
    $(wildcard include/config/sparse/rcu/pointer.h) \
    $(wildcard include/config/trace/branch/profiling.h) \
    $(wildcard include/config/profile/all/branches.h) \
    $(wildcard include/config/enable/must/check.h) \
    $(wildcard include/config/enable/warn/deprecated.h) \
    $(wildcard include/config/kprobes.h) \
  include/linux/compiler-gcc.h \
    $(wildcard include/config/arch/supports/optimized/inlining.h) \
    $(wildcard include/config/optimize/inlining.h) \
  include/linux/compiler-gcc4.h \
    $(wildcard include/config/arch/use/builtin/bswap.h) \
  include/linux/stringify.h \
  include/linux/export.h \
    $(wildcard include/config/have/underscore/symbol/prefix.h) \
    $(wildcard include/config/modules.h) \
    $(wildcard include/config/modversions.h) \
    $(wildcard include/config/unused/symbols.h) \
  /home/necoman51/kernel/arch/arm/include/asm/linkage.h \
  include/linux/stddef.h \
  include/uapi/linux/stddef.h \
  include/linux/types.h \
    $(wildcard include/config/uid16.h) \
    $(wildcard include/config/arch/dma/addr/t/64bit.h) \
    $(wildcard include/config/phys/addr/t/64bit.h) \
    $(wildcard include/config/64bit.h) \
  include/uapi/linux/types.h \
  arch/arm/include/generated/asm/types.h \
  /home/necoman51/kernel/include/uapi/asm-generic/types.h \
  include/asm-generic/int-ll64.h \
  include/uapi/asm-generic/int-ll64.h \
  arch/arm/include/generated/asm/bitsperlong.h \
  include/asm-generic/bitsperlong.h \
  include/uapi/asm-generic/bitsperlong.h \
  /home/necoman51/kernel/include/uapi/linux/posix_types.h \
  /home/necoman51/kernel/arch/arm/include/uapi/asm/posix_types.h \
  /home/necoman51/kernel/include/uapi/asm-generic/posix_types.h \
  include/linux/bitops.h \
  /home/necoman51/kernel/arch/arm/include/asm/bitops.h \
    $(wildcard include/config/smp.h) \
  include/linux/irqflags.h \
    $(wildcard include/config/trace/irqflags.h) \
    $(wildcard include/config/preempt/monitor.h) \
    $(wildcard include/config/irqsoff/tracer.h) \
    $(wildcard include/config/preempt/tracer.h) \
    $(wildcard include/config/trace/irqflags/support.h) \
  include/linux/typecheck.h \
  /home/necoman51/kernel/arch/arm/include/asm/irqflags.h \
  /home/necoman51/kernel/arch/arm/include/asm/ptrace.h \
    $(wildcard include/config/arm/thumb.h) \
  /home/necoman51/kernel/arch/arm/include/uapi/asm/ptrace.h \
    $(wildcard include/config/cpu/endian/be8.h) \
  /home/necoman51/kernel/arch/arm/include/asm/hwcap.h \
  /home/necoman51/kernel/arch/arm/include/uapi/asm/hwcap.h \
  include/asm-generic/bitops/non-atomic.h \
  include/asm-generic/bitops/fls64.h \
  include/asm-generic/bitops/sched.h \
  include/asm-generic/bitops/hweight.h \
  include/asm-generic/bitops/arch_hweight.h \
  include/asm-generic/bitops/const_hweight.h \
  include/asm-generic/bitops/lock.h \
  include/asm-generic/bitops/le.h \
  /home/necoman51/kernel/arch/arm/include/uapi/asm/byteorder.h \
  include/linux/byteorder/little_endian.h \
  include/uapi/linux/byteorder/little_endian.h \
  include/linux/swab.h \
  include/uapi/linux/swab.h \
  /home/necoman51/kernel/arch/arm/include/asm/swab.h \
  /home/necoman51/kernel/arch/arm/include/uapi/asm/swab.h \
  include/linux/byteorder/generic.h \
  include/asm-generic/bitops/ext2-atomic-setbit.h \
  include/linux/log2.h \
    $(wildcard include/config/arch/has/ilog2/u32.h) \
    $(wildcard include/config/arch/has/ilog2/u64.h) \
  include/linux/printk.h \
    $(wildcard include/config/early/printk.h) \
    $(wildcard include/config/printk.h) \
    $(wildcard include/config/dynamic/debug.h) \
  include/linux/init.h \
    $(wildcard include/config/broken/rodata.h) \
  include/linux/kern_levels.h \
  include/linux/dynamic_debug.h \
  include/uapi/linux/kernel.h \
  /home/necoman51/kernel/include/uapi/linux/sysinfo.h \
  /home/necoman51/kernel/arch/arm/include/asm/div64.h \
  /home/necoman51/kernel/arch/arm/include/asm/compiler.h \
  /home/necoman51/kernel/arch/arm/include/asm/bug.h \
    $(wildcard include/config/bug.h) \
    $(wildcard include/config/thumb2/kernel.h) \
    $(wildcard include/config/debug/bugverbose.h) \
    $(wildcard include/config/arm/lpae.h) \
  /home/necoman51/kernel/arch/arm/include/asm/opcodes.h \
    $(wildcard include/config/cpu/endian/be32.h) \
  include/asm-generic/bug.h \
    $(wildcard include/config/generic/bug.h) \
    $(wildcard include/config/generic/bug/relative/pointers.h) \
  include/mach/battery_common.h \
    $(wildcard include/config/mtk/fan5405/support.h) \
    $(wildcard include/config/mtk/bq24158/support.h) \
    $(wildcard include/config/mtk/pump/express/plus/support.h) \
    $(wildcard include/config/mtk/smart/battery.h) \
    $(wildcard include/config/mtk/power/ext/detect.h) \
  /home/necoman51/kernel/include/uapi/linux/ioctl.h \
  arch/arm/include/generated/asm/ioctl.h \
  include/asm-generic/ioctl.h \
  include/uapi/asm-generic/ioctl.h \
  /home/necoman51/kernel/drivers/misc/mediatek/mach/mt6735/include/mach/mt_typedefs.h \
  include/linux/bug.h \
  include/mach/charging.h \
  /home/necoman51/kernel/drivers/misc/mediatek/mach/mt6735/cci6735_35u_l1/power/cust_charging.h \
    $(wildcard include/config/mtk/disable/power/on/off/voltage/limitation.h) \
    $(wildcard include/config/dis/check/battery.h) \
  include/mach/charging.h \
  /home/necoman51/kernel/drivers/misc/mediatek/mach/mt6735/include/mach/mt_boot.h \
  include/mach/mt_boot_common.h \
    $(wildcard include/config/mtk/kernel/power/off/charging.h) \
  include/mach/mt_boot_reason.h \
  /home/necoman51/kernel/drivers/misc/mediatek/mach/mt6735/include/mach/mt_chip.h \
  include/mach/mt_chip_common.h \
  include/linux/delay.h \
  /home/necoman51/kernel/arch/arm/include/asm/delay.h \
  /home/necoman51/kernel/arch/arm/include/asm/memory.h \
    $(wildcard include/config/need/mach/memory/h.h) \
    $(wildcard include/config/mmu.h) \
    $(wildcard include/config/page/offset.h) \
    $(wildcard include/config/highmem.h) \
    $(wildcard include/config/dram/size.h) \
    $(wildcard include/config/dram/base.h) \
    $(wildcard include/config/have/tcm.h) \
    $(wildcard include/config/arm/patch/phys/virt.h) \
    $(wildcard include/config/phys/offset.h) \
    $(wildcard include/config/virt/to/bus.h) \
  /home/necoman51/kernel/include/uapi/linux/const.h \
  include/linux/sizes.h \
  /home/necoman51/kernel/drivers/misc/mediatek/mach/mt6735/include/mach/memory.h \
  include/asm-generic/memory_model.h \
    $(wildcard include/config/flatmem.h) \
    $(wildcard include/config/discontigmem.h) \
    $(wildcard include/config/sparsemem/vmemmap.h) \
    $(wildcard include/config/sparsemem.h) \
  arch/arm/include/generated/asm/param.h \
  include/asm-generic/param.h \
    $(wildcard include/config/hz.h) \
  include/uapi/asm-generic/param.h \
  include/mach/battery_meter.h \
  /home/necoman51/kernel/drivers/misc/mediatek/mach/mt6735/cci6735_35u_l1/power/cust_battery_meter.h \
    $(wildcard include/config/mtk/hafg/20.h) \
  include/linux/mutex.h \
    $(wildcard include/config/debug/mutexes.h) \
    $(wildcard include/config/mutex/spin/on/owner.h) \
    $(wildcard include/config/debug/lock/alloc.h) \
    $(wildcard include/config/mt/debug/mutexes.h) \
    $(wildcard include/config/have/arch/mutex/cpu/relax.h) \
  include/linux/list.h \
    $(wildcard include/config/debug/list.h) \
  include/linux/poison.h \
    $(wildcard include/config/illegal/pointer/value.h) \
  include/linux/spinlock_types.h \
    $(wildcard include/config/generic/lockbreak.h) \
    $(wildcard include/config/debug/spinlock.h) \
  /home/necoman51/kernel/arch/arm/include/asm/spinlock_types.h \
  include/linux/lockdep.h \
    $(wildcard include/config/lockdep.h) \
    $(wildcard include/config/lock/stat.h) \
    $(wildcard include/config/prove/rcu.h) \
  include/linux/rwlock_types.h \
  include/linux/atomic.h \
    $(wildcard include/config/arch/has/atomic/or.h) \
    $(wildcard include/config/generic/atomic64.h) \
  /home/necoman51/kernel/arch/arm/include/asm/atomic.h \
  /home/necoman51/kernel/arch/arm/include/asm/barrier.h \
    $(wildcard include/config/cpu/32v6k.h) \
    $(wildcard include/config/cpu/xsc3.h) \
    $(wildcard include/config/cpu/fa526.h) \
    $(wildcard include/config/arch/has/barriers.h) \
    $(wildcard include/config/arm/dma/mem/bufferable.h) \
  /home/necoman51/kernel/arch/arm/include/asm/outercache.h \
    $(wildcard include/config/outer/cache/sync.h) \
    $(wildcard include/config/outer/cache.h) \
  /home/necoman51/kernel/arch/arm/include/asm/cmpxchg.h \
    $(wildcard include/config/cpu/sa1100.h) \
    $(wildcard include/config/cpu/sa110.h) \
    $(wildcard include/config/cpu/v6.h) \
  include/asm-generic/cmpxchg-local.h \
  include/asm-generic/atomic-long.h \
  include/linux/wakelock.h \
  include/linux/ktime.h \
    $(wildcard include/config/ktime/scalar.h) \
  include/linux/time.h \
    $(wildcard include/config/arch/uses/gettimeoffset.h) \
  include/linux/cache.h \
    $(wildcard include/config/arch/has/cache/line/size.h) \
  /home/necoman51/kernel/arch/arm/include/asm/cache.h \
    $(wildcard include/config/arm/l1/cache/shift.h) \
    $(wildcard include/config/aeabi.h) \
  include/linux/seqlock.h \
  include/linux/spinlock.h \
    $(wildcard include/config/preempt.h) \
  include/linux/preempt.h \
    $(wildcard include/config/debug/preempt.h) \
    $(wildcard include/config/context/tracking.h) \
    $(wildcard include/config/preempt/count.h) \
    $(wildcard include/config/preempt/notifiers.h) \
  include/linux/thread_info.h \
    $(wildcard include/config/compat.h) \
    $(wildcard include/config/debug/stack/usage.h) \
  /home/necoman51/kernel/arch/arm/include/asm/thread_info.h \
    $(wildcard include/config/crunch.h) \
    $(wildcard include/config/arm/thumbee.h) \
    $(wildcard include/config/mt/rt/sched.h) \
  /home/necoman51/kernel/arch/arm/include/asm/fpstate.h \
    $(wildcard include/config/vfpv3.h) \
    $(wildcard include/config/iwmmxt.h) \
  /home/necoman51/kernel/arch/arm/include/asm/domain.h \
    $(wildcard include/config/io/36.h) \
    $(wildcard include/config/cpu/use/domains.h) \
  include/linux/bottom_half.h \
  /home/necoman51/kernel/arch/arm/include/asm/spinlock.h \
  /home/necoman51/kernel/arch/arm/include/asm/processor.h \
    $(wildcard include/config/have/hw/breakpoint.h) \
    $(wildcard include/config/arm/errata/754327.h) \
  /home/necoman51/kernel/arch/arm/include/asm/hw_breakpoint.h \
  include/linux/rwlock.h \
  include/linux/spinlock_api_smp.h \
    $(wildcard include/config/inline/spin/lock.h) \
    $(wildcard include/config/inline/spin/lock/bh.h) \
    $(wildcard include/config/inline/spin/lock/irq.h) \
    $(wildcard include/config/inline/spin/lock/irqsave.h) \
    $(wildcard include/config/inline/spin/trylock.h) \
    $(wildcard include/config/inline/spin/trylock/bh.h) \
    $(wildcard include/config/uninline/spin/unlock.h) \
    $(wildcard include/config/inline/spin/unlock/bh.h) \
    $(wildcard include/config/inline/spin/unlock/irq.h) \
    $(wildcard include/config/inline/spin/unlock/irqrestore.h) \
  include/linux/rwlock_api_smp.h \
    $(wildcard include/config/inline/read/lock.h) \
    $(wildcard include/config/inline/write/lock.h) \
    $(wildcard include/config/inline/read/lock/bh.h) \
    $(wildcard include/config/inline/write/lock/bh.h) \
    $(wildcard include/config/inline/read/lock/irq.h) \
    $(wildcard include/config/inline/write/lock/irq.h) \
    $(wildcard include/config/inline/read/lock/irqsave.h) \
    $(wildcard include/config/inline/write/lock/irqsave.h) \
    $(wildcard include/config/inline/read/trylock.h) \
    $(wildcard include/config/inline/write/trylock.h) \
    $(wildcard include/config/inline/read/unlock.h) \
    $(wildcard include/config/inline/write/unlock.h) \
    $(wildcard include/config/inline/read/unlock/bh.h) \
    $(wildcard include/config/inline/write/unlock/bh.h) \
    $(wildcard include/config/inline/read/unlock/irq.h) \
    $(wildcard include/config/inline/write/unlock/irq.h) \
    $(wildcard include/config/inline/read/unlock/irqrestore.h) \
    $(wildcard include/config/inline/write/unlock/irqrestore.h) \
  include/linux/math64.h \
  include/uapi/linux/time.h \
  include/linux/jiffies.h \
  include/linux/timex.h \
  include/uapi/linux/timex.h \
  /home/necoman51/kernel/include/uapi/linux/param.h \
  /home/necoman51/kernel/arch/arm/include/asm/timex.h \
    $(wildcard include/config/arch/multiplatform.h) \
  /home/necoman51/kernel/drivers/misc/mediatek/mach/mt6735/include/mach/timex.h \
  include/linux/device.h \
    $(wildcard include/config/debug/devres.h) \
    $(wildcard include/config/acpi.h) \
    $(wildcard include/config/pinctrl.h) \
    $(wildcard include/config/numa.h) \
    $(wildcard include/config/cma.h) \
    $(wildcard include/config/pm/sleep.h) \
    $(wildcard include/config/devtmpfs.h) \
    $(wildcard include/config/sysfs/deprecated.h) \
  include/linux/ioport.h \
    $(wildcard include/config/memory/hotremove.h) \
  include/linux/kobject.h \
  include/linux/sysfs.h \
    $(wildcard include/config/sysfs.h) \
  include/linux/errno.h \
  include/uapi/linux/errno.h \
  arch/arm/include/generated/asm/errno.h \
  /home/necoman51/kernel/include/uapi/asm-generic/errno.h \
  /home/necoman51/kernel/include/uapi/asm-generic/errno-base.h \
  include/linux/kobject_ns.h \
  include/linux/kref.h \
  include/linux/wait.h \
  arch/arm/include/generated/asm/current.h \
  include/asm-generic/current.h \
  include/uapi/linux/wait.h \
  include/linux/klist.h \
  include/linux/pinctrl/devinfo.h \
  include/linux/pm.h \
    $(wildcard include/config/vt/console/sleep.h) \
    $(wildcard include/config/pm.h) \
    $(wildcard include/config/pm/runtime.h) \
    $(wildcard include/config/pm/clk.h) \
    $(wildcard include/config/pm/generic/domains.h) \
  include/linux/workqueue.h \
    $(wildcard include/config/debug/objects/work.h) \
    $(wildcard include/config/freezer.h) \
  include/linux/timer.h \
    $(wildcard include/config/timer/stats.h) \
    $(wildcard include/config/debug/objects/timers.h) \
  include/linux/debugobjects.h \
    $(wildcard include/config/debug/objects.h) \
    $(wildcard include/config/debug/objects/free.h) \
  include/linux/threads.h \
    $(wildcard include/config/nr/cpus.h) \
    $(wildcard include/config/base/small.h) \
  include/linux/cpumask.h \
    $(wildcard include/config/cpumask/offstack.h) \
    $(wildcard include/config/hotplug/cpu.h) \
    $(wildcard include/config/debug/per/cpu/maps.h) \
    $(wildcard include/config/disable/obsolete/cpumask/functions.h) \
  include/linux/bitmap.h \
  include/linux/string.h \
    $(wildcard include/config/binary/printf.h) \
  include/uapi/linux/string.h \
  /home/necoman51/kernel/arch/arm/include/asm/string.h \
  include/linux/completion.h \
  include/linux/ratelimit.h \
  include/linux/uidgid.h \
    $(wildcard include/config/uidgid/strict/type/checks.h) \
    $(wildcard include/config/user/ns.h) \
  include/linux/highuid.h \
  /home/necoman51/kernel/arch/arm/include/asm/device.h \
    $(wildcard include/config/dmabounce.h) \
    $(wildcard include/config/iommu/api.h) \
    $(wildcard include/config/arm/dma/use/iommu.h) \
    $(wildcard include/config/arch/omap.h) \
  include/linux/pm_wakeup.h \

drivers/power/mediatek/linear_charging.o: $(deps_drivers/power/mediatek/linear_charging.o)

$(deps_drivers/power/mediatek/linear_charging.o):
