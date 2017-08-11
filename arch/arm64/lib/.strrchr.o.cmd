cmd_arch/arm64/lib/strrchr.o := /home/necoman51/linaro/bin/aarch64-linux-android-gcc -Wp,-MD,arch/arm64/lib/.strrchr.o.d  -nostdinc -isystem /home/necoman51/linaro/bin/../lib/gcc/aarch64-linux-android/4.9.4/include -I/home/necoman51/kernel/arch/arm64/include -Iarch/arm64/include/generated  -Iinclude -I/home/necoman51/kernel/arch/arm64/include/uapi -Iarch/arm64/include/generated/uapi -I/home/necoman51/kernel/include/uapi -Iinclude/generated/uapi -include /home/necoman51/kernel/include/linux/kconfig.h -D__KERNEL__ -mlittle-endian  -D__ASSEMBLY__ -gdwarf-2         -c -o arch/arm64/lib/strrchr.o arch/arm64/lib/strrchr.S

source_arch/arm64/lib/strrchr.o := arch/arm64/lib/strrchr.S

deps_arch/arm64/lib/strrchr.o := \
  include/linux/linkage.h \
  include/linux/compiler.h \
    $(wildcard include/config/sparse/rcu/pointer.h) \
    $(wildcard include/config/trace/branch/profiling.h) \
    $(wildcard include/config/profile/all/branches.h) \
    $(wildcard include/config/enable/must/check.h) \
    $(wildcard include/config/enable/warn/deprecated.h) \
    $(wildcard include/config/kprobes.h) \
  include/linux/stringify.h \
  include/linux/export.h \
    $(wildcard include/config/have/underscore/symbol/prefix.h) \
    $(wildcard include/config/modules.h) \
    $(wildcard include/config/modversions.h) \
    $(wildcard include/config/unused/symbols.h) \
  /home/necoman51/kernel/arch/arm64/include/asm/linkage.h \
  /home/necoman51/kernel/arch/arm64/include/asm/assembler.h \
    $(wildcard include/config/smp.h) \
    $(wildcard include/config/cpu/big/endian.h) \
  /home/necoman51/kernel/arch/arm64/include/asm/ptrace.h \
    $(wildcard include/config/compat.h) \
  /home/necoman51/kernel/arch/arm64/include/uapi/asm/ptrace.h \
  include/linux/types.h \
    $(wildcard include/config/uid16.h) \
    $(wildcard include/config/lbdaf.h) \
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
  /home/necoman51/kernel/arch/arm64/include/asm/hwcap.h \
  /home/necoman51/kernel/arch/arm64/include/uapi/asm/hwcap.h \

arch/arm64/lib/strrchr.o: $(deps_arch/arm64/lib/strrchr.o)

$(deps_arch/arm64/lib/strrchr.o):
