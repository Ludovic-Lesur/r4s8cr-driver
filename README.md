# Description

This repository contains the **R4S8CR** relay box driver.

# Dependencies

The driver relies on:

* An external `types.h` header file defining the **standard C types** of the targeted MCU.
* The **embedded utility functions** defined in the [embedded-utils](https://github.com/Ludovic-Lesur/embedded-utils) repository.

Here is the versions compatibility table:

| **r4s8cr-driver** | **embedded-utils** |
|:---:|:---:|
| [sw2.0](https://github.com/Ludovic-Lesur/r4s8cr-driver/releases/tag/sw2.0) | >= [sw1.3](https://github.com/Ludovic-Lesur/embedded-utils/releases/tag/sw1.3) |
| [sw1.0](https://github.com/Ludovic-Lesur/r4s8cr-driver/releases/tag/sw1.0) | >= [sw1.3](https://github.com/Ludovic-Lesur/embedded-utils/releases/tag/sw1.3) |

# Compilation flags

| **Flag name** | **Value** | **Description** |
|:---:|:---:|:---:|
| `R4S8CR_DRIVER_DISABLE_FLAGS_FILE` | `defined` / `undefined` | Disable the `s2lp_driver_flags.h` header file inclusion when compilation flags are given in the project settings or by command line. |
| `R4S8CR_DRIVER_RS485_ERROR_BASE_LAST` | `<value>` | Last error base of the low level RS485 driver. |
| `R4S8CR_DRIVER_DELAY_ERROR_BASE_LAST` | `<value>` | Last error base of the low level delay driver. |
