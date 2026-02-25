# RPROVIDES in Yocto Recipes

## Overview

`RPROVIDES` is a variable used in Yocto Project recipes to declare
virtual package names that a recipe provides in addition to its real
package name.

It allows one recipe to act as a replacement or alternative provider for
another package without changing dependency declarations in other
recipes.

## Purpose

-   Enables package substitution
-   Supports virtual packages
-   Allows multiple implementations of the same functionality
-   Improves system flexibility and modularity

## How It Works

Example:

``` bash
RPROVIDES:${PN} = "virtual/example"
```

This means:

-   The recipe provides the virtual package `virtual/example`
-   Any other recipe depending on `virtual/example` will be satisfied by
    this recipe

## Example

### Old Recipe: myapp.bb

``` bash
SUMMARY = "Simple Makefile Application"
LICENSE = "CLOSED"

SRC_URI = "file://main.c \
           file://Makefile"

S = "${WORKDIR}"

do_compile() {
    oe_runmake
}

do_install() {
    install -d ${D}${bindir}
    install -m 0755 myapp ${D}${bindir}
}
```
Normally, you can include the ```myapp``` package in the image using the following command:
``` bash
IMAGE_INSTALL:append = " myapp"
```

### New Recipe: myapp_1.bb

``` bash
SUMMARY = "Simple Makefile Application"
LICENSE = "CLOSED"

SRC_URI = "file://main.c \
           file://Makefile"

S = "${WORKDIR}"

do_compile() {
    oe_runmake
}

do_install() {
    install -d ${D}${bindir}
    install -m 0755 myapp ${D}${bindir}
}
```
In this scenario, the myapp package is not available in the build environment and cannot be referenced in the local.conf file. Consequently, the configuration ```IMAGE_INSTALL:append = " myapp"``` is not applicable.

For everything to work properly, you can add the following commands to the myapp_1.bb recipe.
``` bash
RPROVIDES:${PN} = "myapp"
```
At this stage, the myapp package is correctly built and integrated into the final image.
## When to Use RPROVIDES

-   Replacing default implementations
-   Providing hardware-specific implementations
-   Creating alternative libraries or drivers
-   Supporting multiple backends

## Difference Between PROVIDES and RPROVIDES

-   `PROVIDES` → Used for build-time recipe name replacement
-   `RPROVIDES` → Used for runtime virtual package replacement

In most cases for virtual package substitution, `RPROVIDES` is
preferred.
