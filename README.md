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

### Building dependencies

- Clone [EPICS Base](https://github.com/epics-base/epics-base/) to `./epics-base` and build it

  ```sh
  git clone https://github.com/epics-base/epics-base.git
  cat <<EOF > epics-base/configure/CONFIG_SITE.local
  SHARED_LIBRARIES=NO
  STATIC_BUILD=YES
  EOF
  make -C epics-base
  ```

- Clone [PVXS](https://github.com/epics-base/pvxs/) to `./pvxs` and build it

  ```sh
  git clone --recurse-submodules https://github.com/epics-base/pvxs.git
  cat <<EOF > pvxs/configure/CONFIG_SITE.local
  SHARED_LIBRARIES=NO
  STATIC_BUILD=YES
  EOF
  cat <<EOF > pvxs/configure/RELEASE.local
  EPICS_BASE=\$(TOP)/../epics-base
  EOF
  make -C pvxs/bundle libevent
  make -C pvxs
  ```
  See the [PVXS docs](https://epics-base.github.io/pvxs/building.html) for more details

### Building this library

- Windows
  ```ps1
  cmake --preset=windows-x64
  cmake --build --preset=windows-x64
  ```
- Linux
  ```sh
  cmake --preset=linux-x86_64
  cmake --build --preset=linux-x86_64 \
  && mkdir -p labview/libraries/linux-x86_64/ \
  && cp build/linux-x86_64/libpva_labview.so "$_"
  ```
