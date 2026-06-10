# Usage

## Build

### Visual Studio

Open `ProcDumpSafe.sln` and build `Release|x64`.

### PowerShell

```powershell
powershell -ExecutionPolicy Bypass -File .\build.ps1
```

## Run

Create a dump of the current process:

```powershell
.\bin\procdump-safe.exe --self
```

Create a dump at a custom path:

```powershell
.\bin\procdump-safe.exe --self .\dumps\manual.dmp
```

Test the crash handler:

```powershell
.\bin\procdump-safe.exe --crash
```
