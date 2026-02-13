# PVAccess for LabVIEW

An [EPICS PVAccess](https://docs.epics-controls.org/en/latest/pv-access/protocol.html) library for LabVIEW.

⚠️ This software is in the alpha stage of development and does not have a stable interface.

![image](https://github.com/user-attachments/assets/1d8dea33-e0f0-4064-a527-22c7b9b64251)

## Building

- Clone [EPICS Base](https://github.com/epics-base/epics-base/) to `./epics-base` and build it

  ```sh
  git clone https://github.com/epics-base/epics-base.git
  make -C epics-base
  ```

- Clone [PVXS](https://github.com/epics-base/pvxs/) to `./pvxs` and build it

  ```sh
  git clone --recurse-submodules https://github.com/epics-base/pvxs.git
  echo 'EPICS_BASE=$(TOP)/../epics-base' > ./pvxs/configure/RELEASE.local
  make -C pvxs/bundle libevent
  make -C pvxs
  ```
  See the [PVXS docs](https://epics-base.github.io/pvxs/building.html) for more details

- Build this library

  - Windows
    ```
    cmake -G "Visual Studio 17 2022" -A x64 -B .\build\windows-x64\
    cmake --build .\build\windows-x64\ --config Release
    ```
  - Linux
    ```sh
    cmake -B build/linux-x86_64/
    cmake --build build/linux-x86_64/ \
    && mkdir -p labview/libraries/linux-x86_64/ \
    && cp build/linux-x86_64/libpva_labview.so "$_"
    ```
