OSCAR
=====
A Retina screen controlling interface.

This repository contains the software for the host computer program, and the Arduino-ized firmware for the ATMega on board.
This repostiory also contais the schematics and board files.
This repository does not contain the new Aruduino variant required to build this code - but it can be found as a submodule.

Getting Started (from Source)
-----------------------------
1. `git clone https://github.com/OSCARAdapter/OSCAR.git`
2. `git submodule init && git submodule update`

*Build the firmware [in fw/]*
* `make`

*Program to the device.*

You may need to adjust MONITOR_PORT in fw/Makefile.
* `make upload`

*Build the software [in sw/] (_Windows_)*

This requires you to have Visual Studio C++ installed, the QT5 development environment to be set up, and to have the libusb source.
1. `qmake -tp vc oscar.pro`
2. Open the generated vcproj in Visual Studio
3. Adjust as required to fit your environment
4. Build

*Build the software [in sw/] (_Linux/OSX_)*

This requires a C++ compiler, QT5 development libraries, libusb development package.
1. `qmake oscar.pro`
2. `make`

*Other*
On Windows, you will be required to install the drivers for the device, these can be found in installer/drivers.

Getting Started (from Binary)
-----------------------------
TODO: generate the binary

Repository Overview
-------------------
*Arduino/*

Contains the custom OSCAR variant in hardware/arduino/cores/oscar.
This is based on the ATMega task sample, and runs two tasks:
1. USB Task - responsible for processing all USB packets 
2. Arduino Task - reponsible for maintaing the single-threaded Arduino compatible emulation layer.

*Arduino-Makefile/*

A makefile system to allow the compilation of the code without requiring the Arduino IDE. This project can be found at https://github.com/sudar/Arduino-Makefile.

*fw/*

Contains the firmware for the integrated ATmega. All of the OSCAR code can be found in fw/libs/AdapterBoard.* This keeps the top level oscar.ino clear of any unnecessary code, allowing you to directly extend the device as you require.
Libraries for backlight control and control of the RGB led can also be found in fw/libs/

*hw/*

Contains the schematics and pcb layouts for the driver board.

*installer/*

The [NSIS](http://nsis.sourceforge.net/Main_Page) installer for Windows can be found in oscar.nsi. installer/qtlib contains the required DLLs for Qt5 and libusb to be directly included with the generated oscar executable for the installer.
installer/drivers contains the required Windows drivers for XP and Vista/Win7/Win8 to interact with the libusb device.

*logo/*

Contains the OSCAR logo, which is included in the software

*sw/*

Has the control software for your computer. This code presents a GUI for Windows, Linux or OSX based upon Qt5 and libusb. The source code can be found in sw/src, UI designs can be found in src/ui.


Licensing
---------
The software and firmware is licensed under the BSD 3-Clause License (refer to COPYING).

The hardware is licensed under CC-BY-SA.
