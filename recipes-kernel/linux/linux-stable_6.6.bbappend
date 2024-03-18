FILESEXTRAPATHS:prepend := "${THISDIR}/${PN}:"

KBRANCH:custom-stm32-dk1 ?= "linux-${BPV}.y"
KMACHINE:custom-stm32-dk1 ?= "custom-stm32-dk1"
COMPATIBLE_MACHINE:custom-stm32-dk1 = "(custom-stm32-dk1)"

DEPENDS:append:custom-stm32-dk1 = " lzop-native "
SRC_URI:append:custom-stm32-dk1 = " \
	file://${BPV}/custom-stm32-dk1;type=kmeta;destsuffix=${BPV}/custom-stm32-dk1 \
	file://common/custom-stm32-dk1;type=kmeta;destsuffix=common/custom-stm32-dk1 \
	"
KERNEL_FEATURES:custom-stm32-dk1 = " custom-stm32-dk1-standard.scc "
