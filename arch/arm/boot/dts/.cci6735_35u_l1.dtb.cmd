cmd_arch/arm/boot/dts/cci6735_35u_l1.dtb := /home/necoman51/linaro-4.9/bin/arm-eabi-gcc -E -Wp,-MD,arch/arm/boot/dts/.cci6735_35u_l1.dtb.d.pre.tmp -nostdinc -I/home/necoman51/kernel/arch/arm/boot/dts -I/home/necoman51/kernel/arch/arm/boot/dts/include -undef -D__DTS__ -x assembler-with-cpp -o arch/arm/boot/dts/.cci6735_35u_l1.dtb.dts.tmp arch/arm/boot/dts/cci6735_35u_l1.dts ; /home/necoman51/kernel/scripts/dtc/dtc -O dtb -o arch/arm/boot/dts/cci6735_35u_l1.dtb -b 0 -i arch/arm/boot/dts/ -i /home/necoman51/kernel/drivers/misc/mediatek/mach/mt6735/cci6735_35u_l1/dct/dct/ -d arch/arm/boot/dts/.cci6735_35u_l1.dtb.d.dtc.tmp arch/arm/boot/dts/.cci6735_35u_l1.dtb.dts.tmp ; cat arch/arm/boot/dts/.cci6735_35u_l1.dtb.d.pre.tmp arch/arm/boot/dts/.cci6735_35u_l1.dtb.d.dtc.tmp > arch/arm/boot/dts/.cci6735_35u_l1.dtb.d

source_arch/arm/boot/dts/cci6735_35u_l1.dtb := arch/arm/boot/dts/cci6735_35u_l1.dts

deps_arch/arm/boot/dts/cci6735_35u_l1.dtb := \
  arch/arm/boot/dts/mt6735.dtsi \
    $(wildcard include/config/base.h) \
    $(wildcard include/config/addr.h) \
  /home/necoman51/kernel/arch/arm/boot/dts/include/dt-bindings/clock/mt6735-clk.h \
  /home/necoman51/kernel/drivers/misc/mediatek/mach/mt6735/cci6735_35u_l1/dct/dct/cust_eint.dtsi \

arch/arm/boot/dts/cci6735_35u_l1.dtb: $(deps_arch/arm/boot/dts/cci6735_35u_l1.dtb)

$(deps_arch/arm/boot/dts/cci6735_35u_l1.dtb):
