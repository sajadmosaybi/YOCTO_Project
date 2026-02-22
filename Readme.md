# Yocto Project – Configure Root Password Using Hashed Password (Step‑By‑Step)

This guide explains how to securely set the **root password** in a Yocto image using a **SHA‑512 hashed password** via `local.conf`.

---

## ✅ Requirements

- Host PC with Linux
- Working Yocto Project build environment
- A build directory (example: `~/yocto/build`)

---

## Step 1 – Go to Your Yocto Build Directory

Open a terminal and run:

```bash
cd ~/yocto/build
```
## Step 2 – Generate a Secure Hashed Password
Create a SHA‑512 password hash:
```bash
openssl passwd -6
```
When prompted:
```bash
Password: mypassword
Verifying - Password: mypassword
```
Example output (this will be different for you):
```bash
$6$abc123$xyz456EncryptedHashValueHere
```
## Notice:
you can generate your own password string with ```openssl passwd -1 mysecretpassword``` but note that ```$``` needs to be escaped with ```\```as shown in the example.
```bash
ROOTPASSWD = "\$6\$abc123\$xyz456EncryptedHashValueHere"
## Step 3 – Edit Yocto Configuration File
```
Open local.conf:
```bash
nano conf/local.conf
```
Add the following at the end of the file:
```bash
EXTRA_IMAGE_FEATURES:remove = " debug-tweaks"
EXTRA_IMAGE_FEATURES:append = " allow-root-login"
ROOTPASSWD = "\$6\$abc123\$xyz456EncryptedHashValueHere"
INHERIT += "extrausers"
EXTRA_USERS_PARAMS = "usermod -p '${ROOTPASSWD}' root;"
```
⚠️ Replace the hash above with your real hash.
## Step 4 – Build the Yocto Image
```bash
bitbake core-image-minimal
```
## Step 5 – Flash and Boot Your Target Board
Flash the generated image to your SD card or device following your board’s instructions.
Boot your embedded Linux system.
## Step 6 – Login Using the New Root Password
```bash
login: root
password: <your_password>
```
## Optional – Verify Password Change
After login, run:
```bash
cat /etc/shadow | grep root
```
You should see the hashed password stored.


