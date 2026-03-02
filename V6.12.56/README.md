# 🔧 OE_REBOOT – Operating Environment Reboot (v6.12.56)

<div align="center">

![C](https://img.shields.io/badge/Language-C-blue?logo=c&logoColor=white)
![Cross‑Platform](https://img.shields.io/badge/Platform-Windows%20%7C%20Linux-yellow)
![Status](https://img.shields.io/badge/Status-Under%20Development-orange)
![Release](https://img.shields.io/badge/Release%20Date-23%20Feb%202026-lightgrey)

**The initial C port of the classic console‑based “Operating Environment”.**  
A complete rewrite from scratch, introducing modularity and cross‑platform support.

</div>

---

## 📖 Table of Contents

- [Overview](#-overview)
- [What’s in v6.12.56](#-whats-in-v61256)
- [Features](#-features)
- [System Modules](#-system-modules)
- [File Structure](#-file-structure)
- [Building from Source](#-building-from-source)
- [First‑Time Usage](#-firsttime-usage)
- [Command Reference](#-command-reference)
- [Guest Mode](#-guest-mode)
- [File Storage](#-file-storage)
- [Known Issues](#-known-issues)
- [Future Plans](#-future-plans)
- [Contributing](#-contributing)
- [Contact](#-contact)

---

## 🔍 Overview

**OE_REBOOT v6.12.56** is the first fruits of a complete rewrite of the original **Operating Environment** – a console‑based pseudo‑OS originally written in C++ back in 2022 as a school hobby project. This version strips away the old monolithic, Linux‑only C++ code and rebuilds it from the ground up in **C**, with a clean, modular architecture and a **Platform Abstraction Layer (PAL)** that makes it truly cross‑platform (Linux & Windows).

While still in an alpha state, v6.12.56 lays the foundation for everything that follows. It provides a working **command shell**, **user management**, an **application installer**, and a basic **registry editor** – all running inside a retro‑styled bordered console.

---

## ✨ What’s in v6.12.56

| Feature                    | Status              | Notes                                                                 |
| -------------------------- | ------------------- | --------------------------------------------------------------------- |
| **PAL (Platform Abstraction)** | ✅ Complete         | Console I/O, file access, string utils, random numbers, echo control |
| **User Management**        | ✅ Complete         | Login, password change, user ID change, user creation                |
| **Installer / Trial Mode** | ✅ Complete         | First‑run setup, trial mode (guest), direct install                  |
| **Command Shell (prompt)** | ✅ Complete         | Table‑driven, case‑insensitive, install/uninstall shortcuts          |
| **Registry Editor**        | ✅ Complete         | Basic version (install/reset/temp, no admin mode yet)                |
| **Application Placeholders**| ⚠️ Partial         | All apps show messages; real implementations pending                 |
| **Bootscreen & Progress Bar**| ✅ Complete       | Randomized loading bar (original OE style)                           |
| **Help System**            | ⚠️ Partial         | Only basic prompt help exists                                         |
| **Settings Panel**         | ❌ Not yet          | Will be introduced in v6.48.21                                       |
| **Extras (source view, improvements)** | ⚠️ Partial | `source_display` is a placeholder                                    |

---

## 🎯 Features

- **Cross‑platform** – runs on Linux and Windows via PAL.
- **User accounts** – create an account with optional password; change password or user ID later.
- **Guest mode** – try the environment without creating an account (limited commands).
- **Application installer** – install/uninstall apps individually or all at once; status stored in binary `.rg` files.
- **Table‑driven command shell** – easy to extend; supports `inst_<app>` and `unst_<app>` shortcuts.
- **Registry editor** – basic tool to install all apps, reset, or temporarily run TicTacToe/Quiz.
- **Bootscreen & progress bar** – classic OE loading animation.
- **Timer & lockdown** – countdown and exit after too many failed logins.
- **Binary file storage** – all persistent data in compact binary files.

---

## 🧱 System Modules

The codebase is organised into logical modules:

```
app_installer/          – Application registry and installer logic
extras_and_info/        – Improvements display and source viewer (placeholder)
file/                   – Binary file abstraction layer
help_docs/              – Help screens (basic)
pal/                    – Platform Abstraction Layer (Linux/Windows)
setup/                  – First‑run installer
system_core/            – Main command prompt
system_tools/           – Registry editor (basic)
ui/                     – UI drawing primitives (layout, logo, progress bar)
ui_strings/             – High‑level UI utilities (menu, title, status)
user_management/        – User login, creation, password management
utilities/              – Timer, input validation, activation keys (stubs)
```

---

## 📁 File Structure

```
V6.12.56/
│   main.c
│   README.md
│
├───app_installer
│   ├───include
│   │       app_installer.h
│   │       app_table.h
│   │
│   └───src
│           app_installer.c
│           app_table.c
│
├───extras_and_info
│   ├───include
│   │       extras.h
│   │
│   └───src
│           improvements.c
│           source_display.c
│
├───file
│   ├───include
│   │       file.h
│   │
│   └───src
│           file.c
│
├───help_docs
│   ├───include
│   │       help.h
│   │
│   └───src
│           prompt_help.c          # Basic help for prompt
│           regedit_help.c          # Placeholder
│           settings_help.c         # Placeholder (unused)
│
├───pal
│   ├───include
│   │       pal.h
│   │
│   └───src
│           pal_linux.c
│           pal_windows.c
│
├───setup
│   ├───include
│   │       installer.h
│   │
│   └───src
│           installer.c
│
├───system_core
│   ├───include
│   │       prompt.h
│   │
│   └───src
│           prompt.c
│
├───system_tools
│   ├───include
│   │       regedit.h
│   │
│   └───src
│           regedit.c               # Basic registry editor
│
├───ui
│   ├───include
│   │       bootscreen.h
│   │       ui_elements.h
│   │
│   └───src
│           bootscreen.c
│           ui_elements.c
│
├───ui_strings
│   ├───include
│   │       ui_setup.h
│   │
│   └───src
│           ui_setup.c
│
├───user_management
│   ├───include
│   │       user.h
│   │
│   └───src
│           login.c
│           password_management.c
│           user_creation.c
│           user_id_change.c
│           (user_guest.c not yet present)
│
└───utilities
    ├───include
    │       utils.h
    │
    └───src
            activation.c            # Stub
            input_validation.c
            timer.c
```

---

## 🔧 Building from Source

### Prerequisites
- **C compiler** (GCC, Clang, MSVC) with C99 support.
- **Make** (optional).
- **Windows**: A terminal that supports ANSI escape codes (Windows Terminal, ConEmu, etc.).
- **Linux**: Any terminal.

### Clone & Build
```bash
git clone https://github.com/yourusername/oe-reboot.git
cd oe-reboot
```

#### Linux
```bash
gcc -D OE_PLATFORM_LINUX -std=c99 -Iapp_installer/include -Iextras_and_info/include -Ifile/include -Ihelp_docs/include -Ipal/include -Isetup/include -Isystem_core/include -Isystem_tools/include -Iui/include -Iui_strings/include -Iuser_management/include -Iutilities/include \
    main.c \
    app_installer/src/*.c \
    extras_and_info/src/*.c \
    file/src/*.c \
    help_docs/src/*.c \
    pal/src/pal_linux.c \
    setup/src/*.c \
    system_core/src/*.c \
    system_tools/src/*.c \
    ui/src/*.c \
    ui_strings/src/*.c \
    user_management/src/*.c \
    utilities/src/*.c \
    -o oe_reboot
./oe_reboot
```

#### Windows (MinGW)
```bash
gcc -D OE_PLATFORM_WINDOWS -std=c99 -Iapp_installer/include -Iextras_and_info/include -Ifile/include -Ihelp_docs/include -Ipal/include -Isetup/include -Isystem_core/include -Isystem_tools/include -Iui/include -Iui_strings/include -Iuser_management/include -Iutilities/include \
    main.c \
    app_installer/src/*.c \
    extras_and_info/src/*.c \
    file/src/*.c \
    help_docs/src/*.c \
    pal/src/pal_windows.c \
    setup/src/*.c \
    system_core/src/*.c \
    system_tools/src/*.c \
    ui/src/*.c \
    ui_strings/src/*.c \
    user_management/src/*.c \
    utilities/src/*.c \
    -o oe_reboot.exe
oe_reboot.exe
```

#### Windows (MSVC)
```batch
cl /TC /D OE_PLATFORM_WINDOWS /Iapp_installer\include /Iextras_and_info\include /Ifile\include /Ihelp_docs\include /Ipal\include /Isetup\include /Isystem_core\include /Isystem_tools\include /Iui\include /Iui_strings\include /Iuser_management\include /Iutilities\include /Feoe_reboot.exe main.c app_installer\src\*.c extras_and_info\src\*.c file\src\*.c help_docs\src\*.c pal\src\pal_windows.c setup\src\*.c system_core\src\*.c system_tools\src\*.c ui\src\*.c ui_strings\src\*.c user_management\src\*.c utilities\src\*.c
oe_reboot.exe
```

> **Note:** The first run will take you through the installer. Choose trial mode to test without creating a user, or install to set up a permanent account.

---

## 🚀 First‑Time Usage

1. **Run the program** – you’ll see the OE bootscreen.
2. **If no user exists**, the installer appears:
   - Press **y** to install directly (you’ll be guided to create a user account).
   - Press **n** to enter guest mode (limited commands).
   - Special backdoors: `registryeditor`, `prompt` (skip installer).
3. **In normal mode**, type `help` at the `Command->` prompt to see available commands.
4. Explore the **registry editor** by typing `registryeditor`.

---

## 📟 Command Reference (Normal Mode)

| Command               | Description                                   |
|-----------------------|-----------------------------------------------|
| `help`                | Show available commands.                      |
| `exit`                | Exit the program.                             |
| `ver`                 | Display version information.                  |
| `login`               | Return to login screen.                       |
| `registryeditor`      | Enter the registry editor (basic).            |
| `inst_all`            | Install all applications.                      |
| `unst_all`            | Uninstall all applications.                    |
| `inst_<app>`          | Install a specific application (e.g., `inst_tictactoe`). |
| `unst_<app>`          | Uninstall a specific application.              |
| `<app name>`          | Run an installed application (e.g., `tictactoe`). |

**Available app names:**  
`tictactoe`, `quiz`, `temp_conv`, `calculator`, `eqn_solve`, `quad_eqn_solve`, `atc`.

### Guest Mode Commands
In guest mode, only `help`, `exit`, `ver`, `login`, and `registryeditor` are allowed.

---

## 👤 Guest Mode

- Activated by pressing **n** during the first‑run installer.
- Also accessible if no user account exists and you choose to test.
- Limited to commands: `help`, `exit`, `ver`, `login`, `registryeditor`.
- Useful for quick demos or testing without creating a permanent user.

---

## 📁 File Storage

All persistent data is stored in binary files:

| File(s)               | Purpose                                |
|-----------------------|----------------------------------------|
| `user.bd`             | Stored username                        |
| `pwd.bd`              | Stored password (or `"0"` for none)    |
| `*.rg` (e.g., `tictactoe.rg`) | Application registry (0 = uninstalled, 1 = installed) |

Delete these files to reset the system to a fresh state.

---

## 🐞 Known Issues

- **Screen coordinates** are hard‑coded for a 209×50 terminal. May misalign in smaller windows.
- **Application placeholders** – none of the apps are functional yet.
- **Input echoing** – in some terminals, characters may appear twice (being addressed).
- **No error recovery** for corrupted binary files; delete the affected file to reset.
- **Progress bar** may pause briefly at 100% (cosmetic).
- **Help texts** minimal; extended help will come in later versions.
- **Registry editor** lacks admin mode and advanced features (planned for v6.48.21).

---

## 🛤️ Future Plans

- Add a full settings panel (v6.48.21).
- Enhance registry editor with admin mode and more commands.
- Replace placeholder apps with real implementations.
- Improve screen coordinate system to adapt to any terminal size.
- Add robust error handling and unit tests.
- Evolve towards a real OS kernel by replacing PAL with syscalls.

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

## 🕰️ Version History

| Version | Date       | Description                              |
| ------- | ---------- | ---------------------------------------- |
| v6.12.56 | 2026-02-23 | Initial C port: PAL, user management, installer, table‑driven prompt, application placeholders, basic registry editor. |
| v6.1.0   | 2026-02-20 | PAL prototype, basic layout, bootscreen, progress bar. |

---

<div align="center">

*OE_REBOOT v6.12.56 – The foundation for a modular, cross‑platform OE.*  
⭐ Star the repo if you find it interesting! ⭐

</div>
