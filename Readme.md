## Step 2: Build Linux for STM32MP1

In this section, we will build a custom Linux image for the **STM32MP1** series using the Yocto Project.

---

### 2.1 Prerequisites

Make sure your development machine has the following installed:

- Linux OS (Ubuntu 22.04 recommended)
- Git
- vscode
- Required packages:
```
sudo apt-get update
sudo apt-get install -y gawk wget git-core diffstat unzip texinfo gcc-multilib \
     build-essential chrpath socat cpio python3 python3-pip python3-pexpect \
     xz-utils debianutils iputils-ping
```

# Create a directory for Yocto
```
mkdir ~/yocto-stm32mp1
mkdir -p ~/yocto-stm32mp1/build
cd ~/yocto-stm32mp1
```
# Clone Poky (Yocto reference)
```
git clone -b mickledore git://git.yoctoproject.org/poky.git
cd poky
```
# Clone meta-openembedded for additional recipes
```
git clone -b mickledore git://git.openembedded.org/meta-openembedded
```
# Clone STM32 BSP layer
```
git clone -b mickledore https://github.com/STMicroelectronics/meta-st-stm32mp.git
```
# Setup the Build Environment
```
source oe-init-build-env ../build/STM32MP1
```
# Configure the Build for STM32MP1
```
MACHINE ?= "stm32mp1"
```
You can also customize other settings such as number of parallel builds:
```
BB_NUMBER_THREADS = "8"
PARALLEL_MAKE = "-j 8"
RM_OLD_IMAGE = "1"
INHERIT += "rm_work"
```
# Add BSP Layers
Edit build/conf/bblayers.conf and add the paths to the layers
```
BBLAYERS ?= " \
  ${TOPDIR}/../poky/meta \
  ${TOPDIR}/../poky/meta-poky \
  ${TOPDIR}/../poky/meta-yocto-bsp \
  ${TOPDIR}/../meta-openembedded/meta-oe \
  ${TOPDIR}/../meta-openembedded/meta-networking \
  ${TOPDIR}/../meta-openembedded/meta-python \
  ${TOPDIR}/../meta-st-stm32mp \
"
```
# Show BSP Layers
```
bitbake-layers show-layers
```
# Build the Linux Image
Now, you can build the Linux image:
```
bitbake core-image-minimal
```
```core-image-minimal``` is a small Linux image. You can replace it with core-image-full-cmdline or create a custom image.

The build may take a few hours depending on your machine.

