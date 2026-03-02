# 🚀 OE_REBOOT – Operating Environment Reboot

<div align="center">

![C](https://img.shields.io/badge/Language-C-blue?logo=c&logoColor=white)
![Cross‑Platform](https://img.shields.io/badge/Platform-Windows%20%7C%20Linux-yellow)
![Status](https://img.shields.io/badge/Status-Active%20Development-orange)
![Release](https://img.shields.io/badge/Latest%20Release-v6.48.21-lightgrey)
![Original](https://img.shields.io/badge/Original-C%2B%2B%20(2022)-red)

**A complete reimagining of the classic console‑based “Operating Environment”**  
From a school‑kid’s hurried C++ experiment to a clean, modular C codebase – cross‑platform and ready for the future.

</div>

---

## 📖 Table of Contents

- [Overview](#-overview)
- [Why a Reboot?](#-why-a-reboot)
- [Evolution: Original (2022) → v6.12.56 → v6.48.21](#-evolution-original-2022--v61256--v64821)
- [Architecture at a Glance](#-architecture-at-a-glance)
- [Feature Comparison](#-feature-comparison)
- [Building from Source](#-building-from-source)
- [First‑Time Usage](#-firsttime-usage)
- [Known Issues](#-known-issues)
- [Roadmap to an OS](#-roadmap-to-an-os)
- [Version History](#-version-history)
- [Contributing](#-contributing)
- [Contact](#-contact)

---

## 🔍 Overview

**OE_REBOOT** is a ground‑up rewrite of the original **Operating Environment** – a retro console pseudo‑OS originally written in C++ way back in **2022** by me a school‑going kid, back then as a hobby project. That first version, while functional and fun, was a classic example of **spaghetti code**:

- Everything crammed into a few files with global variables everywhere.
- Relied on Linux‑specific calls (`gotoxy`, `system("clear")`) – no Windows support.
- No separation between UI, logic, and file I/O.
- Hard‑coded screen coordinates, paths, and colors.
- Adding a new feature meant copying and pasting huge blocks of code.

The reboot (started in 2026) tackles these issues head‑on by introducing a **clean, modular C design** with a **Platform Abstraction Layer (PAL)**. The result is a codebase that is:

- ✅ **Cross‑platform** – runs flawlessly on Linux and Windows.
- ✅ **Maintainable** – clear modules (UI, user management, installer, registry, etc.).
- ✅ **Extensible** – new commands and apps are added via simple tables.
- ✅ **Portable** – the PAL can later be swapped for kernel syscalls in a real OS.

The project now comprises two major releases under the OE_REBOOT umbrella:

- **v6.12.56** – The initial C port, featuring a basic prompt, user system, and installer.
- **v6.48.21** – The current release, adding a full settings panel, registry editor, guest mode, color wizard, and much more.

Together, they document the journey from a hobbyist’s messy prototype to a robust, well‑architected simulation.

---

## 🤔 Why a Reboot?

The original OE (circa 2022) was written in a hurry by me exploring C++. While it worked on my Linux machine/ online compiler, it suffered from:

- **Monolithic structure** – over 2000 lines in a single `main.cpp`, with global variables everywhere.
- **Platform lock‑in** – used `gotoxy()`, `system("clear")`, and Linux‑specific headers; impossible to run on Windows without massive changes.
- **No separation of concerns** – UI, logic, and file I/O were tangled together.
- **Hard‑coded everything** – screen coordinates, file names, color codes – all littered throughout the code.
- **Limited extensibility** – adding a new app meant copying an entire block and tweaking a few lines.

The reboot started with a simple goal: **rewrite everything in C, with a clean architecture, and make it cross‑platform**. The result is a codebase that demonstrates how even a chaotic hobby project can evolve into something elegant and future‑proof.

---

## 🔄 Evolution: Original (2022) → v6.12.56 → v6.48.21

| Aspect                | Original (C++ 2022)                | v6.12.56 (C)                        | v6.48.21 (C)                          |
|-----------------------|-------------------------------------|--------------------------------------|----------------------------------------|
| **Language**          | C++                                 | C (C99)                              | C (C99)                                |
| **Structure**         | Monolithic (`main.cpp` + headers)   | Modular (`*.c` / `*.h`)              | Same, with new modules                 |
| **Platform**          | Linux only                          | Linux + Windows (via PAL)            | Same                                   |
| **Screen handling**   | `gotoxy()` + `system("clear")`      | `pal_set_cursor()` + `pal_clear_screen()` | Same, plus `ui_menu()`, `ui_confirm()` |
| **User management**   | Basic text files (`file.txt`)       | Binary `user.bd` / `pwd.bd`          | Same, with better validation           |
| **Application registry** | Individual text files (`.txt`)   | Binary `.rg` files per app           | Same                                   |
| **Command shell**      | Giant `if-else` chain               | Table‑driven dispatch                | Same, with guest restrictions          |
| **Settings**           | Scattered, some in `settings()`     | –                                    | Full panel with user, reset, color     |
| **Registry editor**    | `reg_edit()` with hard‑coded prompts | Basic version                        | Enhanced with admin mode, help         |
| **Color personalization** | `color_change()` (raw ANSI)      | –                                    | Wizard with table preview              |
| **Guest mode**         | –                                   | –                                    | Yes, limited commands                   |
| **Input validation**   | Minimal, prone to crashes           | `util_get_int()`, `util_get_double()` | Same, integrated with UI                |

### 🧠 Key Architectural Changes

1. **Platform Abstraction Layer (PAL)**  
   All OS‑dependent calls (console I/O, file access, sleeping) are routed through PAL. Two implementations exist: `pal_linux.c` and `pal_windows.c`. This makes the code truly cross‑platform.

2. **Binary File Storage**  
   Instead of parsing text files, all persistent data (usernames, passwords, app installation status, theme) is stored in binary format. This is faster, more compact, and avoids string parsing errors.

3. **Table‑Driven Design**  
   Commands, applications, and menus are defined as constant tables. The shell iterates over the table instead of using a long `if-else` chain. Adding a new command is now a one‑line addition.

4. **UI Modularity**  
   `ui_title()`, `ui_menu()`, `ui_confirm()`, `ui_status()` provide consistent, reusable UI elements. Hard‑coded `gotoxy()` calls are gone.

5. **Centralized Error Handling**  
   `ui_status()` with predefined codes replaces scattered `cout << "Error"` messages.

---

## 🏗️ Architecture at a Glance

```
┌─────────────────┐
│     main.c      │  – Entry point, initialises PAL, bootscreen, 
│                 │    checks for existing user → installer or login.
└─────────────────┘
         │
         ▼
┌─────────────────────────────────────┐
│   Platform Abstraction Layer (PAL)   │  – pal_linux.c / pal_windows.c
│   (console, file I/O, strings,       │    Abstracts all OS dependencies.
│    random, sleep)                     │
└─────────────────────────────────────┘
         │
         ▼
┌─────────────────────────────────────┐
│         UI Modules                   │  – ui_elements.c (layout, logo, progressbar)
│                                      │    ui_setup.c (menu, title, status, confirm)
└─────────────────────────────────────┘
         │
         ▼
┌──────────┬──────────┬──────────────┐
│ installer│ prompt   │ regedit      │  – Core interactive shells
│ settings │ help     │ extras       │    (each in its own file)
└──────────┴──────────┴──────────────┘
         │
         ▼
┌─────────────────────────────────────┐
│      User Management                 │  – login.c, user_creation.c,
│                                      │    password_management.c, user_id_change.c
└─────────────────────────────────────┘
         │
         ▼
┌─────────────────────────────────────┐
│      App Installer & Registry        │  – app_installer.c, app_table.c
│                                      │    Manages .rg files, install/uninstall.
└─────────────────────────────────────┘
```

---

## 📊 Feature Comparison

| Feature                          | Original OE (2022) | OE_REBOOT v6.12.56 | OE_REBOOT v6.48.21 |
|----------------------------------|---------------------|---------------------|---------------------|
| Cross‑platform (Linux/Windows)   | ❌ (Linux only)     | ✅                  | ✅                  |
| Modular codebase                 | ❌                  | ✅                  | ✅                  |
| Binary file storage              | ❌ (text)           | ✅                  | ✅                  |
| Table‑driven command shell       | ❌                  | ✅                  | ✅                  |
| User accounts with passwords     | ✅                  | ✅ (improved)       | ✅ (even better)     |
| Guest mode                       | ❌                  | ❌                  | ✅                  |
| Installer / trial mode           | ✅                  | ✅                  | ✅                  |
| Settings panel                   | ❌ (scattered)      | ❌                  | ✅                  |
| Registry editor                  | ✅ (basic)          | ✅ (basic)          | ✅ (admin mode)      |
| Color personalization            | ✅ (simple)         | ❌                  | ✅ (wizard)          |
| Reset & restore                  | ❌                  | ❌                  | ✅                  |
| Help system                      | ❌                  | ❌                  | ✅                  |
| Application placeholders         | ✅ (real apps)      | ✅ (placeholders)   | ✅ (placeholders)    |
| Progress bar / bootscreen        | ✅                  | ✅                  | ✅                  |
| Input validation                 | ❌                  | ✅                  | ✅                  |

---

## 🔧 Building from Source

### Prerequisites
- **C compiler** (GCC, Clang, MSVC) with C99 support.
- **Make** (optional).
- **Windows**: Terminal with ANSI support (Windows Terminal, ConEmu, etc.).
- **Linux**: Any terminal.

### Clone the Repository
```bash
git clone https://github.com/yourusername/oe-reboot.git
cd oe-reboot
```

### Build for Linux
```bash
gcc -D OE_PLATFORM_LINUX -std=c99 *.c -o oe_reboot
./oe_reboot
```

### Build for Windows (MinGW)
```bash
gcc -D OE_PLATFORM_WINDOWS -std=c99 *.c -o oe_reboot.exe
oe_reboot.exe
```

### Build for Windows (MSVC)
```batch
cl /TC /D OE_PLATFORM_WINDOWS /Feoe_reboot.exe *.c
oe_reboot.exe
```

> **Note:** The first run will launch the installer. Choose trial mode to explore without creating a user, or install to set up a permanent account.

---

## 🎮 First‑Time Usage

1. **Run the program** – you’ll see the OE bootscreen.
2. **Installer appears** (if no user exists):
   - Press **y** to install directly (you’ll create a user afterwards).
   - Press **n** to enter guest mode (limited commands).
   - Special backdoors: `registryeditor`, `registryeditor_admin`, `prompt` (skip installer).
3. **In normal mode**, type `help` at the `Command->` prompt to see available commands.
4. Explore the **Settings panel** (`settings` command) to change colors, reset apps, or manage your account.

---

## 🐞 Known Issues

- **Screen coordinates** are hard‑coded for a 209×50 terminal. May misalign in smaller windows.
- **Application placeholders** – all apps are stubs (real logic pending).
- **Input echoing** – in some terminals, characters may appear twice (being addressed).
- **Color change** requires a restart to take effect (by design).
- **Corrupted binary files** – delete `user.bd`/`pwd.bd` to reset.
- **Help texts** may not be perfectly aligned.

---

## 🛤️ Roadmap to an OS

OE_REBOOT is not just a nostalgia project – it’s a **stepping stone** toward a real operating system. The modular architecture and PAL are designed to be replaced by kernel syscalls and drivers in the future.

### Near‑term Goals (v7.x)
- Replace placeholders with fully functional apps (Temperature Converter, Calculator, etc.).
- Implement dynamic screen size detection.
- Add raw input mode for better console handling.
- Write unit tests for core modules.

### Long‑term Vision
- Port the PAL to a custom kernel (e.g., using bare‑metal syscalls).
- Replace file I/O with a real filesystem.
- Turn the command shell into a proper OS shell.
- Evolve the registry editor into a system configuration tool.

The ultimate aim: **a hobby OS that looks and feels like the original OE, but runs on real hardware**.

---

## 📜 Version History

| Version   | Date       | Description                                                                 |
|-----------|------------|-----------------------------------------------------------------------------|
| **v6.48.21** | 2026-02-24 | Settings panel, registry editor enhancements, guest mode, color wizard, reset & restore, help system. |
| **v6.12.56** | 2026-02-21 | Initial C port: PAL, user management, installer, table‑driven prompt, application placeholders. |
| **v6.1.0**   | 2026-02-20 | PAL prototype, basic layout, bootscreen, progress bar.                      |
| *Original*    | 2022       | Monolithic C++ codebase – a school hobby project, written in a hurry.      |

---

## 🤝 Contributing

Contributions, bug reports, and suggestions are warmly welcomed!  
Please follow the existing code style and document your changes.

1. Fork the repository.
2. Create a feature branch.
3. Commit your changes.
4. Open a pull request.

---

## 📬 Contact

**Subhajit Halder**  
📧 subhajithalder267@outlook.com  

---

<div align="center">

**OE_REBOOT – From a School Kid’s Messy C++ to Clean, Modular C**  
⭐ Star the repo if you find it interesting! ⭐

</div>
