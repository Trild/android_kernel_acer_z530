cmd_kernel/power/poweroff.o := /home/necoman51/linaro/bin/aarch64-linux-android-gcc -Wp,-MD,kernel/power/.poweroff.o.d  -nostdinc -isystem /home/necoman51/linaro/bin/../lib/gcc/aarch64-linux-android/4.9.4/include -I/home/necoman51/kernel/arch/arm64/include -Iarch/arm64/include/generated  -Iinclude -I/home/necoman51/kernel/arch/arm64/include/uapi -Iarch/arm64/include/generated/uapi -I/home/necoman51/kernel/include/uapi -Iinclude/generated/uapi -include /home/necoman51/kernel/include/linux/kconfig.h -D__KERNEL__ -mlittle-endian -Wall -Wundef -Wstrict-prototypes -Wno-trigraphs -fno-strict-aliasing -fno-common -Werror-implicit-function-declaration -Wno-format-security -fno-delete-null-pointer-checks -Werror=format -Werror=int-to-pointer-cast -Werror=pointer-to-int-cast -O2 -mgeneral-regs-only -fno-pic -Wframe-larger-than=1400 -fno-stack-protector -Wno-unused-but-set-variable -fno-omit-frame-pointer -fno-optimize-sibling-calls -fno-var-tracking-assignments -g -Wdeclaration-after-statement -Wno-pointer-sign -fno-strict-overflow -fconserve-stack -I/home/necoman51/kernel/drivers/misc/mediatek/mach/mt6735/include -I/home/necoman51/kernel/drivers/misc/mediatek/mach/mt6735/include/mach -I/home/necoman51/kernel/drivers/misc/mediatek/mach/mt6735/liquidz530/accdet -I/home/necoman51/kernel/drivers/misc/mediatek/mach/mt6735/liquidz530/core -I/home/necoman51/kernel/drivers/misc/mediatek/mach/mt6735/liquidz530/camera/camera -I/home/necoman51/kernel/drivers/misc/mediatek/mach/mt6735/liquidz530/common -I/home/necoman51/kernel/drivers/misc/mediatek/mach/mt6735/liquidz530/dct/dct -I/home/necoman51/kernel/drivers/misc/mediatek/mach/mt6735/liquidz530/hdmi -I/home/necoman51/kernel/drivers/misc/mediatek/mach/mt6735/liquidz530/imgsensor/inc -I/home/necoman51/kernel/drivers/misc/mediatek/mach/mt6735/liquidz530/keypad -I/home/necoman51/kernel/drivers/misc/mediatek/mach/mt6735/liquidz530/leds/mt65xx -I/home/necoman51/kernel/drivers/misc/mediatek/mach/mt6735/liquidz530/power -I/home/necoman51/kernel/drivers/misc/mediatek/mach/mt6735/liquidz530/rtc -I/home/necoman51/kernel/drivers/misc/mediatek/mach/mt6735/liquidz530/sound/inc -I/home/necoman51/kernel/drivers/misc/mediatek/mach/mt6735/liquidz530/touchpanel/ft5336 -I/home/necoman51/kernel/drivers/misc/mediatek/mach/mt6735/liquidz530/vibrator -I/home/necoman51/kernel/drivers/misc/mediatek/mach/mt6735/liquidz530/nand -I/home/necoman51/kernel/drivers/misc/mediatek/mach/mt6735/liquidz530/dct/dct/inc -I/home/necoman51/kernel/drivers/misc/mediatek/accdet/mt6735 -I/home/necoman51/kernel/drivers/misc/mediatek/accelerometer/inc -I/home/necoman51/kernel/drivers/misc/mediatek/alsps/inc -I/home/necoman51/kernel/drivers/misc/mediatek/hdmi/inc -I/home/necoman51/kernel/drivers/misc/mediatek/barometer/inc -I/home/necoman51/kernel/drivers/misc/mediatek/auxadc/mt6735 -I/home/necoman51/kernel/drivers/misc/mediatek/cam_cal/inc -I/home/necoman51/kernel/drivers/misc/mediatek/camera/mt6735 -I/home/necoman51/kernel/drivers/misc/mediatek/cmdq/mt6735 -I/home/necoman51/kernel/drivers/misc/mediatek/devinfo/mt6735 -I/home/necoman51/kernel/drivers/misc/mediatek/dispsys/mt6735 -I/home/necoman51/kernel/drivers/misc/mediatek/dual_ccci/mt6735/include -I/home/necoman51/kernel/drivers/misc/mediatek/dual_ccci/include -I/home/necoman51/kernel/drivers/misc/mediatek/flashlight/inc -I/home/necoman51/kernel/drivers/misc/mediatek/hall/ -I/home/necoman51/kernel/drivers/misc/mediatek/gyroscope/inc -I/home/necoman51/kernel/drivers/misc/mediatek/step_counter -I/home/necoman51/kernel/drivers/misc/mediatek/pedometer -I/home/necoman51/kernel/drivers/misc/mediatek/activity_sensor -I/home/necoman51/kernel/drivers/misc/mediatek/in_pocket_sensor -I/home/necoman51/kernel/drivers/misc/mediatek/face_down_sensor -I/home/necoman51/kernel/drivers/misc/mediatek/pick_up_sensor -I/home/necoman51/kernel/drivers/misc/mediatek/shake_sensor -I/home/necoman51/kernel/drivers/misc/mediatek/heart_rate_sensor -I/home/necoman51/kernel/drivers/misc/mediatek/tilt_detector_sensor -I/home/necoman51/kernel/drivers/misc/mediatek/wake_gesture_sensor -I/home/necoman51/kernel/drivers/misc/mediatek/glance_gesture_sensor -I/home/necoman51/kernel/drivers/misc/mediatek/i2c/mt6735 -I/home/necoman51/kernel/drivers/misc/mediatek/imgsensor/inc -I/home/necoman51/kernel/drivers/misc/mediatek/eeprom/inc -I/home/necoman51/kernel/drivers/misc/mediatek/leds/mt6735 -I/home/necoman51/kernel/drivers/misc/mediatek/lens/inc -I/home/necoman51/kernel/drivers/misc/mediatek/magnetometer/inc -I/home/necoman51/kernel/drivers/misc/mediatek/met/platform/mt6735 -I/home/necoman51/kernel/drivers/misc/mediatek/met/mt6735 -I/home/necoman51/kernel/drivers/misc/mediatek/sensorHub/inc -I/home/necoman51/kernel/drivers/misc/mediatek/smi/mt6735 -I/home/necoman51/kernel/drivers/misc/mediatek/ssw/inc -I/home/necoman51/kernel/drivers/misc/mediatek/sync -I/home/necoman51/kernel/drivers/misc/mediatek/uart/mt6735 -I/home/necoman51/kernel/drivers/misc/mediatek/vibrator/mt6735 -I/home/necoman51/kernel/drivers/misc/mediatek/video/mt6735 -I/home/necoman51/kernel/drivers/misc/mediatek/video -I/home/necoman51/kernel/drivers/misc/mediatek/wdk -I/home/necoman51/kernel/drivers/misc/mediatek/mjc/mt6735 -I/home/necoman51/kernel/drivers/misc/mediatek/lcm -I/home/necoman51/kernel/drivers/misc/mediatek/lcm/inc -I/home/necoman51/kernel/drivers/misc/mediatek/multibridge/mt6735/mt8193/inc -I/home/necoman51/kernel/drivers/misc/mediatek/dum-char/mt6735 -I/home/necoman51/kernel/drivers/misc/mediatek/lens/mt6735/inc -DCONSTANT_FLASHLIGHT -DILI9881C_HD720_DSI_VDO_DJN -DOV8858_MIPI_RAW -DOV8858S_MIPI_RAW -I/home/necoman51/kernel/PTGEN/inc -I/home/necoman51/kernel/drivers/misc/mediatek/ptgen/mt6735 -I/home/necoman51/kernel/drivers/misc/mediatek/m4u/mt6735/mt6735/    -D"KBUILD_STR(s)=\#s" -D"KBUILD_BASENAME=KBUILD_STR(poweroff)"  -D"KBUILD_MODNAME=KBUILD_STR(poweroff)" -c -o kernel/power/poweroff.o kernel/power/poweroff.c

