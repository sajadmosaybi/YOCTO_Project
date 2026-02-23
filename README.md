## Development of a Reproducible Embedded Linux Build System Using Yocto and Git Source Integration
The main objective of this project is to integrate a C-based application into a Yocto-based embedded Linux system. The workflow includes creating a custom Yocto layer and recipe, retrieving the source code from a remote Git repository, applying the appropriate cross-compilation toolchain, and packaging the compiled application into the target system image. This approach ensures reproducible builds, platform independence, and seamless deployment on embedded hardware.

``` bash
cd poky/meta-mycustom-layer/recipes-example
mkdir information
nano information.bb
```
add the content below to the ```information.bb``` file.
``` bash
SUMMARY = "Embedded linux Information program from GitHub"
DESCRIPTION = "Embedded linux Information c code"
LICENSE = "MIT"
LIC_FILES_CHKSUM = "file://${COMMON_LICENSE_DIR}/MIT;md5=3da9cfbcb788c80a0384361b4de20420"

SRC_URI = "git://github.com/sajadmosaybi/Source.git;branch=main;protocol=https"

SRCREV = "c287c152fc3b84d3b7600873b10c5f5f1e54d4b8"

S = "${WORKDIR}/git/src"

do_compile() {
    ${CC} ${CFLAGS} ${LDFLAGS} Embedded_Linux_Info.c -o Embedded_Linux_Info
}

do_install() {
    install -d ${D}${bindir}
    install -m 0755 Embedded_Linux_Info ${D}${bindir}
}
```
To find SRCREV (the correct Git commit hash) for a Yocto recipe, follow these steps:
``` bash
git ls-remote <Source address>
```
Fetch data from ```SRC_URI```
``` bash
bitbake -c do_fetch information
```
If everything is correct, you can use the working directory (```tmp/work/cortexa7t2hf-neon-vfpv4-poky-linux-gnueabi/information/1.0-r0```) to fetch the recipe content.

Extracting (unpacking) the source code or files defined in the ```SRC_URI``` variable using ```do_unpack``` command.
``` bash
bitbake -c do_unpack information
```
If everything is correct, you can check the content of ```SRC_URI```, which includes the source code.

🔧 Building (compiling) the source code of a recipe.
``` bash
bitbake -c do_compile information
```
The ```Embedded_Linux_info``` program can be found inside the unpacked directory.
``` bash
file Embedded_Linux_Info
Embedded_Linux_Info: ELF 32-bit LSB pie executable, ARM, EABI5 version 1 (SYSV), dynamically linked, interpreter /lib/ld-linux-armhf.so.3, BuildID[sha1]=9ca2c91440bf97582bd63a843f7b87bc2ab1242a, for GNU/Linux 3.2.0, with debug_info, not stripped
```
In simple terms:

🔧 It copies compiled output into the final package structure before packaging.
```do_install``` is the task responsible for installing built files into the temporary staging directory (```${D}```).
``` bash
bitbake -c do_install information
```
Finally, add the information package to image."
``` bash
nano conf/local.conf
IMAGE_INSTALL:append = " information"
bitbake core-image-minimal
```
