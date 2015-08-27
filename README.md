# Pygclib
Python bindings for [gclib](http://www.galilmc.com/downloads/api) to send commands to Galil motion controllers using python.

## pygclib

A python module with a simple interface to control the motion controller.

### Configuration
Open `source/pygclib.py` and add the ip address of the motion controller and the mechanical specifications of the encoders.

### Compiling using MSVS
1. Open the command line
2. Set the env variable VSXXXCOMNTOOLS corresponding to your python build to the VS version you have installed
3. Type `python setup.py install`. This will create a build directory with the binaries but install the necessary binaries and dlls into the python path.

### Usage
Only import pygclib when the hardware safety switch is off, because importing pygclib immediately initializes the motors. If you forget, simply re-import.

Type `import pygclib` to use `move(axis, speed, displacement, blocking=True)` and `rotate(degrees_per_sec, degrees, blocking=True)`.

Type `import gclib` to access `GOpen(address)`, `GCommand(con, command)` and `GClose(con)` functions.

## tester

A commandline interface for sending DMC code to the motion controller.

### Compiling Using MinGW and Cygwin
1. Install cygwin and the 32-bit mingw C compiler and make utility
2. Install [MSVS 2013 redistributables] (https://www.microsoft.com/en-ca/download/details.aspx?id=40784)
3. Change the ip address in `tester.c`
4. Type `Make` to generate `tester.exe` in `bin` directory

### Usage
Navigate to the 'bin' directory and enter `./tester.exe`. You will be prompted for a command and the return code and buffer will be printed.

## DMC Code
The full [documentation](http://www.galilmc.com/downloads/manuals-and-data-sheets) can be found on [Galil's website] (http://www.galilmc.com/).

To get started look up: `SP, IP, PR, BG, AB, SH and MO`. The motors/control algorithm must be activated using the `SH` command.

## Mechanical Specifications for Lab C-Scan Machine
10mm = 6298 counts on encoder