# NI Linux RT

Building the library for NI Linux RT targets.

Tested with NILRT 2025Q4.

## Development

- Clone this repo to the target
  ```bash
  git clone https://github.com/ISISNeutronMuon/pvaccess-labview.git
  ```
- Install and build dependencies
  ```bash
  nilrt/install
  ```
- Build this library and package it into an IPK
  ```bash
  nilrt/build-package
  ```

## Installation

- Copy the `.ipk` file to the target and install it
  ```bash
  opkg install pvalabview_x.x.x_x64.ipk
  ```
