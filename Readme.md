# Adding a Package to Yocto Project Image

This guide explains how to include a package directly in your Yocto Project image using the `IMAGE_INSTALL` variable.

## Prerequisites

- Yocto Project environment set up
- Build environment sourced:

```bash
source oe-init-build-env
```

## Steps to Add a Package

1. Check available recipes and their layers:

```bash
bitbake-layers show-recipes <package-name>
```
2. This shows the exact path of the .bb file:

```bash
bitbake -e <package-name> | grep ^FILE=
```
**Example:**
```
embedded@embedded:~/Documents/STM32MP157/yocto/poky/Linux_Build$ bitbake-layers show-recipes ethtool
NOTE: Starting bitbake server...
Loading cache: 100% |###################################################################################################################################################################| Time: 0:00:00
Loaded 3876 entries from dependency cache.
=== Matching recipes: ===
ethtool:
  meta                 5.16
```
```
embedded@embedded-HP-EliteDesk-800-G1-SFF:~/Documents/Yocto/STM32MP157_build$ bitbake -e ethtool | grep ^FILE=
FILE="/home/embedded/Documents/Yocto/poky-kirkstone-4.0.32/meta/recipes-extended/ethtool/ethtool_5.16.bb"
```
If the layer containing the package recipe is not added to your Yocto build, you need to add the layer before you can build the package. Here’s what you should do step by step:
```
bitbake-layers add-layer Name_of_layer
```
This will display the layer each recipe comes from, helping you ensure the package is available.

2. Open the Yocto configuration file:

```bash
nano conf/local.conf
```

3. Append the package to `IMAGE_INSTALL`:

```bash
IMAGE_INSTALL:append = " <package-name>"
```

**Example:**

```bash
IMAGE_INSTALL:append = " nano"
IMAGE_INSTALL:append = " python3"
IMAGE_INSTALL:append = " git"
IMAGE_INSTALL:append = " htop"
IMAGE_INSTALL:append = " ethtool"
IMAGE_INSTALL:append = " net-snmp"
IMAGE_INSTALL:append = " openssh"
IMAGE_INSTALL:append = " lftp"
```

4. Rebuild the image:

```bash
bitbake core-image-minimal
```

## Verify Package Installation
In Yocto, you can verify that a package is installed in your image before booting the embedded board using several reliable methods.
1. Check if Package Is Included in Image (Build-Time Check):
Go to:
```bash
tmp/deploy/images/stm32mp1/
```
Find the .manifest file:
```bash
core-image-minimal-stm32mp1.manifest
```
```bash
cat core-image-minimal-stm32mp1.manifest | grep <Package Name>
```
If you see:
```bash
<Package Name> <version>
```
The package is included in the root filesystem.

2. After flashing and booting the image on your target device:
```bash
which <package-name>
<package-name> --version
```

## References

- [Yocto Project Documentation](https://www.yoctoproject.org/docs/)
