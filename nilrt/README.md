# NI Linux RT

Building the library for NI Linux RT targets.

## Development

- Build the package
  ```bash
  docker build -f nilrt/Dockerfile --output . .
  ```

## Installation

- Copy the `.ipk` file to the target and install it
  ```bash
  opkg install pvalv_x.x.x_x64.ipk
  ```
