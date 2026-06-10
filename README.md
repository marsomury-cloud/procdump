# ProcDump v12.0 - Sysinternals

**By Mark Russinovich and Andrew Richards**  
**Published:** May 7, 2026


## Overview

**ProcDump** is a command-line utility from Microsoft Sysinternals. Its primary purpose is to monitor applications for CPU spikes and generate crash dumps during those spikes. It is also useful for capturing dumps on hung windows, unhandled exceptions, and performance counter thresholds.

## Features

- Monitor a process for high CPU usage and generate dumps
- Monitor for hung windows
- Capture dumps on first-chance or second-chance exceptions
- Monitor performance counters
- Act as a Just-In-Time (JIT) debugger
- Launch a process and monitor it from startup
- Generate multiple dumps
- Support for different dump types (Mini, Full, Triage, etc.)

## Command Line Usage

### Basic Syntax
```cmd
procdump.exe [options] {[-w] <Process_Name | Service_Name | PID> | -x <Dump_Folder> <Image_File> [Args...]}
```

### Common Options

| Option | Description |
|--------|-------------|
| `-ma` | Full memory dump |
| `-mm` | Mini dump (default) |
| `-mt` | Triage dump |
| `-mp` | MiniPlus dump |
| `-c <value>` | Dump when CPU usage exceeds threshold |
| `-m <MB>` | Dump when commit charge exceeds threshold |
| `-e [1]` | Dump on exceptions (1 = first chance) |
| `-h` | Dump when a window is hung |
| `-n <count>` | Number of dumps to write |
| `-s <seconds>` | Seconds the condition must be met |
| `-r` | Use clone (PSS) for lower impact |
| `-w` | Wait for the process to start |
| `-x` | Launch and monitor a new process |
| `-i` | Install as JIT debugger |
| `-u` | Uninstall JIT registration |

### Examples

```cmd
# Create a mini dump of a running process
procdump notepad.exe

# Full dump by PID
procdump -ma 1234

# Dump when CPU > 80% for 10 seconds
procdump -c 80 -s 10 MyApp.exe

# 5 dumps on exceptions
procdump -e -n 5 -ma w3wp.exe

# Launch and monitor a process
procdump -e -x C:\Dumps\ MyApp.exe arg1 arg2

# Install as JIT debugger
procdump -i C:\Dumps\
```

## Dump File Naming

Dumps are saved with the following pattern:
```
<ProcessName>_<YYYYMMDD>_<HHMMSS>.dmp
```



**ProcDump** is part of the Microsoft Sysinternals suite — powerful utilities for troubleshooting Windows systems.
```

The file `README.md` has been created successfully. You can now download it.
