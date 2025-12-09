# Adding a Package to Yocto Project Image (Method 1)

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
```

4. Rebuild the image:

```bash
bitbake core-image-minimal
```

## Verify Package Installation

After flashing and booting the image on your target device:

```bash
which <package-name>
<package-name> --version
```

## References

- [Yocto Project Documentation](https://www.yoctoproject.org/docs/)
