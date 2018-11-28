# Jaguar USB Tap

![Atari Jaguar logo](./preview/Atari-Jaguar-logo.png)

The [controller](https://atariage.com/controller_page.html?ControllerID=21&SystemID=JAGUAR) for the [Atari Jaguar](https://en.wikipedia.org/wiki/Atari_Jaguar) game console is a strange beast and doesn't map well to modern controllers (in large part due to the numeric keypad). This makes emulating games on a PC with off-the-shelf controllers, which usually mimic PlayStation or XBox layouts, somewhat cumbersome. One possible solution is to create a device which can convert the Jaguar controller's pinout and signals to a USB HID device.

## Hardware

The hardware was developed using the open-source schematic and PCB design tool [KiCad](http://kicad-pcb.org/). It sports an [STM32F070](http://www.st.com/en/microcontrollers/stm32f070cb.html) ARM Cortex M0 micro-controller which handles input from the Jaguar gamepad and generate appropriate USB HID signalling.

![Assembled Jaguar USB Tap](./preview/close-up.jpg)

![Jaguar USB Tap](./preview/game-in-progress.jpg)

![Typical use case](./preview/windows-button-assignment.jpg)

## Accessibility

Even though the design uses entirely surface-mount (SMD) components, with the exception of connectors, I selected components with relatively large footprints such as 1812 for non-polarised capacitors. Larger components resulted in the PCB being bigger than it needs to be, but I feel this to be an acceptable trade-off to ensure that the design is accessible as they require less skill to solder and can also be identified and handled more easily by those with poorer eyesight.

At the heart of the board is an [STM32F070 microcontroller](http://www.st.com/en/microcontrollers/stm32f070cb.html). This part contains an ARM processor core, a USB peripheral and a small handful of GPIO pins making it highly suited as an embedded processor in USB human-interface devices (HID). While the part is a good technical fit for the project there are also accessibility reasons for using an STM32 uC. Chiefly, **firmware can be developed using entirely open-source tools**, such as gcc, on the user’s platform of choice (Linux, Mac OS or, I suppose, even Windows).

## Firmware

### Compatibility

I've tested on:

* Linux
* Windows 7
* MacOS X

In all cases the default USB HID driver on each system is suitable for use with the Jaguar USB Tap and enumerates correctly without additional drivers.

### Building

#### Prerequisites

Requires an ARM toolchain:

* arm-none-eabi-gcc
* arm-none-eabi-gdb
* arm-none-eabi-binutils
* OpenOCD (programming utility)

On Debian/Ubuntu: 

```
$ sudo apt-get install gcc-arm-none-eabi gdb-arm-none-eabi openocd
```
#### Make targets

To build the application:

```
$ make
```

To delete compiled objects and binaries:

```
$ make clean
```

To flash the STM32F0 over STLink:

```
$ make upload
```

To run the debugger, start an OpenOCD session with the target:

```
$ make debug
```

and then, in another terminal window:

```
$ make run_gdb
```
