cmd_drivers/staging/android/ion/ion_profile.o := /home/necoman51/linaro-4.9/bin/arm-eabi-gcc -Wp,-MD,drivers/staging/android/ion/.ion_profile.o.d  -nostdinc -isystem /home/necoman51/linaro-4.9/bin/../lib/gcc/arm-eabi/4.9.4/include -I/home/necoman51/kernel/arch/arm/include -Iarch/arm/include/generated  -Iinclude -I/home/necoman51/kernel/arch/arm/include/uapi -Iarch/arm/include/generated/uapi -I/home/necoman51/kernel/include/uapi -Iinclude/generated/uapi -include /home/necoman51/kernel/include/linux/kconfig.h -D__KERNEL__ -mlittle-endian -I/home/necoman51/kernel/drivers/misc/mediatek/mach/mt6735/include -Wall -Wundef -Wstrict-prototypes -Wno-trigraphs -fno-strict-aliasing -fno-common -Werror-implicit-function-declaration -Wno-format-security -fno-delete-null-pointer-checks -Werror=format -Werror=int-to-pointer-cast -Werror=pointer-to-int-cast -O2 -fno-dwarf2-cfi-asm -fno-omit-frame-pointer -mapcs -mno-sched-prolog -fstack-protector -mabi=aapcs-linux -mno-thumb-interwork -marm -D__LINUX_ARM_ARCH__=7 -march=armv7-a -msoft-float -Uarm -Wframe-larger-than=1400 -Wno-unused-but-set-variable -fno-omit-frame-pointer -fno-optimize-sibling-calls -fno-var-tracking-assignments -g -Wdeclaration-after-statement -Wno-pointer-sign -fno-strict-overflow -fconserve-stack -DCC_HAVE_ASM_GOTO -I/home/necoman51/kernel/drivers/staging/android/ion -DION_RUNTIME_DEBUGGER=0    -D"KBUILD_STR(s)=\#s" -D"KBUILD_BASENAME=KBUILD_STR(ion_profile)"  -D"KBUILD_MODNAME=KBUILD_STR(ion_profile)" -c -o drivers/staging/android/ion/ion_profile.o drivers/staging/android/ion/ion_profile.c

source_drivers/staging/android/ion/ion_profile.o := drivers/staging/android/ion/ion_profile.c

deps_drivers/staging/android/ion/ion_profile.o := \
  drivers/staging/android/ion/ion_profile.h \
  include/linux/mmprofile.h \
  include/linux/mmprofile_static_event.h \

drivers/staging/android/ion/ion_profile.o: $(deps_drivers/staging/android/ion/ion_profile.o)

$(deps_drivers/staging/android/ion/ion_profile.o):