source_kernel/power/poweroff.o := kernel/power/poweroff.c

deps_kernel/power/poweroff.o := \
  include/linux/kernel.h \
    $(wildcard include/config/lbdaf.h) \
    $(wildcard include/config/preempt/voluntary.h) \
    $(wildcard include/config/debug/atomic/sleep.h) \
    $(wildcard include/config/prove/locking.h) \
    $(wildcard include/config/ring/buffer.h) \
    $(wildcard include/config/tracing.h) \
    $(wildcard include/config/ftrace/mcount/record.h) \
  /home/necoman51/linaro/lib/gcc/aarch64-linux-android/4.9.4/include/stdarg.h \
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
  /home/necoman51/kernel/arch/arm64/include/asm/linkage.h \
  include/linux/stddef.h \
  include/uapi/linux/stddef.h \
  include/linux/types.h \
    $(wildcard include/config/uid16.h) \
    $(wildcard include/config/arch/dma/addr/t/64bit.h) \
    $(wildcard include/config/phys/addr/t/64bit.h) \
    $(wildcard include/config/64bit.h) \
  include/uapi/linux/types.h \
  arch/arm64/include/generated/asm/types.h \
  /home/necoman51/kernel/include/uapi/asm-generic/types.h \
  include/asm-generic/int-ll64.h \
  include/uapi/asm-generic/int-ll64.h \
  /home/necoman51/kernel/arch/arm64/include/uapi/asm/bitsperlong.h \
  include/asm-generic/bitsperlong.h \
  include/uapi/asm-generic/bitsperlong.h \
  /home/necoman51/kernel/include/uapi/linux/posix_types.h \
  arch/arm64/include/generated/asm/posix_types.h \
  /home/necoman51/kernel/include/uapi/asm-generic/posix_types.h \
  include/linux/bitops.h \
  /home/necoman51/kernel/arch/arm64/include/asm/bitops.h \
  /home/necoman51/kernel/arch/arm64/include/asm/barrier.h \
    $(wildcard include/config/smp.h) \
  include/asm-generic/bitops/builtin-__ffs.h \
  include/asm-generic/bitops/builtin-ffs.h \
  include/asm-generic/bitops/builtin-__fls.h \
  include/asm-generic/bitops/builtin-fls.h \
  include/asm-generic/bitops/ffz.h \
  include/asm-generic/bitops/fls64.h \
  include/asm-generic/bitops/find.h \
    $(wildcard include/config/generic/find/first/bit.h) \
  include/asm-generic/bitops/sched.h \
  include/asm-generic/bitops/hweight.h \
  include/asm-generic/bitops/arch_hweight.h \
  include/asm-generic/bitops/const_hweight.h \
  include/asm-generic/bitops/lock.h \
  include/asm-generic/bitops/non-atomic.h \
  include/asm-generic/bitops/le.h \
  /home/necoman51/kernel/arch/arm64/include/uapi/asm/byteorder.h \
  include/linux/byteorder/little_endian.h \
  include/uapi/linux/byteorder/little_endian.h \
  include/linux/swab.h \
  include/uapi/linux/swab.h \
  arch/arm64/include/generated/asm/swab.h \
  /home/necoman51/kernel/include/uapi/asm-generic/swab.h \
  include/linux/byteorder/generic.h \
  include/linux/log2.h \
    $(wildcard include/config/arch/has/ilog2/u32.h) \
    $(wildcard include/config/arch/has/ilog2/u64.h) \
  include/linux/typecheck.h \
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
  include/linux/sysrq.h \
    $(wildcard include/config/magic/sysrq.h) \
  include/linux/errno.h \
  include/uapi/linux/errno.h \
  arch/arm64/include/generated/asm/errno.h \
  /home/necoman51/kernel/include/uapi/asm-generic/errno.h \
  /home/necoman51/kernel/include/uapi/asm-generic/errno-base.h \
  include/linux/pm.h \
    $(wildcard include/config/vt/console/sleep.h) \
    $(wildcard include/config/pm.h) \
    $(wildcard include/config/pm/sleep.h) \
    $(wildcard include/config/pm/runtime.h) \
    $(wildcard include/config/pm/clk.h) \
    $(wildcard include/config/pm/generic/domains.h) \
  include/linux/list.h \
    $(wildcard include/config/debug/list.h) \
  include/linux/poison.h \
    $(wildcard include/config/illegal/pointer/value.h) \
  /home/necoman51/kernel/include/uapi/linux/const.h \
  include/linux/workqueue.h \
    $(wildcard include/config/debug/objects/work.h) \
    $(wildcard include/config/lockdep.h) \
    $(wildcard include/config/freezer.h) \
    $(wildcard include/config/sysfs.h) \
  include/linux/timer.h \
    $(wildcard include/config/timer/stats.h) \
    $(wildcard include/config/debug/objects/timers.h) \
  include/linux/ktime.h \
    $(wildcard include/config/ktime/scalar.h) \
  include/linux/time.h \
    $(wildcard include/config/arch/uses/gettimeoffset.h) \
  include/linux/cache.h \
    $(wildcard include/config/arch/has/cache/line/size.h) \
  /home/necoman51/kernel/arch/arm64/include/asm/cache.h \
  include/linux/seqlock.h \
  include/linux/spinlock.h \
    $(wildcard include/config/debug/spinlock.h) \
    $(wildcard include/config/generic/lockbreak.h) \
    $(wildcard include/config/preempt.h) \
    $(wildcard include/config/debug/lock/alloc.h) \
  include/linux/preempt.h \
    $(wildcard include/config/debug/preempt.h) \
    $(wildcard include/config/preempt/tracer.h) \
    $(wildcard include/config/context/tracking.h) \
    $(wildcard include/config/preempt/count.h) \
    $(wildcard include/config/preempt/notifiers.h) \
  include/linux/thread_info.h \
    $(wildcard include/config/compat.h) \
    $(wildcard include/config/debug/stack/usage.h) \
  include/linux/bug.h \
    $(wildcard include/config/generic/bug.h) \
  arch/arm64/include/generated/asm/bug.h \
  include/asm-generic/bug.h \
    $(wildcard include/config/bug.h) \
    $(wildcard include/config/generic/bug/relative/pointers.h) \
    $(wildcard include/config/debug/bugverbose.h) \
  /home/necoman51/kernel/arch/arm64/include/asm/thread_info.h \
    $(wildcard include/config/arm64/64k/pages.h) \
    $(wildcard include/config/mt/rt/sched.h) \
  include/linux/irqflags.h \
    $(wildcard include/config/trace/irqflags.h) \
    $(wildcard include/config/preempt/monitor.h) \
    $(wildcard include/config/irqsoff/tracer.h) \
    $(wildcard include/config/trace/irqflags/support.h) \
  /home/necoman51/kernel/arch/arm64/include/asm/irqflags.h \
  /home/necoman51/kernel/arch/arm64/include/asm/ptrace.h \
  /home/necoman51/kernel/arch/arm64/include/uapi/asm/ptrace.h \
  /home/necoman51/kernel/arch/arm64/include/asm/hwcap.h \
  /home/necoman51/kernel/arch/arm64/include/uapi/asm/hwcap.h \
  include/linux/bottom_half.h \
  include/linux/spinlock_types.h \
  /home/necoman51/kernel/arch/arm64/include/asm/spinlock_types.h \
  include/linux/lockdep.h \
    $(wildcard include/config/lock/stat.h) \
    $(wildcard include/config/prove/rcu.h) \
  include/linux/rwlock_types.h \
  /home/necoman51/kernel/arch/arm64/include/asm/spinlock.h \
  /home/necoman51/kernel/arch/arm64/include/asm/processor.h \
  include/linux/string.h \
    $(wildcard include/config/binary/printf.h) \
  include/uapi/linux/string.h \
  /home/necoman51/kernel/arch/arm64/include/asm/string.h \
  /home/necoman51/kernel/arch/arm64/include/asm/fpsimd.h \
  /home/necoman51/kernel/arch/arm64/include/asm/hw_breakpoint.h \
    $(wildcard include/config/have/hw/breakpoint.h) \
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
  include/linux/atomic.h \
    $(wildcard include/config/arch/has/atomic/or.h) \
    $(wildcard include/config/generic/atomic64.h) \
  /home/necoman51/kernel/arch/arm64/include/asm/atomic.h \
  /home/necoman51/kernel/arch/arm64/include/asm/cmpxchg.h \
  include/asm-generic/atomic-long.h \
  include/linux/math64.h \
  arch/arm64/include/generated/asm/div64.h \
  include/asm-generic/div64.h \
  include/uapi/linux/time.h \
  include/linux/jiffies.h \
  include/linux/timex.h \
  include/uapi/linux/timex.h \
  /home/necoman51/kernel/include/uapi/linux/param.h \
  /home/necoman51/kernel/arch/arm64/include/uapi/asm/param.h \
  include/asm-generic/param.h \
    $(wildcard include/config/hz.h) \
  include/uapi/asm-generic/param.h \
  /home/necoman51/kernel/arch/arm64/include/asm/timex.h \
  include/asm-generic/timex.h \
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
  include/linux/wait.h \
  arch/arm64/include/generated/asm/current.h \
  include/asm-generic/current.h \
  include/uapi/linux/wait.h \
  include/linux/completion.h \
  include/linux/reboot.h \
  include/linux/notifier.h \
  include/linux/mutex.h \
    $(wildcard include/config/debug/mutexes.h) \
    $(wildcard include/config/mutex/spin/on/owner.h) \
    $(wildcard include/config/mt/debug/mutexes.h) \
    $(wildcard include/config/have/arch/mutex/cpu/relax.h) \
  include/linux/rwsem.h \
    $(wildcard include/config/rwsem/generic/spinlock.h) \
  include/linux/rwsem-spinlock.h \
  include/linux/srcu.h \
  include/linux/rcupdate.h \
    $(wildcard include/config/rcu/torture/test.h) \
    $(wildcard include/config/tree/rcu.h) \
    $(wildcard include/config/tree/preempt/rcu.h) \
    $(wildcard include/config/rcu/trace.h) \
    $(wildcard include/config/preempt/rcu.h) \
    $(wildcard include/config/rcu/user/qs.h) \
    $(wildcard include/config/tiny/rcu.h) \
    $(wildcard include/config/tiny/preempt/rcu.h) \
    $(wildcard include/config/debug/objects/rcu/head.h) \
    $(wildcard include/config/rcu/nocb/cpu.h) \
  include/linux/rcutree.h \
  include/uapi/linux/reboot.h \
  arch/arm64/include/generated/asm/emergency-restart.h \
  include/asm-generic/emergency-restart.h \

kernel/power/poweroff.o: $(deps_kernel/power/poweroff.o)

$(deps_kernel/power/poweroff.o):