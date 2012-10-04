Herein lies all the source code for libtsctl, which is the library
implementing the tsctl C API ("libtsctl"), as well as all sample code
which uses this API.

The CHANGES.txt file contains a summary of changes for each release.
For more in depth information, please visit the libtsctl blog at:
http://libtsctl.blogspot.com


Before you can compile you create a file called Makefile.config.
There is a sample "Makefile.config.sample" that you can use as a
reference.  You will need to define TOOL_PREFIX to be the path to
your compiler (or cross-compiler) plus any common prefix such as
"arm-linux" if that exists.  You will also need to define BOARDSEL
to be either "cavium" if you are compiling for a Cavium based board
(TS-4500 or TS-75XX), or "noncavium" for all other CPU boards.

For ease of embedding libtsctl in your own application while still
being able to support a wide range of hardware, the approach is
taking of including the C files for each architecture to be supported.
If you want to import libtsctl into your own project, it should be
sufficient to copy the .h header files and the ts/ sub-directory 
to your own project directory, and then  #include "libtsctl.h" in 
your program.

If for your own purposes you want to create a stripped-down version
of libtsctl that supports only the specific architecture for your
board, you will need to edit either libtsctl-cavium.h or 
libtsctl-noncavium.h and remove the include statements for all
boards you are not using.  You will then need to edit near the top
of ts4200.c (for noncavium) or ts4500.c (for cavium) to remove the 
data structures corresponding to these boards.  More specifically,
look for the lines starting with "ArrayAuto" and remove the references
from each line to the variables containing those board names in each
list.

The provided Makefile by default will compile all the sample applications
for your selected board class (cavium or noncavium), putting the binaries
in a sub-directory of the same name.  You can compile a subset of the
applications be prefixing the make command with a "PRODUCTS=..."
assignment with the list of applications to compile.

The resulting binaries can be run from anywhere on your board, although
it is recommended that they go somewhere in your PATH to avoid needing
to specify an explicit path.  If you wish to override or extend any
of the default configuration you can do so by creating an /etc/dioctl.config
file containing name=value assignments as specific in the documentation.

Support for using libtsctl from languages other than C is provided by
a SWIG .i file.  Please read the SWIG.txt file for more information.

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

tsctl: implementint the full tsctl client and server. also incorporates the 
canctl, dioctl, and spictl servers.  in addition, implements modbus and 
http servers.  compile time options can selectively exclude any of the 
auxiliary (canctl, dioctl, spictl, modbus, http) servers.
