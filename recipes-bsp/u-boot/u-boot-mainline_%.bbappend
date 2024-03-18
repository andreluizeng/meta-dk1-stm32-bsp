FILESEXTRAPATHS:prepend := "${THISDIR}/files/common:${THISDIR}/files/${MACHINE}:${THISDIR}/files:"

do_compile:prepend:custom-stm32-dk1 () {
	sed -i -e "s/%UBOOT_DTB_LOADADDRESS%/${UBOOT_DTB_LOADADDRESS}/g" \
		-e "s/%UBOOT_DTBO_LOADADDRESS%/${UBOOT_DTBO_LOADADDRESS}/g" \
		${WORKDIR}/${UBOOT_ENV_SRC}
}

SRC_URI:append:custom-stm32-dk1 = " \
	file://boot.cmd \
	file://fw_env.config \
	file://default-device-tree.cfg \
	"

# U-Boot release extra version, used as identifier of a patch
# release. Update this every time this recipe is updated. The
# format is -${MACHINE}-date.extraversion. The date is in the
# format YYYYMMDD, the extraversion is used in case there are
# multiple releases during a single day, which is unlikely.
UBOOT_LOCALVERSION:custom-stm32-dk1 ?= "-${MACHINE}-20240318.01"
