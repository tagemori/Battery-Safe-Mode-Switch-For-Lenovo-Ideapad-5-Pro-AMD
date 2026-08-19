# 🔋 Пераключальнік рэжымаў зарадкі акумулятара для Lenovo IdeaPad 5 Pro AMD

<div align="center">

![License](https://img.shields.io/badge/license-MIT-blue.svg)
![Platform](https://img.shields.io/badge/platform-Linux-lightgrey.svg)
![Language](https://img.shields.io/badge/language-C%2B%2B-blue.svg)

**Невялічкая ўтыліта для пераключэння рэжыму кансервацыі акумулятара на наўтбуках Lenovo IdeaPad**

[Беларуская](README-be.md) • [English](README-en.md) • [Русский](README-ru.md)

</div>

---

## 📖 Апісанне

Гэта лёгкая ўтыліта, прызначаная для пераключэння рэжымаў зарадкі акумулятара на наўтбуках Lenovo IdeaPad 5 Pro. **Бяспечны рэжым** абмяжоўвае максімальны зарад акумулятара на ўзроўні **60%**, што дапамагае захаваць здароўе акумулятара пры доўгім падключэнні да сеткі.

### Навошта выкарыстоўваць бяспечны рэжым?

Пастаяннае трыманне акумулятара зараджаным на 100% можа пагоршыць яго стан з цягам часу. Бяспечны рэжым падтрымлівае зарад на ўзроўні 60%, значна памяншаючы знос, калі наўтбук доўга застаецца падключаным да зарадкі.

> ⚠️ **Заўвага:** Гэтая праграма створана як простае рашэнне для сістэм Linux з KDE Plasma.

---

## 🚀 Магчымасці

- 🔌 Пераключэнне паміж абмежаваннямі зараду 60% і 100%
- 📊 Праверка бягучага статусу рэжыму акумулятара
- 🔔 Павядомленні на працоўным стале пры змене рэжыму
- ⚡ Хуткі інтэрфейс каманднага радка

---

## 📦 Залежнасці

Упэўніцеся, што ў вас усталяваны наступныя пакеты:

| Пакет | Прызначэнне |
|-------|-------------|
| `kdesu` | Павышэнне прывілеяў для сістэмных каманд |
| `libnotify-tools` | Павядомленні на працоўным стале |
| `g++` або `clang++` | Кампілятар C++ для зборкі |

### Усталёўка ў Arch-дыстрыбутывах

```bash
sudo pacman -S kdesu libnotify base-devel
```

### Усталёўка ў Debian/Ubuntu

```bash
sudo apt install kdesu libnotify-bin build-essential
```

---

## 🛠️ Зборка з зыходнага коду

```bash
# Кланіраваць рэпазіторый
git clone <url-рэпазіторыя>
cd <каталог-рэпазіторыя>

# Скампіляваць праграму
g++ -o safeModeSwitch safeModeSwitch.cpp

# Ці з дапамогай clang++
clang++ -o safeModeSwitch safeModeSwitch.cpp
```

---

## 💻 Выкарыстанне

### Паказаць даведку
```bash
./safeModeSwitch
```

### Атрымаць бягучы статус
```bash
./safeModeSwitch --get-status
```

### Пераключыць бяспечны рэжым
```bash
./safeModeSwitch --switch-status
```

### Даведнік па камандах

| Каманда | Апісанне |
|---------|----------|
| `--get-status` | Паказаць бягучы рэжым кансервацыі акумулятара |
| `--switch-status` | Пераключыць паміж абмежаваннямі зараду 60% і 100% |

---

## 📝 Як гэта працуе

Утыліта ўзаемадзейнічае з ACPI інтэрфейсам па шляху:
```
/sys/bus/platform/drivers/ideapad_acpi/VPC2004:00/conservation_mode
```

- **Значэнне `1`**: Рэжым кансервацыі ЎКЛ (абмежаванне зараду 60%)
- **Значэнне `0`**: Рэжым кансервацыі ВЫКЛ (зарад 100%)

---

## ⚠️ Важныя заўвагі

- Патрабуе правоў root для змены сістэмных файлаў
- Распрацавана спецыяльна для наўтбукаў Lenovo IdeaPad з драйверам ideapad_acpi
- Праверце сумяшчальнасць з вашай мадэллю перад рэгулярным выкарыстаннем

---

## 📄 Ліцэнзія

Гэты праект ліцэнзуецца паводле **Ліцэнзіі MIT**.

<details>
<summary>Праглядзець ліцэнзію</summary>

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

**Зроблена з ❤️ для карыстальнікаў Lenovo IdeaPad**

</div>
