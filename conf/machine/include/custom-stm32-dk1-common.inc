DEFAULTTUNE ?= "cortexa7thf-neon-vfpv4"
SOC_FAMILY ?= "stm32mp1"

# MACHINEOVERRIDES =. "dh-dhsom:dh-stm32mp1-dhsom:"

ARM_INSTRUCTION_SET = "thumb"

require conf/machine/include/${@'' if (d.getVar('LAYERSERIES_CORENAMES') in ["dunfell"]) else 'arm/armv7a/'}tune-cortexa7.inc
require conf/machine/include/soc-family.inc

MACHINE_FEATURES ?= "apm ext2 keyboard screen serial usbhost"

SERIAL_CONSOLE = "115200 ttySTM0"

# U-Boot bootloader
UBOOT_ENTRYPOINT := "0xc4000000"
UBOOT_MAKE_TARGET := "u-boot.img all"
UBOOT_BINARY := "u-boot.img"
UBOOT_SUFFIX ?= "img"
SPL_BINARY := "u-boot-spl.stm32"
UBOOT_ENV = "boot"
UBOOT_ENV_SUFFIX = "scr"
# fitImage DT and DTO load addresses
UBOOT_DTB_LOADADDRESS = "0xcff00000"
UBOOT_DTBO_LOADADDRESS = "0xcff80000"

PREFERRED_PROVIDER_virtual/bootloader ?= "u-boot-mainline"
PREFERRED_PROVIDER_u-boot ?= "u-boot-mainline"
PREFERRED_PROVIDER_u-boot-native ?= "u-boot-mainline"
PREFERRED_PROVIDER_u-boot-fw-utils ?= "u-boot-mainline-fw-utils"
PREFERRED_PROVIDER_u-boot-fw-utils-native ?= "u-boot-mainline-fw-utils-native"
PREFERRED_PROVIDER_u-boot-mkimage-native ?= "u-boot-mainline-tools-native"
PREFERRED_PROVIDER_u-boot-tools ?= "u-boot-mainline-tools"
PREFERRED_PROVIDER_u-boot-tools-native ?= "u-boot-mainline-tools-native"
PREFERRED_VERSION_u-boot-mainline ?= "2024.01%"
PREFERRED_VERSION_u-boot-mainline-native ?= "2024.01%"
PREFERRED_VERSION_u-boot-mainline-fw-utils ?= "2024.01%"
PREFERRED_VERSION_u-boot-mainline-fw-utils-native ?= "2024.01%"
PREFERRED_VERSION_u-boot-mainline-tools ?= "2024.01%"
PREFERRED_VERSION_u-boot-mainline-tools-native ?= "2024.01%"

# Linux kernel
KERNEL_IMAGETYPE = "fitImage"
KERNEL_CLASSES += " kernel-fitimage "

PREFERRED_PROVIDER_virtual/kernel ?= "linux-stable"
PREFERRED_VERSION_linux-stable ?= "6.6%"
KERNEL_DTC_FLAGS += "-@"

# Ship kernel modules
MACHINE_ESSENTIAL_EXTRA_RDEPENDS += " kernel-modules kernel-devicetree u-boot-default-env "

# List of images to be built
IMAGE_FSTYPES ?= "tar.xz wic.xz wic.gz wic.bmap ext4.gz"
INITRAMFS_FSTYPES ?= "cpio.xz"

EXTRA_IMAGEDEPENDS += "virtual/bootloader"
WKS_FILE ?= "sdimage-stm32mp1.wks"
IMAGE_BOOT_FILES ?= "${KERNEL_IMAGETYPE}"
IMAGE_INSTALL:append = " kernel-devicetree kernel-image-fitimage virtual/bootloader "
do_image_wic[depends] += "mtools-native:do_populate_sysroot dosfstools-native:do_populate_sysroot virtual/bootloader:do_deploy"

# Add any optional config files that might be present e.g. in other layers
include conf/machine/include/custom-stm32-dk1-common-extra.inc
include conf/machine/${MACHINE}-extra.conf
