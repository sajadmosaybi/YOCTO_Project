
# 🛠️ Yocto Project for STM32MP157

This repository documents how to build a custom embedded Linux image using the **Yocto Project** for the **STM32MP157-DK1** development board.

---

## 📌 About the Project

Yocto is a flexible, powerful build system for creating custom Linux distributions. This setup uses **STMicroelectronics' Yocto BSP layers** to target the STM32MP1 platform.

---

## 📦 Features

- Based on **Poky + OpenEmbedded**
- Includes **ST BSP layers**
- Custom machine for **STM32MP157-DK1**
- Generates bootloader, kernel, and root filesystem
- Suitable for headless or GUI systems

---

## 🧰 Requirements

Install dependencies (Ubuntu 20.04+):

```bash
sudo apt update
sudo apt install gawk wget git diffstat unzip texinfo gcc-multilib   build-essential chrpath socat cpio python3 python3-pip python3-pexpect   xz-utils debianutils iputils-ping libssl-dev
```

---

## 📥 Download Yocto + STM32 Layers

```bash
# Create a working directory
mkdir stm32mp1-yocto && cd stm32mp1-yocto

# Clone ST's OpenEmbedded layers
repo init -u https://github.com/STMicroelectronics/oe-manifest.git -b refs/tags/openstlinux-6.1-yocto-mickledore-mp1-v23.06.21
repo sync
```

---

## 🔧 Initialize Environment

```bash
DISTRO=openstlinux-weston MACHINE=stm32mp1 source layers/meta-st/scripts/envsetup.sh
```

You should now be inside a build directory like: `build-openstlinuxweston-stm32mp1`.

---

## ⚙️ Configure and Build

### Minimal Console Image:
```bash
bitbake st-image-core
```

### Full Weston GUI Image:
```bash
bitbake st-image-weston
```

> First build may take several hours. Internet is required to download sources.

---

## 📤 Output

Images will be located in:

```
build-openstlinuxweston-stm32mp1/tmp-glibc/deploy/images/stm32mp1/
├── FlashLayout_sdcard_stm32mp157c-dk1-trusted.tsv
├── st-image-core-stm32mp1.ext4
├── u-boot-stm32mp157c-dk1-trusted.stm32
├── zImage / uImage
├── stm32mp157c-dk1.dtb
```

---

## 💽 Flash to SD Card

ST provides the `create_sdcard_from_flashlayout.sh` script, or flash manually:

```bash
sudo dd if=st-image-core-stm32mp1.ext4 of=/dev/sdX bs=1M status=progress
```

> Replace `/dev/sdX` with your SD card path.

---

## 🚀 Boot the Board

1. Insert the SD card into STM32MP157-DK1.
2. Connect USB-UART or HDMI.
3. Power the board.
4. You should see U-Boot followed by Linux boot.

---

## 🛠️ Customize with Yocto

You can add packages in `local.conf`:

```conf
IMAGE_INSTALL:append = " nano openssh python3"
```

To modify kernel configuration:

```bash
bitbake -c menuconfig virtual/kernel
```

To add your own application layer:
```bash
yocto-layer create my-layer
```

---

## 🖼️ Screenshots (Optional)

<details>
<summary><strong>1. Serial Console Boot Log</strong></summary>

```
U-Boot 2024.01 (Apr 29 2025)

CPU: STM32MP157C Rev.B
MMC: STM32 SD/MMC: 0
Hit any key to stop autoboot: 0
Booting Linux...

[    0.000000] Linux version 6.1.38 (oe-user@yocto) ...
stm32mp1 login: root
```

</details>

---

## 🙋 Author & Credits

Based on:
- [ST Yocto BSP](https://wiki.st.com/stm32mpu/wiki/STM32MP1_Distribution_Package)
- [Yocto Project](https://www.yoctoproject.org/)
- [OpenEmbedded](https://www.openembedded.org/)

---

## 📄 License

This guide is provided under the MIT License.  
Feel free to fork, modify, and contribute!
