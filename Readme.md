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
