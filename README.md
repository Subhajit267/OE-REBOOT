## 📘 OE_REBOOT – Operating Environment Reboot

**Author:** Subhajit Halder  
**Project Type:** Console‑based System Simulation (C)  
**Platforms:** Linux, Windows  

---

### 🔍 Overview

OE_REBOOT is a retro‑style console environment that simulates a complete operating system’s user interface and system tools. It is a **reboot** of an original **OE** project, which was written in **C++**. This version is built from the ground up in **C** using a clean, modular architecture with a Platform Abstraction Layer (PAL) for cross‑platform support.

The project features:

- A **command prompt** with a guest/normal user mode.
- **User management** (login, password change, user ID change, guest access).
- An **application installer** with persistent registry files (`.rg`).
- A **Registry Editor** for advanced system configuration (admin mode available).
- A **Settings panel** for personalization (border color), reset/restore, and help.
- Built‑in **timer, activation key verification, and countdown lockdown**.
- A **progress bar** and **bootscreen** for each application.

All this runs inside a bordered layout with colored text, giving a nostalgic “operating environment” feel – entirely in the console. The ultimate goal is to evolve this simulation into a lightweight **operating system kernel** in the future.

---

### 🎯 Purpose (Why OE_REBOOT?)

This project was created to demonstrate:

- **Modular C programming** – separation of concerns via PAL, UI, installer, user modules.
- **Cross‑platform development** – a single codebase runs on Linux and Windows.
- **Persistent state management** – binary files store user data, application installation status, and theme settings.
- **Interactive console UI** – menus, forms, and real‑time feedback without external libraries.
- **Security concepts** – password hiding, guest restrictions, lockdown timers.
- **Extensibility** – new applications can be added by simply updating the app table.

It is not meant to be a full OS, but a simulation that shows how such systems are structured – and a foundation for a future OS project.

---

### 🧱 Architecture

```
┌─────────────────┐
│   main.c        │  Entry point: initialises PAL, shows bootscreen,
│                 │  checks for existing user → installer or login.
└─────────────────┘
         │
         ▼
┌─────────────────────────────────────┐
│ PAL (pal_linux.c / pal_windows.c)   │  Platform Abstraction Layer –
│                                     │  console I/O, file I/O, strings,
│                                     │  random numbers, sleep.
└─────────────────────────────────────┘
         │
         ▼
┌─────────────────────────────────────┐
│ UI Modules (ui_*.c)                 │  Drawing (layout, logo, progressbar),
│                                     │  menus, status, confirm, title.
└─────────────────────────────────────┘
         │
         ▼
┌──────────┬──────────┬──────────────┐
│ installer│ prompt   │ regedit      │  Core interactive shells
│ settings │ help     │ extras       │
└──────────┴──────────┴──────────────┘
         │
         ▼
┌─────────────────────────────────────┐
│ User Management (user_*.c)          │  login, add_user, password change,
│                                     │  user ID change, guest mode.
└─────────────────────────────────────┘
         │
         ▼
┌─────────────────────────────────────┐
│ App Installer (app_installer.c)     │  Install/uninstall apps, check status,
│                                     │  find app by name.
└─────────────────────────────────────┘
```

---

### ✨ Features

- **First‑run installer** – asks whether to test in guest mode or install directly.
- **User system** – create an account with optional password; change or remove password later.
- **Guest mode** – limited command set (`install`, `login`, `registryeditor`, `exit`).
- **Command prompt** – type `help` to see available commands; supports `inst_<app>` and `unst_<app>` shortcuts.
- **Application placeholders** – seven apps (TicTacToe, Quiz, Temp Converter, Calculator, Equation Solver, Quadratic Solver, Area of Triangle) with bootscreen and “placeholder” message – easily replaceable with real logic.
- **Registry Editor** – advanced tool with admin mode; can install all apps, reset, temporarily run apps, manage user accounts, add keys.
- **Settings panel** – user accounts, reset & restore (uninstall all or full reinstall), personalisation (border color), help.
- **Colour change wizard** – 16 background colours, preview table, saved in `looks.bd`.
- **Lockdown timer** – after too many failed logins, a 10‑second countdown and exit.
- **Activation key placeholders** – for future app registration.

---

### 🛠️ Building and Running

#### Linux
```bash
gcc -D OE_PLATFORM_LINUX *.c -o oe_reboot
./oe_reboot
```

#### Windows (MinGW or Visual Studio)
```bash
gcc -D OE_PLATFORM_WINDOWS *.c -o oe_reboot.exe
oe_reboot.exe
```

**No external libraries required** – only standard C runtime and (on Windows) the Windows API for console modes.

---

### 🚀 First‑Time Usage

1. Run the program – you’ll see a bootscreen.
2. If no user exists, the **installer** appears.
   - Press **y** to install directly (you’ll create a user afterwards).
   - Press **n** to enter guest mode (limited commands).
   - Special backdoors: `registryeditor`, `registryeditor_admin`, `prompt` (skip installer).
3. In normal mode, type `help` at the `Command->` prompt to see all commands.
4. Explore the Settings panel (`settings` command) to change colours, reset apps, or manage your account.

---

### 📁 Important Files

| File(s)               | Purpose                                |
|-----------------------|----------------------------------------|
| `user.bd`, `pwd.bd`   | Stored username and password (binary)  |
| `*.rg` files          | Application registry (0 = uninstalled, 1 = installed) |
| `looks.bd`            | Selected border colour (1–16)          |

---

### 📌 Version History

| Version  | Date       | Key Features / Changes |
|----------|------------|------------------------|
| 6.12.56  | 2026‑02‑21 | Initial PAL‑based rewrite, basic user system, installer, prompt. |
| 6.48.21  | 2026‑02‑24 | Added settings panel, colour wizard, registry editor, guest mode, bug fixes. |

*Intermediate versions exist but are not tagged separately.*

---

### 🔮 Future Direction

OE_REBOOT is a stepping stone toward a larger goal: converting this simulation into a **real operating system kernel**. The current codebase demonstrates the core concepts – user management, application installation, a registry, and a settings panel – all of which are essential components of an OS. Future work may involve:

- Replacing placeholder apps with full implementations.
- Dynamic screen size detection.
- Raw input mode for better console handling.
- Eventually, booting on bare metal with a custom kernel.

---

### 📬 Contact

**Subhajit Halder**  
📧 subhajithalder267@outlook.com

---

**Enjoy the retro experience – and stay tuned for the OS!**
