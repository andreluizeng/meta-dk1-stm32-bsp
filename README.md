OpenEmbedded BSP layer for the Custom STM32 DK1
==========================================

This layer provides BSP for the a Custom STM32 board (based on STM32MP157a-DK1)

Dependencies
------------

This layer depends on:

* URI: git://git.yoctoproject.org/poky
  - branch: kirkstone
  - layers: meta

* URI: https://source.denx.de/denx/meta-mainline-common.git
  - branch: dunfell-3.1

Building the image
------------------

A good starting point for setting up the build environment is is the official
Yocto Project wiki.

* https://www.yoctoproject.org/docs/3.1/brief-yoctoprojectqs/brief-yoctoprojectqs.html

Before attempting the build, the following metalayer git repositories shall
be cloned into a location accessible to the build system and a branch listed
below shall be checked out. The examples below will use /path/to/OE/ as a
location of the metalayers.

* https://source.denx.de/denx/meta-mainline-common.git	(branch: kirkstone)
* https://github.com/andreluizeng/meta-dk1-stm32-bsp.git	(branch: master)
* git://git.yoctoproject.org/poky				(branch: kirkstone)

With all the source artifacts in place, proceed with setting up the build
using oe-init-build-env as specified in the Yocto Project wiki:
/path/to/OE/poky $ source oe-init-build-env

In addition to the content in the wiki, the aforementioned metalayers shall
be referenced in bblayers.conf in this order:

```
BBLAYERS ?= " \
  /path/to/OE/poky/meta \
  /path/to/OE/meta-mainline-common \
  /path/to/OE/meta-dk1-stm32-bsp \
  "
```

The following specifics should be placed into local.conf:

```
MACHINE = "custom-stm32-dk1"
DISTRO = "nodistro"
```

Note that MACHINE must be:

* custom-stm32-dk1

Adapt the suffixes of all the files and names of directories further in
this documentation according to MACHINE.

Both local.conf and bblayers.conf are included verbatim in full at the end
of this readme.

Once the configuration is complete, a basic demo system image suitable for
evaluation can be built using:

```
$ bitbake core-image-minimal
```

Once the build completes, the images are available in:

```
tmp-glibc/deploy/images/custom-stm32-dk1/
```
The SD card is specifically in:

```
core-image-minimal-custom-stm32-dk1.wic.gz
```

And shall be written to the SD card via the following
commands from the U-Boot prompt:

```
gunzip core-image-minimal-custom-stm32-dk1.wic.gz
sudo dd if=core-image-minimal-custom-stm32-dk1.wic of=/dev/sdX; sudo sync
```

Example local.conf
------------------
```
MACHINE = "custom-stm32-dk1"
DL_DIR = "/path/to/OE/downloads"
DISTRO ?= "nodistro"
PACKAGE_CLASSES ?= "package_rpm"
EXTRA_IMAGE_FEATURES = "debug-tweaks"
USER_CLASSES ?= "buildstats"
PATCHRESOLVE = "noop"
BB_DISKMON_DIRS = "\
    STOPTASKS,${TMPDIR},1G,100K \
    STOPTASKS,${DL_DIR},1G,100K \
    STOPTASKS,${SSTATE_DIR},1G,100K \
    STOPTASKS,/tmp,100M,100K \
    HALT,${TMPDIR},100M,1K \
    HALT,${DL_DIR},100M,1K \
    HALT,${SSTATE_DIR},100M,1K \
    HALT,/tmp,10M,1K"
PACKAGECONFIG:append:pn-qemu-native = " sdl"
PACKAGECONFIG:append:pn-nativesdk-qemu = " sdl"
CONF_VERSION = "2"

```

Example bblayers.conf
---------------------
```
# LAYER_CONF_VERSION is increased each time build/conf/bblayers.conf
# changes incompatibly
POKY_BBLAYERS_CONF_VERSION = "2"

BBPATH = "${TOPDIR}"
BBFILES ?= ""

BBLAYERS ?= " \
	/path/to/OE/poky/meta \
	/path/to/OE/meta-mainline-common \
	/path/to/OE/meta-dk1-stm32-bsp \
	"
```

Example Installing the BSP and build the minimal image
---------------------
```
# Get Yocto (kirkstone) source and dependencies
	
	$ git clone http://git.yoctoproject.org/git/poky -b kirkstone yocto
	$ cd yocto
	$ git clone https://source.denx.de/denx/meta-mainline-common.git -b kirkstone
	$ git clone https://github.com/andreluizeng/meta-dk1-stm32-bsp.git
	
# Set the build environment

	$ source oe-init-build-env build-custom-stm32-dk1
	
# Change the local.conf and bblayers.conf as presented before (example of local.conf and bblayers.conf)

# Build the minimal image

	$ bitbake core-image-minimal
	
```
