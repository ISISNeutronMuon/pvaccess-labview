# PVAccess for LabVIEW

An [EPICS PVAccess](https://docs.epics-controls.org/en/latest/pv-access/protocol.html) library for LabVIEW.

⚠️ This software is in the alpha stage of development and does not have a stable interface.

![image](https://github.com/user-attachments/assets/87c6365a-914c-402b-8513-65aa0285e8db)

## Requirements

The VIPM package is compatible with LabVIEW 2020 or above.

Real-time targets running NI Linux RT 2023 Q1 or above should be compatible.

## Installation

### LabVIEW library (VIPM)

Download the latest `.vip` file from [releases](https://github.com/ISISNeutronMuon/pvaccess-labview/releases) and open it with VIPM.

### NI Linux Real-Time

SSH into the target and run this command, replace `<VERSION>`with the version of the VIP file you have installed.

```bash
wget https://github.com/ISISNeutronMuon/pvaccess-labview/releases/download/v<VERSION>/pva_labview_<VERSION>.ipk
opkg install pva_labview_<VERSION>.ipk
```

## Development

### Prerequisits

#### Windows

- Install the [Microsoft C++ Build Tools](https://learn.microsoft.com/en-us/cpp/build/building-on-the-command-line)

- Install [Chocolatey](Chocolatey)

- Install Make, CMake and Perl
  ```ps1
  choco install make cmake strawberryperl
  ```

- Launch the "Developer Command Prompt for VS", not PowerShell, and run the subsequent commands from it

- Activate the [64-bit environment](https://learn.microsoft.com/en-us/cpp/build/building-on-the-command-line#developer_command_file_locations)

#### Linux

- Install Make, CMake, Perl and libevent using your distribution's package manager
  ```sh
  sudo apt install make cmake perl libevent-dev
  ```

#### NI Linux RT

- Install build dependencies
  ```sh
  opkg install
    git \
    packagegroup-core-buildessential \
    perl-modules \
    libevent-dev \
    cmake
  ```

### Building dependencies

#### Windows

- Build EPICS Base
  ```bat
  set EPICS_HOST_ARCH=windows-x64-static
  make -C epics-base
  ```

- Build PVXS
  ```bat
  echo EPICS_BASE = $(TOP)/../epics-base > pvxs/configure/RELEASE.local
  make -C pvxs/bundle libevent
  make -C pvxs
  ```
  See the [PVXS docs](https://epics-base.github.io/pvxs/building.html) for more details

#### Linux and NI Linux RT

- Build EPICS Base
  ```sh
  make -C epics-base
  ```

- Build PVXS
  ```sh
  cat <<EOF > pvxs/configure/RELEASE.local
  EPICS_BASE = \$(TOP)/../epics-base
  EOF
  make -C pvxs
  ```

### Building this library

- Windows
  ```ps1
  cmake --preset=windows-x64
  cmake --build --preset=windows-x64
  ```
- Linux
  ```sh
  cmake --preset=linux-x86_64
  cmake --build --preset=linux-x86_64
  ```

### Packaging NI Linux RT Package
These command must be run on an NI Linux RT target
```sh
cmake --preset=nilrt
cmake --build --preset=nilrt
cpack --preset=nilrt
```
