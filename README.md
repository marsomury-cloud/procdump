========================================================================
       Sysinternals ProcDump - Advanced Process Dump Utility
========================================================================
Copyright (C) 2009-2026 Mark Russinovich and Andrew Brummer
Sysinternals - www.sysinternals.com

Introduction
------------
ProcDump is a command-line utility whose primary purpose is monitoring 
an application for CPU spikes and generating crash dumps during a spike 
that an administrator or developer can use to determine the cause of 
the spike. 

ProcDump also includes hung window monitoring, unhandled exception 
monitoring and can generate dumps based on the values of system 
performance counters.

Installation
------------
To install ProcDump, copy the executable file (procdump.exe or 
procdump64.exe) to any directory on your local hard drive that is 
included in your system PATH environment variable.

Requirements
------------
* Windows 7 / Windows Server 2008 and higher.
* Requires administrative privileges to capture processes memory 
  contexts and write dump files to system protected directories.

Using ProcDump
--------------
Usage: procdump [-c CPU] [-m Memory] [-n Count] <PID or Process Name>

Common Command-Line Switches:
   -c      CPU threshold (0-100) at which to create a dump.
   -m      Memory threshold (MB) at which to create a dump.
   -n      Number of dumps to write before exiting (default is 1).
   -s      Consecutive seconds threshold before dump is written.
   -e      Write a dump when the process encounters an unhandled exception.

Examples
--------
Capture a standard mini-dump of 'explorer.exe' immediately:
   C:\> procdump explorer.exe

Monitor PID 4320 and write a dump if CPU exceeds 70% for 10 seconds:
   C:\> procdump -c 70 -s 10 4320

Reporting Bugs
--------------
If you encounter any issues or wish to request new feature sets, 
please visit the official Microsoft Sysinternals forums or submit 
a ticket via the Azure DevOps portal at learn.microsoft.com/sysinternals.