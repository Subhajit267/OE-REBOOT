# 🔧 OE_REBOOT – Operating Environment Reboot (v6.12.56)

<div align="center">

![C](https://img.shields.io/badge/Language-C-blue?logo=c\&logoColor=white)
![Cross‑Platform](https://img.shields.io/badge/Platform-Windows%20%7C%20Linux-yellow)
![Status](https://img.shields.io/badge/Status-Under%20Development-orange)
![Release](https://img.shields.io/badge/Release%20Date-23%20Feb%202026-lightgrey)

**A modern, modular C port of the classic console‑based “Operating Environment”.**  
The original C++ codebase has been completely rewritten from scratch with a clean architecture, paving the way for future integration into a hobby operating system.

</div>

---

## 📌 Overview

**OE_REBOOT** is a ground‑up reimplementation of the beloved **Operating Environment** – a retro console pseudo‑OS that originally featured user accounts, an application registry, a built‑in shell, and several mini‑games. This reboot preserves the original’s look and feel while introducing:

- A **Platform Abstraction Layer (PAL)** for seamless Windows / Linux support.
- A **modular codebase** (separate modules for UI, file I/O, user management, app installer, etc.).
- **Binary file storage** instead of plain text.
- A **table‑driven command shell** that is easy to extend.
- Clean separation of concerns, making it ideal as a foundation for a future OS shell.

The project is **actively developed** and currently in an **alpha state**. The core shell, user management, installer, registry editor, and settings panels are fully functional, but many applications are placeholders and some visual glitches remain. Contributions and feedback are welcome!

---

## ✨ What Works (Core Features)

| Feature                    | Status              | Notes                                                                 |
| -------------------------- | ------------------- | --------------------------------------------------------------------- |
| **PAL (Platform Abstraction)** | ✅ Complete         | Console I/O, file access, string utils, random numbers, echo control |
| **User Management**        | ✅ Complete         | Login, guest mode, password change, user ID change, user creation    |
| **Installer / Trial Mode** | ✅ Complete         | First‑run setup, trial mode (guest), direct install                  |
| **Command Shell (prompt)** | ✅ Complete         | Table‑driven, case‑insensitive, guest restrictions, install/uninstall|
| **Registry Editor**        | ✅ Complete         | Basic version (admin mode, install/reset/temp)                       |
| **Settings Panel**         | ✅ Complete         | User accounts, reset & restore, border color personalization         |
| **Application Placeholders**| ⚠️ Partial         | All apps show messages; real implementations pending                 |
| **Bootscreen & Progress Bar**| ✅ Complete       | Randomized loading bar (original OE style)                           |
| **Help System**            | ✅ Complete         | Prompt help, registry help, settings help                            |
| **Extras (source view, improvements)** | ⚠️ Partial | `source_display` is a placeholder                                    |

---

## 🖥️ System Modules

### 📁 Platform Abstraction Layer (PAL)
- Console functions (`pal_print`, `pal_set_cursor`, `pal_clear_screen`, …)
- String wrappers (`pal_strlen`, `pal_strcmp`, `pal_itoa`, …)
- File I/O (`pal_file_open_*`, `pal_file_read`, …)
- Random number generator (`pal_srand`, `pal_rand`)
- Echo control (`pal_set_echo`) – used for password entry

### 👤 User Management
- `user.bd` / `pwd.bd` binary storage
- `login()`, `add_user()`, `password_change()`, `userid_change()`
- Guest mode (`reg_status = 1`)

### 🛠️ Installer & Registry
- `app_installer` module with `app_t` table
- Binary registry files (`*.rg`) store installation status
- `install_all`, `uninstall_all`, per‑app install/uninstall

### 🖥️ UI Elements
- `layout()` draws a 209×50 bordered box with centered headers
- `logo()` – enlarged tri‑colour OE logo
- `progressbar()` – randomised loading bar
- `ui_title`, `ui_menu`, `ui_confirm`, `ui_status`

### 📚 Help System
- `help_show_prompt()`, `help_show_regedit()`, `help_show_settings()`

### ⚙️ Settings
- User accounts (password change, user ID change)
- Reset & restore (uninstall all apps)
- Personalization (border colour selection)

### 🎮 Application Placeholders (to be replaced)
- TicTacToe, Quiz, Temp Converter, Calculator, Equation Solvers, Area of Triangle
- All currently show a placeholder message.

---

## 🔧 Building & Running

### Prerequisites
- **C compiler** (GCC, Clang, MSVC) with C99 support
- **Make** (optional)
- **Windows**: a terminal that supports ANSI escape codes (Windows Terminal, ConEmu, etc.)
- **Linux**: any terminal

### Clone & Build
```bash
git clone https://github.com/yourusername/oe-reboot.git
cd oe-reboot
```

#### Linux / macOS
```bash
gcc -std=c99 -I. -o oe_reboot main.c */*.c */*/*.c
./oe_reboot
```

#### Windows (MinGW)
```bash
gcc -std=c99 -I. -o oe_reboot.exe main.c */*.c */*/*.c
oe_reboot.exe
```

#### Windows (MSVC)
```batch
cl /TC /I. /Feoe_reboot.exe main.c app_installer\src\*.c extras_and_info\src\*.c file\src\*.c help_docs\src\*.c pal\src\pal_windows.c setup\src\*.c system_core\src\*.c system_tools\src\*.c ui\src\*.c ui_strings\src\*.c user_management\src\*.c utilities\src\*.c
```

> **Note:** The first run will take you through the installer. Choose trial mode to test without creating a user, or install to set up a permanent account.

---

## 🎮 Using OE_REBOOT

### First Run
- If no user exists, you’ll be asked to **install** or **try the program** (trial mode).
- Trial mode gives you a guest shell with limited commands (`help`, `exit`, `login`, `registryeditor`).
- Installing creates a user account (with optional password) and grants full access.

### Commands
At the `Command->` prompt, type:

| Command               | Description                                   | Guest Allowed? |
| --------------------- | --------------------------------------------- | -------------- |
| `help`                | Show available commands                       | ✅             |
| `exit`                | Exit the program                              | ✅             |
| `ver`                 | Show version                                  | ✅             |
| `login`               | Re‑authenticate (return to login)             | ✅             |
| `registryeditor`      | Enter registry editor (limited in guest mode) | ✅             |
| `settings`            | Open settings panel                           | ❌             |
| `inst_all`            | Install all apps                              | ❌             |
| `unst_all`            | Uninstall all apps                            | ❌             |
| `inst_<app>`          | Install a specific app                        | ❌             |
| `unst_<app>`          | Uninstall a specific app                      | ❌             |
| `<app name>`          | Run an app (if installed)                     | ❌             |

Available app names: `tictactoe`, `quiz`, `temp_conv`, `calculator`, `eqn_solve`, `quad_eqn_solve`, `atc`.

### Guest Mode
- `reg_status = 1` indicates guest.
- Only `help`, `exit`, `ver`, `login`, `registryeditor` are allowed.
- Useful for a quick demo without setting up an account.

---

## 🐞 Known Issues

- **Screen coordinates** may be off in terminals other than the developer’s (assumes 209×50).
- **Application placeholders** – none of the apps are functional yet.
- **Input echoing** – in some terminals, characters may appear twice; this is being addressed.
- **Color personalisation** – changing the border color requires a restart (by design).
- **No error recovery** for corrupted binary files; delete `user.bd`/`pwd.bd` to reset.
- **Progress bar** may still pause briefly at 100% (cosmetic).
- **Help texts** may not be perfectly aligned.

---

## 🚧 Roadmap

- [ ] **Replace placeholders with real app implementations** (starting with temperature converter).
- [ ] **Improve screen coordinate system** to adapt to any terminal size.
- [ ] **Add more robust error handling** (file corruption, invalid input).
- [ ] **Write unit tests** for core modules.
- [ ] **Prepare for integration into a hobby OS kernel** (replace PAL with kernel syscalls).

---

## 🤝 Contributing

This is a personal learning project, but contributions, bug reports, and suggestions are very welcome!  
Feel free to open an issue or submit a pull request. Please keep the code style consistent and document your changes.

---

## 📄 License

[MIT](LICENSE) (or choose your preferred license)

---

## 👨‍💻 Developer

**Subhajit Halder**  
📧 subhajithalder267@outlook.com

---

## 🕰️ Version History

| Version | Date       | Description                              |
| ------- | ---------- | ---------------------------------------- |
| v6.12.56  | 2026-02-23 | Core shell, user management, installer, settings, PAL |
| v6.1.0  | 2026-02-20 | Initial PAL implementation, basic layout |

---

<div align="center">

*OE_REBOOT is a work in progress – stay tuned for updates!*

</div>
