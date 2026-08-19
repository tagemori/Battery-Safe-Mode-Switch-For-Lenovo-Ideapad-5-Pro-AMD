# 🔋 Battery Charge Mode Switch for Lenovo IdeaPad 5 Pro AMD

<div align="center">

![License](https://img.shields.io/badge/license-MIT-blue.svg)
![Platform](https://img.shields.io/badge/platform-Linux-lightgrey.svg)
![Language](https://img.shields.io/badge/language-C%2B%2B-blue.svg)

**A simple utility to toggle battery conservation mode on Lenovo IdeaPad laptops**

[Беларуская](README-be.md) • [English](README-en.md) • [Русский](README-ru.md)

</div>

---

## 📖 Overview

This is a lightweight utility designed to toggle battery conservation modes on Lenovo IdeaPad 5 Pro laptops. The **Safe Mode** limits the maximum battery charge to **60%**, which helps preserve battery health during extended periods of plugged-in usage.

### Why Use Safe Mode?

Keeping your laptop constantly charged at 100% can degrade battery health over time. Safe Mode maintains the charge at 60%, significantly reducing wear when the laptop remains plugged in for long periods.

> ⚠️ **Note:** This utility was created as a simple solution for Linux systems with KDE Plasma.

---

## 🚀 Features

- 🔌 Toggle between 60% and 100% charge limits
- 📊 Check current battery mode status
- 🔔 Desktop notifications for mode changes
- ⚡ Quick command-line interface

---

## 📦 Dependencies

Make sure you have the following packages installed:

| Package | Purpose |
|---------|---------|
| `kdesu` | Privilege escalation for system commands |
| `libnotify-tools` | Desktop notifications |
| `g++` or `clang++` | C++ compiler for building |

### Installation on Arch-based Systems

```bash
sudo pacman -S kdesu libnotify base-devel
```

### Installation on Debian/Ubuntu

```bash
sudo apt install kdesu libnotify-bin build-essential
```

---

## 🛠️ Building from Source

```bash
# Clone the repository
git clone <repository-url>
cd <repository-directory>

# Compile the program
g++ -o safeModeSwitch safeModeSwitch.cpp

# Or using clang++
clang++ -o safeModeSwitch safeModeSwitch.cpp
```

---

## 💻 Usage

### Show Help
```bash
./safeModeSwitch
```

### Get Current Status
```bash
./safeModeSwitch --get-status
```

### Toggle Safe Mode
```bash
./safeModeSwitch --switch-status
```

### Command Reference

| Command | Description |
|---------|-------------|
| `--get-status` | Display current battery conservation mode |
| `--switch-status` | Toggle between 60% and 100% charge limit |

---

## 📝 How It Works

The utility interacts with the ACPI interface at:
```
/sys/bus/platform/drivers/ideapad_acpi/VPC2004:00/conservation_mode
```

- **Value `1`**: Conservation mode ON (60% charge limit)
- **Value `0`**: Conservation mode OFF (100% charge)

---

## ⚠️ Important Notes

- Requires root privileges to modify system files
- Designed specifically for Lenovo IdeaPad laptops with ideapad_acpi driver
- Test compatibility with your specific model before regular use

---

## 📄 License

This project is licensed under the **MIT License**.

<details>
<summary>View License</summary>

```
Copyright © 2025 Tagemori

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
```

</details>

---

<div align="center">

**Made with ❤️ for Lenovo IdeaPad users**

</div>
