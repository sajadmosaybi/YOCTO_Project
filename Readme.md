# Compiling C Code in the Yocto Project

This guide explains how to compile a simple C application using the
Yocto Project. Unlike traditional Linux systems, Yocto uses **BitBake
recipes** to cross-compile applications for embedded targets.

------------------------------------------------------------------------

## 1. Key Concept

You **do not compile C code manually** in Yocto using `gcc`.

Instead, you: - Write a BitBake recipe (`.bb`) - Let Yocto use its
cross-compiler - Install the binary into the root filesystem
automatically

------------------------------------------------------------------------

## 2. Example C Application

### `counter.c`

``` c
#include <stdio.h>
#include <unistd.h>  // for sleep()

int main(void)
{
    int counter = 0;

    while (1)  // infinite loop
    {
        printf("Counter: %d\n", counter);
        counter++;          // increment counter
        sleep(1);           // wait 1 second
    }

    return 0;
}

```
------------------------------------------------------------------------

## 3. Directory Structure

    meta-mylayer/
    └── recipes-example/
        └── counter/
            ├── counter_0.1.bb
            └── files
                 └── counter.c
------------------------------------------------------------------------

## 4. BitBake Recipe

### `counter_0.1.bb`

``` bitbake
SUMMARY = "Counter Code Program"
LICENSE = "MIT"
LIC_FILES_CHKSUM = "file://${COREBASE}/meta/COPYING.MIT;md5=3da9cfbcb788c80a0384361b4de20420"

SRC_URI = "file://counter.c"
S = "${WORKDIR}/build"

python do_display_banner() {
    bb.plain("***********************************************");
    bb.plain("*                                             *");
    bb.plain("*  Counter Code Build Running...              *");
    bb.plain("*                                             *");
    bb.plain("***********************************************");
}
addtask display_banner before do_build

do_compile(){
    ${CC} ${CFLAGS} ${LDFLAGS} ${WORKDIR}/counter.c -o ${S}/counter
}
do_install(){
    install -d ${D}${bindir}
    install -m 0755 ${S}/counter ${D}${bindir}/
}
```

------------------------------------------------------------------------

## 5. Add Application to Image

In `local.conf` or your image recipe:

``` bitbake
IMAGE_INSTALL:append = " counter"
```

------------------------------------------------------------------------

## 6. Build the Image

``` bash
bitbake core-image-minimal
```

------------------------------------------------------------------------

## 7. Run on Target

``` bash
counter
```

Output:

    Counter: 1
    Counter: 2
    .
    .

-----------------------------------------------------------------------
