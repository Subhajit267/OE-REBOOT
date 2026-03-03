# 🚀 OE_REBOOT – Operating Environment Reboot (v6.48.21)

<div align="center">

![C](https://img.shields.io/badge/Language-C-blue?logo=c&logoColor=white)
![Cross‑Platform](https://img.shields.io/badge/Platform-Windows%20%7C%20Linux-yellow)
![Status](https://img.shields.io/badge/Status-Stable-orange)
![Release](https://img.shields.io/badge/Release%20Date-24%20Feb%202026-brightgreen)

**The most advanced release of the rebooted classic console “Operating Environment”**  
A fully modular, cross‑platform C implementation with a rich feature set.

</div>

---

## 📖 Table of Contents

- [Overview](#-overview)
- [What’s New in v6.48.21](#-whats-new-in-v64821)
- [Features](#-features)
- [System Modules](#-system-modules)
- [File Structure](#-file-structure)
- [Building from Source](#-building-from-source)
- [First‑Time Usage](#-firsttime-usage)
- [Command Reference](#-command-reference)
- [Settings Panel](#-settings-panel)
- [Registry Editor](#-registry-editor)
- [Guest Mode](#-guest-mode)
- [File Storage](#-file-storage)
- [Known Issues](#-known-issues)
- [Future Plans](#-future-plans)
- [Contributing](#-contributing)
- [Contact](#-contact)

---

## 🔍 Overview

**OE_REBOOT v6.48.21** is the culmination of a complete rewrite of the original **Operating Environment**, a console‑based pseudo‑OS first created in 2022 as a school hobby project. This version transforms the old monolithic C++ code into a **clean, modular C codebase** with a **Platform Abstraction Layer (PAL)** that enables seamless operation on both **Linux** and **Windows**.

The release focuses on **usability, extensibility, and stability**. It introduces a full‑fledged settings panel, an enhanced registry editor with admin mode, guest user isolation, a colour personalisation wizard, and a built‑in help system – all while preserving the nostalgic retro aesthetic of the original.

Whether you’re a developer curious about console application architecture, a retro enthusiast, or someone interested in how a hobby project can evolve, OE_REBOOT v6.48.21 offers a polished, functional experience.

---

## ✨ What’s New in v6.48.21

Compared to the initial C port (v6.12.56), this release adds:

- **Settings Panel** – centralised configuration for user accounts, reset/restore, and personalisation.
- **Registry Editor Enhancements** – admin mode, temporary app runs, better command handling, and help.
- **Guest Mode** – a restricted environment for demo purposes (limited commands).
- **Colour Change Wizard** – an interactive table to select from 16 background colours, complete with live samples.
- **Reset & Restore** – option to uninstall all apps or trigger a full system reinstall.
- **Dedicated Help System** – context‑sensitive help for the prompt, registry editor, and settings.
- **Improved User Management** – password change now correctly handles the “0” (no password) case and validates input.
- **Modular Menu System** – all menus now use `ui_menu()` for consistent look and behaviour.
- **Numerous Bug Fixes** – screen alignment, input validation, file I/O, and more.

---

## 🎯 Features

| Feature                    | Description                                                                 |
|----------------------------|-----------------------------------------------------------------------------|
| **Cross‑Platform**         | Runs on Linux and Windows via a Platform Abstraction Layer (PAL).          |
| **User Management**        | Create an account with optional password; change/remove password later; change user ID. |
| **Guest Mode**             | Try the environment without creating an account; only basic commands allowed. |
| **Application Installer**  | Install/uninstall apps individually or all at once; status stored in binary `.rg` files. |
| **Command Shell**          | Table‑driven prompt with case‑insensitive commands, guest restrictions, and install/uninstall shortcuts (`inst_<app>`, `unst_<app>`). |
| **Registry Editor**        | Advanced tool for power users; can install all apps, reset, temporarily run apps, manage user accounts, and add keys (admin mode). |
| **Settings Panel**         | Centralised configuration: user accounts, reset & restore, personalisation, help. |
| **Colour Personalisation** | Choose from 16 background colours via a wizard; saved to `looks.bd`. |
| **Bootscreen & Progress Bar** | Classic OE loading screen with a randomised progress bar. |
| **Help System**            | Dedicated help for the main prompt, registry editor, and settings. |
| **Timer & Lockdown**       | Countdown timer and system lockdown after too many failed logins. |
| **Activation Key Placeholders** | Future support for app registration (TicTacToe, Quiz). |

---

## 🧱 System Modules

The codebase is organised into logical modules:

```
app_installer/          – Application registry and installer logic
extras_and_info/        – Improvements display and source viewer
file/                   – Binary file abstraction layer
help_docs/              – Help screens for various parts
pal/                    – Platform Abstraction Layer (Linux/Windows)
setup/                  – First‑run installer
system_core/            – Main command prompt
system_tools/           – Registry editor and settings panel
ui/                     – UI drawing primitives (layout, logo, progress bar)
ui_strings/             – High‑level UI utilities (menus, status, confirmation)
user_management/        – User login, creation, password management
utilities/              – Timer, input validation, activation keys
```

---

## 📁 File Structure

The complete source tree for v6.48.21 is organised as follows:

```
V6.48.21/
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
│           prompt_help.c
│           regedit_help.c
│           settings_help.c
│
├───pal
│   ├───include
│   │       pal.h
│   │
│   └───src
│           pal_kernel.c      # (placeholder for future OS)
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
│   │       settings.h
│   │
│   └───src
│           regedit.c
│           settings.c
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
│           user_guest.c
│           user_id_change.c
│
└───utilities
    ├───include
    │       utils.h
    │
    └───src
            activation.c
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

> **Note:** The first run will launch the installer. Choose trial mode to explore without creating a user, or install to set up a permanent account.

---

## 🚀 First‑Time Usage

1. **Run the program** – you’ll see the OE bootscreen.
2. **If no user exists**, the installer appears:
   - Press **y** to install directly (you’ll be guided to create a user account).
   - Press **n** to enter guest mode (limited commands).
   - Special backdoors: `registryeditor`, `registryeditor_admin`, `prompt` (skip installer).
3. **In normal mode**, type `help` at the `Command->` prompt to see available commands.
4. Explore the **Settings panel** by typing `settings` at the prompt.

---

## 📟 Command Reference (Normal Mode)

| Command               | Description                                   |
|-----------------------|-----------------------------------------------|
| `help`                | Show available commands.                      |
| `exit`                | Exit the program.                             |
| `ver`                 | Display version information.                  |
| `login`               | Return to login screen.                       |
| `registryeditor`      | Enter the registry editor (admin mode available). |
| `settings`            | Open the settings panel.                      |
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

## ⚙️ Settings Panel

The settings panel is accessed via the `settings` command. It offers:

1. **User Accounts** – change or remove your password, change your user ID.
2. **Reset & Restore** – uninstall all applications or perform a full system reinstall.
3. **Personalization** – change the border colour via the interactive wizard.
4. **Help** – brief documentation on settings options.
5. **Exit** – return to the main prompt.

### Colour Change Wizard
- Displays a table of 16 background colours with samples.
- Enter a number (1–16) to select; `e` to exit.
- Colour is saved to `looks.bd` and takes effect after restart.

---

## 🛠️ Registry Editor

The registry editor (`registryeditor` command) is a powerful tool for system manipulation. It features:

- **Admin Mode** – activate by typing `start_admin_reg_edit` (not available in guest mode).
- **Commands**:
  - `install` – install all applications.
  - `temp` – temporarily run TicTacToe or Quiz (admin mode required for TicTacToe; Quiz runs in trial mode without admin).
  - `exit` – return to login screen.
  - `reset` – uninstall all applications (with confirmation).
  - `prompt` – jump directly to the main prompt.
  - `add_key` – install TicTacToe, Quiz, or both (admin only).
  - `user` – reset user account (admin only, with confirmation).
  - `help` – show command list.
  - `clear` / `cls` – clear the screen (the editor redraws automatically).

---

## 👤 Guest Mode

- Activated by pressing **n** during the first‑run installer.
- Also accessible if no user account exists and you choose to test.
- Limited to commands: `help`, `exit`, `ver`, `login`, `registryeditor`.
- Useful for quick demos or testing without creating a permanent user.

---

## 📁 File Storage

All persistent data is stored in binary files for speed and compactness:

| File(s)               | Purpose                                |
|-----------------------|----------------------------------------|
| `user.bd`             | Stored username                        |
| `pwd.bd`              | Stored password (or `"0"` for none)    |
| `*.rg` (e.g., `tictactoe.rg`) | Application registry (0 = uninstalled, 1 = installed) |
| `looks.bd`            | Selected border colour (1–16)          |

Delete these files to reset the system to a fresh state.

---

## 🐞 Known Issues

- **Screen coordinates** are hard‑coded for a 209×50 terminal. May misalign in smaller windows.
- **Application placeholders** – all apps are stubs; real implementations are pending.
- **Input echoing** – in some terminals, characters may appear twice (being addressed).
- **Colour change** requires a restart to take effect (by design).
- **Corrupted binary files** – delete the affected file to reset.
- **Help texts** may not be perfectly aligned.
- **pal_sleep** may not work on all linux systems due to usleep, can be fixed using nanosleep

---

## 🛤️ Future Plans

- Replace placeholder apps with full implementations (Temperature Converter, Calculator, etc.).
- Add dynamic screen size detection.
- Implement raw input mode for better console handling.
- Write unit tests for core modules.
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

<div align="center">

**OE_REBOOT v6.48.21 – From a School Kid’s Messy C++ to Clean, Modular C**  
⭐ Star the repo if you find it interesting! ⭐

</div>

