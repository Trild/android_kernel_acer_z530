cmd_arch/arm64/crypto/aes-ce.o := /home/necoman51/linaro/bin/aarch64-linux-android-gcc -Wp,-MD,arch/arm64/crypto/.aes-ce.o.d  -nostdinc -isystem /home/necoman51/linaro/bin/../lib/gcc/aarch64-linux-android/4.9.4/include -I/home/necoman51/kernel/arch/arm64/include -Iarch/arm64/include/generated  -Iinclude -I/home/necoman51/kernel/arch/arm64/include/uapi -Iarch/arm64/include/generated/uapi -I/home/necoman51/kernel/include/uapi -Iinclude/generated/uapi -include /home/necoman51/kernel/include/linux/kconfig.h -D__KERNEL__ -mlittle-endian  -D__ASSEMBLY__ -gdwarf-2      -DINTERLEAVE=2 -DINTERLEAVE_INLINE   -c -o arch/arm64/crypto/aes-ce.o arch/arm64/crypto/aes-ce.S

source_arch/arm64/crypto/aes-ce.o := arch/arm64/crypto/aes-ce.S

deps_arch/arm64/crypto/aes-ce.o := \
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
  arch/arm64/crypto/aes-modes.S \

arch/arm64/crypto/aes-ce.o: $(deps_arch/arm64/crypto/aes-ce.o)

$(deps_arch/arm64/crypto/aes-ce.o):
