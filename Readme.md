# Makefile in Yocto Project
In the Yocto Project, a Makefile is usually not written directly by you (as in traditional embedded projects). Instead, Yocto uses its own build system called:
- BitBake
- OpenEmbedded metadata
  
Yocto generates and runs Makefiles automatically when building packages that use ```make```.

So in Yocto:
- You don’t control Makefiles directly.
- You control the build using recipes (.bb files).

## 1️⃣ Traditional Makefile (Normal Embedded Project)
In a bare-metal STM32 project (like what you use in STM32CubeIDE), you might write:
```bash
CC=arm-none-eabi-gcc
CFLAGS=-Wall

all: main.elf

main.elf: main.o
	$(CC) main.o -o main.elf

main.o: main.c
	$(CC) $(CFLAGS) -c main.c

clean:
	rm -f *.o *.elf
```
Here:
- make reads the Makefile
- Compiles sources
- Links them
## 2️⃣ How Yocto Uses Makefile
In Yocto:

BitBake executes tasks like:
- do_fetch
- do_configure
- do_compile
- do_install

If your software project contains a Makefile, Yocto will automatically run:
```bash
make
make install
```
## 3️⃣ Example: Using a Makefile Project in Yocto
Let’s say you have this simple C project:
```
myapp/
 ├── myapp.c
 └── Makefile
```
### myapp.c
```bash
#include <stdio.h>

int main() {
    printf("Hello Yocto\n");
    return 0;
}
```
### Makefile
```bash
CC ?= gcc
CFLAGS ?= -Wall

all:
	$(CC) $(CFLAGS) $(LDFLAGS) myapp.c -o myapp

clean:
	rm -f myapp
```
copy ```myapp.c``` and ```MakeFile``` into ```meta-mycustom-layer/recipes-example/myapp/files```.
### Yocto Recipe for This Makefile Project
```bash
cd meta-mycustom-layer/recipes-example
mkdir -p myapp/files
nano myapp_1.0.bb
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
### build myapp
```bash
bitbake myapp
```
### Build the image
```bash
nano conf/local.conf
```
add:
```bash
IMAGE_INSTALL:append = " myapp"
```
### Flash the generated image to the target board
```bash
bitbake core-image-minimal
tmp/deploy/images/stm32mp1/scripts/create_sdcard_from_flashlayout.sh tmp/deploy/images/stm32mp1/flashlayout_core-image-minimal/extensible/FlashLayout_sdcard_stm32mp157a-dk1-extensible.tsv
sudo dd if=tmp/deploy/images/stm32mp1/FlashLayout_sdcard_stm32mp157a-dk1-extensible.raw of=/dev/sdx bs=4M oflag=direct status=progress
```





