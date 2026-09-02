# 🚀 OE_REBOOT – Operating Environment Reboot (v8.42.28)

<div align="center">

![C](https://img.shields.io/badge/Language-C-blue?logo=c\&logoColor=white)
![Cross-Platform](https://img.shields.io/badge/Platform-Windows%20%7C%20Linux-yellow)
![Status](https://img.shields.io/badge/Status-Development-orange)
![Release](https://img.shields.io/badge/Release%20Date-2026-brightgreen)

**A modular console runtime environment evolving into a full operating system**

</div>

---

# 📖 Table of Contents

* Overview
* What’s New in v8.42.28
* Major Improvements from v6.48.21
* Features
* System Modules
* File Structure
* Building from Source
* First-Time Usage
* Command Reference
* Filesystem Commands
* Built-in Tools
* File Storage
* Known Issues
* Future Roadmap
* Contributing
* Contact

---

# 🔍 Overview

**OE_REBOOT v8.42.28** is the current development snapshot of the Operating Environment (OE) project. OE is a modular console runtime written in C that centralises system services behind a Platform Abstraction Layer (PAL) and a small set of system modules. The intent is to evolve OE from a console environment toward a custom kernel and OS infrastructure over future releases.

Core design goals:

- Small, portable C codebase (C99)
- Clear subsystem boundaries (PAL, UI, system tools)
- Simple installer/registry for modular apps
- Console-first UI with structured command shell

---

# ✨ What’s New in v8.42.28

This README is generated from repository metadata (see `system_core/include/branding.h`). Key build metadata:

- Version: v8.42.28
- Build type: (Pre Release Build C and PAL Based)
- Developer: Subhajit Halder
- Build date/time: 26/08/2026 01:40 am

Highlights in this snapshot:

### New / Confirmed Built-in Applications

- Notepad — console-based text editor (system_tools/notepad)
- Calculator — numeric utility (system_tools/calculator)
- System Information Tool — CPU/RAM/disk/uptime summary (system_tools/systeminfo)

### Filesystem Command Layer

PAL-backed filesystem commands are available from the shell (mdr, rdr, ldr, cdr, rmf, cpf, rdf, mvf, pwd). These call into the `pal/` abstraction to provide cross-platform behaviour.

### Branding & PAL

Branding and build metadata are centralised in `system_core/include/branding.h`. PAL provides the platform-specific implementations used throughout the codebase (input, output, string helpers, file/dir operations).

---

# 🔄 Major Improvements from v6.48.21

| Feature                      | v6.48.21 | v8.42.28 |
| ---------------------------- | -------- | -------- |
| Filesystem commands          | ❌        | ✔        |
| Notepad editor               | ❌        | ✔        |
| Calculator tool              | ❌        | ✔        |
| System information utility   | ❌        | ✔        |
| Branding system              | ❌        | ✔        |
| Extended PAL functionality   | Limited  | Expanded |
| Hardware information support | ❌        | ✔        |

Version 8 is an architectural expansion over previous releases, focusing on PAL and modular builtin apps.

---

# 🔁 Comparison: v8.13.07 → v8.42.28

The table below compares major features described for v8.13.07 with the current repository snapshot (v8.42.28). Evidence links point to source files that demonstrate the implementation or change.

| Feature | v8.13.07 | v8.42.28 | Evidence |
| --- | ---: | ---: | --- |
| Version string | 8.13.07 (release doc) | 8.42.28 (branding) | [system_core/include/branding.h](system_core/include/branding.h)
| Centralised branding system | Introduced | Present & updated | [system_core/include/branding.h](system_core/include/branding.h)
| Platform Abstraction Layer (PAL) | Expanded | Further expanded (dir/file commands, kernel stubs) | [pal/include/pal.h](pal/include/pal.h), [pal/src/pal_dir_file_cmds_linux.c](pal/src/pal_dir_file_cmds_linux.c)
| Filesystem command layer (mdr/rdr/ldr/cdr/rmf/cpf/rdf/mvf/pwd) | Introduced | Implemented & exposed in help | [pal/include/pal_dir_file_cmds.h](pal/include/pal_dir_file_cmds.h), [help_docs/src/prompt_help.c](help_docs/src/prompt_help.c)
| Notepad editor | Introduced | Full sources present | [system_tools/notepad/src/notepad.c](system_tools/notepad/src/notepad.c)
| Calculator tool | Introduced | Full sources present | [system_tools/calculator/src/calculator.c](system_tools/calculator/src/calculator.c)
| System information utility | Introduced | Full sources present | [system_tools/systeminfo/src/systeminfo.c](system_tools/systeminfo/src/systeminfo.c)
| Application installer framework | Present | Present (app table + installer code) | [app_installer/src/app_installer.c](app_installer/src/app_installer.c), [app_installer/src/app_table.c](app_installer/src/app_table.c)
| Password handling (storage/hashing) | Basic/unspecified | Salted SHA-256 hashing implemented | [utilities/include/password_hash.h](utilities/include/password_hash.h)
| Terminal UI sizing | Listed as 209×50 in earlier doc | Standardised to 80×25 (README updated) | [README.md](README.md)


# 🎯 Features

| Feature               | Description                                                |
| --------------------- | ---------------------------------------------------------- |
| Cross-Platform        | Runs on Windows and Linux using PAL                        |
| User Management       | User creation, login, password management                  |
| Application Installer | Install or uninstall applications individually or globally |
| Command Shell         | Table-driven command dispatch system                       |
| Filesystem Commands   | Directory and file manipulation via PAL                    |
| Registry Editor       | Advanced system management interface                       |
| Settings Panel        | Centralised configuration utility                          |
| Console UI Engine     | Layout rendering, logo display, progress bar               |
| Help System           | Built-in contextual documentation                          |
| Binary File Storage   | Fast persistent storage for system data                    |

---

# 🧱 System Modules

The repository is organised into independent subsystems. See the `File Structure` section for disk layout.

- `app_installer/`      – Application registry and installer
- `extras_and_info/`    – Improvements viewer and source display
- `file/`               – Binary file abstraction layer
- `help_docs/`          – Built-in help documentation
- `pal/`                – Platform abstraction layer (Windows/Linux backends)
- `setup/`              – Initial installation logic
- `system_core/`        – Main command shell and branding
- `system_tools/`       – System utilities (settings, registry editor, notepad, calculator, systeminfo)
- `ui/`                 – Console rendering system
- `ui_strings/`         – Menu and UI helper functions
- `user_management/`    – Login and user account management
- `utilities/`         – Timer, validation, and helper utilities

---

# 📁 File Structure

Repository root (top-level):

```
main.c
app_installer/
extras_and_info/
file/
help_docs/
pal/
setup/
system_core/
system_tools/
ui/
ui_strings/
user_management/
utilities/
```

Module highlights:

- `system_core/include/branding.h` — centralised build/version strings (used to generate this README)
- `system_tools/notepad/` — built-in text editor implementation (console)
- `system_tools/calculator/` — basic calculator utility
- `system_tools/systeminfo/` — gathers and prints system metrics via PAL

---

# 🔧 Building from Source

### Requirements

- C compiler supporting C99 (GCC/MinGW/Clang)
- Linux or Windows terminal with ANSI escape support

### Linux

```bash
gcc -D OE_PLATFORM_LINUX -std=c99 main.c */src/*.c -o oe
./oe
```

### Windows (MinGW)

```powershell
gcc -D OE_PLATFORM_WINDOWS -std=c99 main.c */src/*.c -o oe.exe
.\oe.exe
```

Notes:

- Source uses the PAL layer; compile-time symbol `OE_PLATFORM_LINUX` or `OE_PLATFORM_WINDOWS` toggles platform-specific code paths.
- Some modules may need explicit include paths depending on your shell/glob handling.

---

# 🚀 First-Time Usage

1. Run the program.
2. If no user exists, the installer will start.
3. Create a user account or enter guest mode.
4. After login, you will reach the OE command prompt:

```
Command->
```

Type `help` to see available commands.

---

# 📟 Command Reference

| Command        | Description                    |
| -------------- | ------------------------------ |
| help           | Show command list              |
| exit           | Exit OE                        |
| ver            | Show version information       |
| login          | Return to login screen         |
| settings       | Open settings panel            |
| registryeditor | Enter registry editor          |
| inst_all       | Install all apps               |
| unst_all       | Uninstall all apps             |
| inst_<app>     | Install specific application   |
| unst_<app>     | Uninstall specific application |

---

# 📂 Filesystem Commands

```
mdr <dir>
rdr <dir>
ldr [dir]
cdr <dir>
rmf <file>
cpf <src> <dst>
rdf <file>
mvf <src> <dst>
pwd
```

These commands provide cross-platform directory/file operations via PAL.

---

# 🛠 Built-in Tools

- Calculator — `system_tools/calculator`
- Notepad — `system_tools/notepad`
- System Information — `system_tools/systeminfo`
- Registry editor, Settings, and other utilities are under `system_tools/`.

---

# 📁 File Storage

OE stores persistent data in binary files under the repository (or configured data directory):

| File     | Purpose              |
| -------- | -------------------- |
| user.bd  | usernames            |
| pwd.bd   | passwords            |
| looks.bd | UI colour settings   |
| *.rg     | application registry |

Removing these files resets local system state.

---

# 🐞 Known Issues

- Terminal size is currently fixed (80×25 recommended).

**Important:** The OE console UI is designed for a fixed terminal size of 80×25 characters; run the program in an emulator or terminal set to this size to ensure correct layout and avoid display overflow.

- Some built-in applications remain partial or simple prototypes.
- Input behaviour may vary depending on terminal emulator.
- Colour changes may require restart to apply.

---

# 🛤 Future Roadmap

Planned items:

- Bootloader development
- Kernel implementation
- HAL support for multiple architectures (arm/arm64/x86/x64)
- Kernel-level filesystem and driver subsystem
- PAL kernel backend to enable lower-level integration

---

# 🤝 Contributing

Contributions welcome — fork, branch, commit, and create a pull request.

---

# 📬 Contact

**Subhajit Halder**
📧 subhajithalder267@outlook.com

---

**OE_REBOOT v8.42.28 – From Console Runtime to Future Operating System**

⭐ Star the repository if you find the project interesting ⭐
