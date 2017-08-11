cmd_arch/arm64/boot/dts/cci6735m_65c_l1.dtb := /home/necoman51/linaro/bin/aarch64-linux-android-gcc -E -Wp,-MD,arch/arm64/boot/dts/.cci6735m_65c_l1.dtb.d.pre.tmp -nostdinc -I/home/necoman51/kernel/arch/arm64/boot/dts -I/home/necoman51/kernel/arch/arm64/boot/dts/include -undef -D__DTS__ -x assembler-with-cpp -o arch/arm64/boot/dts/.cci6735m_65c_l1.dtb.dts.tmp arch/arm64/boot/dts/cci6735m_65c_l1.dts ; /home/necoman51/kernel/scripts/dtc/dtc -O dtb -o arch/arm64/boot/dts/cci6735m_65c_l1.dtb -b 0 -i arch/arm64/boot/dts/ -i /home/necoman51/kernel/drivers/misc/mediatek/mach/mt6735/liquidz530/dct/dct/ -d arch/arm64/boot/dts/.cci6735m_65c_l1.dtb.d.dtc.tmp arch/arm64/boot/dts/.cci6735m_65c_l1.dtb.dts.tmp ; cat arch/arm64/boot/dts/.cci6735m_65c_l1.dtb.d.pre.tmp arch/arm64/boot/dts/.cci6735m_65c_l1.dtb.d.dtc.tmp > arch/arm64/boot/dts/.cci6735m_65c_l1.dtb.d

source_arch/arm64/boot/dts/cci6735m_65c_l1.dtb := arch/arm64/boot/dts/cci6735m_65c_l1.dts

deps_arch/arm64/boot/dts/cci6735m_65c_l1.dtb := \
  arch/arm64/boot/dts/mt6735m.dtsi \
    $(wildcard include/config/base.h) \
    $(wildcard include/config/addr.h) \
  /home/necoman51/kernel/drivers/misc/mediatek/mach/mt6735/liquidz530/dct/dct/cust_eint.dtsi \

arch/arm64/boot/dts/cci6735m_65c_l1.dtb: $(deps_arch/arm64/boot/dts/cci6735m_65c_l1.dtb)

$(deps_arch/arm64/boot/dts/cci6735m_65c_l1.dtb):
