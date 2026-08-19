# 🔋 Переключатель режимов зарядки аккумулятора для Lenovo IdeaPad 5 Pro AMD

<div align="center">

![License](https://img.shields.io/badge/license-MIT-blue.svg)
![Platform](https://img.shields.io/badge/platform-Linux-lightgrey.svg)
![Language](https://img.shields.io/badge/language-C%2B%2B-blue.svg)

**Небольшая утилита для переключения режима консервации аккумулятора на ноутбуках Lenovo IdeaPad**

[Беларуская](README-be.md) • [English](README-en.md) • [Русский](README-ru.md)

</div>

---

## 📖 Описание

Это легковесная утилита, предназначенная для переключения режимов зарядки аккумулятора на ноутбуках Lenovo IdeaPad 5 Pro. **Безопасный режим** ограничивает максимальный заряд аккумулятора на уровне **60%**, что помогает сохранить здоровье батареи при длительном подключении к сети.

### Зачем использовать безопасный режим?

Постоянное поддержание аккумулятора заряженным на 100% может ухудшить его состояние со временем. Безопасный режим поддерживает заряд на уровне 60%, значительно снижая износ, когда ноутбук долго остаётся подключённым к зарядке.

> ⚠️ **Примечание:** Эта программа создана как простое решение для систем Linux с KDE Plasma.

---

## 🚀 Возможности

- 🔌 Переключение между ограничениями заряда 60% и 100%
- 📊 Проверка текущего статуса режима аккумулятора
- 🔔 Уведомления на рабочем столе при смене режима
- ⚡ Быстрый интерфейс командной строки

---

## 📦 Зависимости

Убедитесь, что у вас установлены следующие пакеты:

| Пакет | Назначение |
|-------|------------|
| `kdesu` | Повышение привилегий для системных команд |
| `libnotify-tools` | Уведомления на рабочем столе |
| `g++` или `clang++` | Компилятор C++ для сборки |

### Установка в Arch-дистрибутивах

```bash
sudo pacman -S kdesu libnotify base-devel
```

### Установка в Debian/Ubuntu

```bash
sudo apt install kdesu libnotify-bin build-essential
```

---

## 🛠️ Сборка из исходного кода

```bash
# Клонировать репозиторий
git clone <url-репозитория>
cd <каталог-репозитория>

# Скомпилировать программу
g++ -o safeModeSwitch safeModeSwitch.cpp

# Или с помощью clang++
clang++ -o safeModeSwitch safeModeSwitch.cpp
```

---

## 💻 Использование

### Показать справку
```bash
./safeModeSwitch
```

### Получить текущий статус
```bash
./safeModeSwitch --get-status
```

### Переключить безопасный режим
```bash
./safeModeSwitch --switch-status
```

### Справочник по командам

| Команда | Описание |
|---------|----------|
| `--get-status` | Показать текущий режим консервации аккумулятора |
| `--switch-status` | Переключить между ограничениями заряда 60% и 100% |

---

## 📝 Как это работает

Утилита взаимодействует с ACPI интерфейсом по пути:
```
/sys/bus/platform/drivers/ideapad_acpi/VPC2004:00/conservation_mode
```

- **Значение `1`**: Режим консервации ВКЛ (ограничение заряда 60%)
- **Значение `0`**: Режим консервации ВЫКЛ (заряд 100%)

---

## ⚠️ Важные замечания

- Требует прав root для изменения системных файлов
- Разработано специально для ноутбуков Lenovo IdeaPad с драйвером ideapad_acpi
- Проверьте совместимость с вашей моделью перед регулярным использованием

---

## 📄 Лицензия

Этот проект лицензируется согласно **Лицензии MIT**.

<details>
<summary>Просмотреть лицензию</summary>

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

**Сделано с ❤️ для пользователей Lenovo IdeaPad**

</div>
