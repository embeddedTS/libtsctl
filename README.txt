Herein lies all the source code for libtsctl, which is the library
implementing the tsctl C API ("libtsctl"), as well as all sample code
which uses this API.

For in depth information on recent changes, please visit the libtsctl 
blog at:
http://libtsctl.blogspot.com

All libtsctl files are under the ts/ sub-directory.  To integrate libtsctl
directly into your own project, include ts/libtsctl.h to embed the
library into your code and make the API available.  Be sure to define
the ARCH variable to a valid architecture (e.g. "cavium" or "noncavium").
Then, the appropriate C files for the architecture you have selected
will be automatically included into whatever file you included libtsctl.h
into, eliminating the need to modify your build process to accomdate files
in ts/.  If you need to access the libtsctl from multiple files, you will
need to #include "libtsctl0.h" into all files except the one you included
libtsctl.h into, this will pull in the API definitions only.

All tsctl client files are under the net/ directory.  To integrate
these directly into your own project, include net/nettsctl.h into
your code.

The build process is set up to build tsctl for non-cavium boards out of the 
box directly on the board (e.g. in the Debian environment) by simply invoking 
'make' in the top-most project directory (i.e. the directory this README.txt 
file is in.)  You can also specify other products to build or "make all" to
build all sample code.  Please consult the Makefile for available sample
products to build; look for the line beginning "PRODUCTS=".

The tsctl product requires libreadline to compile correctly; before compiling
on the board you may need to run libreadline5-dev.  The default build process
will statically link readline, so you will not need it to be installed on
the board tsctl is run on.

If you wish to build for Cavium boards (TS-4500, TS-75XX), you will need to
define ARCH=cavium, e.g.
    ARCH=cavium make

Presently we recommend that you compile all libtsctl based products
directly on the board.  If you do not do this, you will need to
define TOOL_PREFIX to point to the path prefix to your toolchain,
for example:
    TOOL_PREFIX=/opt/locall/arm-linux/gcc-3.4.5-glibc-2.3.4/bin/arm-linux- make

By default the products go in a sub-directory with the same name of the
architecture; by default this is "noncavium".  You can override this using
the DIR variable, e.g.
    DIR=binaries

The resulting binaries can be run from anywhere on your board, although
it is recommended that they go somewhere in your PATH to avoid needing
to specify an explicit path.  If you wish to override or extend any
of the default configuration you can do so by creating an /etc/dioctl.config
file containing name=value assignments as specific in the documentation.

If for your own purposes you want to create a stripped-down version
of libtsctl that supports only the specific architecture for your
board, you will need to edit either libtsctl-cavium.h or 
libtsctl-noncavium.h and remove the include statements for all
boards you are not using.  You will then need to edit near the top
of ts4200.c (for noncavium) or ts4500.c (for cavium) to remove the 
data structures corresponding to these boards.  More specifically,
look for the lines starting with "ArrayAuto" and remove the references
from each line to the variables containing those board names in each
list.  You may also need to move these definitions, e.g. if you are only
including ts4700.c you will need to move these data structures from ts4200.c
to ts4700.c.

It is possible to use libtsctl from languages other than C is provided by
a SWIG .i file.  Please read the SWIG.txt file for more information.
Please note that this method is provided for your convenience only and is
not officially supported at this time.

=== SAMPLE CODE ===

Currently the following sample programs are included:

diotoggle: toggles a DIO specified by name or number from the command line

spi8200: displays the A/D readings from various power rails.  Requires a
TS-8200 with populated U3 and U4 to be present. (These chips are not populated
on stock models.)

ts8160ctl: interacts with the AVR on the TS-8160 to get info and put the
board into sleep mode.  Requires a TS-8160 base board to be present.

DIOTest: interacts with a test harness to test DIOs.  Some base boards have
this harness (e.g. TS-8200).  The /etc/dioctl.config file must define the
wires in the test harness unless they are already in the built-in config.

CANTx: demonstrates how to directly send a CAN frame

CANRx: demonstrates how to directly wait for and receive a CAN frame

CAN2: demonstrates how to indirectly send a CAN frame.  this is accomplished
by starting a server implementing the canctl protocol, and then instantiating
a network CAN object talking that protocol to communicate with the server.

canctl: implements the classic standalone canctl server and command line 
options using the libtsctl API and provides enhancements over the original
program.  cannot be run simultaneously with any of the other ctl servers 
documented here.

tsctl: partial implementation of tsctl client using local objects. Also
implements the tsctl http server.

spictl: implements the classic standalone spictl server and command line 
options using the libtsctl API.  cannot be run simultaneously with any of the 
other ctl servers documented here.

Additional sample code will be available soon:

dioctl: implements the classic standalone dioctl server and command line 
options using the libtsctl API.  cannot be run simultaneously with any of the 
other ctl servers documented here.

tsctl: implementing the full tsctl client and server. also incorporates the 
canctl, dioctl, and spictl servers.  in addition, implements modbus and 
http servers.  compile time options can selectively exclude any of the 
auxiliary (canctl, dioctl, spictl, modbus, http) servers.
