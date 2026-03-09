# 🚀 OE_REBOOT – Operating Environment Reboot (v8.13.07)

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
* What’s New in v8.13.07
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

**OE_REBOOT v8.13.07** represents the next major milestone in the evolution of the **Operating Environment** project.

Originally created as a small experimental console program, OE has grown into a **modular runtime environment written entirely in C**, featuring:

• A clean subsystem architecture
• A powerful **Platform Abstraction Layer (PAL)**
• Built-in system tools and applications
• Filesystem command support
• Modular application installer framework
• Console UI engine

Version 8 expands OE beyond a simple console environment and begins preparing the codebase for the **future introduction of a custom kernel and operating system infrastructure**.

---

# ✨ What’s New in v8.13.07

Version 8 introduces several major improvements over previous releases.

### New Built-in Applications

• **Notepad** – console-based text editor
• **Calculator** – numeric calculation utility
• **System Information Tool** – displays CPU, RAM, disk usage, and uptime

---

### Filesystem Command Layer

A new filesystem command interface has been added to the shell.

Commands include:

```
mdr   – create directory
rdr   – remove directory
ldr   – list directory
cdr   – change directory
rmf   – remove file
cpf   – copy file
rdf   – read file
mvf   – move file
pwd   – print working directory
```

These commands are implemented through PAL directory and file abstractions.

---

### Branding System

A centralized **branding system** was introduced.

```
branding.h
```

This file stores global OE metadata such as:

• version information
• developer name
• build type
• system identifiers

This eliminates hardcoded version strings across the project.

---

### Expanded Platform Abstraction Layer

PAL has been extended to support:

• filesystem directory commands
• system information retrieval
• math utilities
• additional runtime services

PAL now acts as a **foundation layer for the future OE kernel backend**.

---

# 🔄 Major Improvements from v6.48.21

Version 8 significantly expands the capabilities of OE compared to the previous stable release.

| Feature                      | v6.48.21 | v8.13.07 |
| ---------------------------- | -------- | -------- |
| Filesystem commands          | ❌        | ✔        |
| Notepad editor               | ❌        | ✔        |
| Calculator tool              | ❌        | ✔        |
| System information utility   | ❌        | ✔        |
| Branding system              | ❌        | ✔        |
| Extended PAL functionality   | Limited  | Expanded |
| Hardware information support | ❌        | ✔        |

Version 8 therefore represents a **major architectural expansion** rather than a minor feature update.

---

# 🎯 Features

| Feature               | Description                                                |
| --------------------- | ---------------------------------------------------------- |
| Cross-Platform        | Runs on Windows and Linux using PAL                        |
| User Management       | User creation, login, password management                  |
| Application Installer | Install or uninstall applications individually or globally |
| Command Shell         | Table-driven command dispatch system                       |
| Filesystem Commands   | Directory and file manipulation                            |
| Registry Editor       | Advanced system management interface                       |
| Settings Panel        | Centralised configuration utility                          |
| Console UI Engine     | Layout rendering, logo display, progress bar               |
| Help System           | Built-in contextual documentation                          |
| Binary File Storage   | Fast persistent storage for system data                    |

---

# 🧱 System Modules

The OE codebase is organized into independent subsystems.

```
app_installer/      – Application registry and installer
extras_and_info/    – Improvements viewer and source display
file/               – Binary file abstraction layer
help_docs/          – Built-in help documentation
pal/                – Platform abstraction layer
setup/              – Initial installation logic
system_core/        – Main command shell
system_tools/       – System utilities (settings, registry editor, etc.)
ui/                 – Console rendering system
ui_strings/         – Menu and UI helper functions
user_management/    – Login and user account management
utilities/          – Timer, validation, and helper utilities
```

---

# 📁 File Structure

```
V8.13.07/
│   main.c
│
├── app_installer
├── extras_and_info
├── file
├── help_docs
├── pal
├── setup
├── system_core
├── system_tools
├── ui
├── ui_strings
├── user_management
└── utilities
```

Compared to v6, this version introduces additional modules inside:

```
system_tools/
pal/
system_core/
```

to support new runtime capabilities.

---

# 🔧 Building from Source

### Requirements

• C compiler supporting C99
• Linux or Windows terminal with ANSI escape support

---

### Linux

```
gcc -D OE_PLATFORM_LINUX -std=c99 main.c */src/*.c -o oe
./oe
```

---

### Windows (MinGW)

```
gcc -D OE_PLATFORM_WINDOWS -std=c99 main.c */src/*.c -o oe.exe
oe.exe
```

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

Version 8 introduces filesystem interaction commands:

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

These commands allow OE to manipulate the host filesystem through PAL.

---

# 🛠 Built-in Tools

OE Version 8 includes several built-in utilities:

Calculator
Notepad
System Information Tool

Additional application placeholders remain available through the installer system.

---

# 📁 File Storage

OE stores persistent data in binary files:

| File     | Purpose              |
| -------- | -------------------- |
| user.bd  | username             |
| pwd.bd   | password             |
| looks.bd | UI colour settings   |
| *.rg     | application registry |

Deleting these files resets the system state.

---

# 🐞 Known Issues

• Terminal size is currently fixed (209×50 recommended)
• Some built-in applications are still placeholders
• Input behaviour may vary depending on terminal
• Colour changes require restart

---

# 🛤 Future Roadmap

Planned future milestones include:

• Bootloader development
• Kernel implementation
• Hardware abstraction layer (HAL)
• Kernel-level filesystem
• Driver subsystem
• PAL kernel backend

These additions will eventually allow OE to run **directly on custom operating system infrastructure**.

---

# 🤝 Contributing

Contributions, ideas, and improvements are welcome.

1. Fork the repository
2. Create a feature branch
3. Commit changes
4. Submit a pull request

---

# 📬 Contact

**Subhajit Halder**
📧 [subhajithalder267@outlook.com](mailto:subhajithalder267@outlook.com)

---

<div align="center">

**OE_REBOOT v8.13.07 – From Console Runtime to Future Operating System**

⭐ Star the repository if you find the project interesting ⭐

</div>
