Herein lies all the source code for libtsctl, which is the library
implementing the tsctl C API ("libtsctl"), as well as all sample code
which uses this API.

For in depth information on recent changes, please visit the libtsctl 
blog at:
http://libtsctl.blogspot.com

For up to date documentation on libtsctl, please visit the official
documentation wiki at:
http://wiki.embeddedarm.com/wiki/Tsctl

The project files are divided into four parts.  The root contains all the
same source code (libtsctl clients such as tsctl).  The ts/ sub-directory
contains all the architecture specific files, which collectively form the
libtsctl library proper.  The net/ sub-directory contains all the architecture
independent network based implementations of the API, which require a server
such as tsctl to be running on the target board.  The dioctl.config/
sub-directory is discussed in a later section.

To build you must define a variable (i.e. by prefixing the make command
with an assignment) which defines your architecture.  Currently there are
three supported: "ARCH=cavium" for all Cavium CNS2132 based CPU boards (e.g.
TS-4500 and TS-75XX) which do not have a branch-exchange instruction, 
"ARCH=noncavium" for all other Technologic Systems boards, and "ARCH=x86"
for a PC; this last option is only valid for libnettsctl based builds.  If
no architecture is specified, "ARCH=noncavium" is assumed.

The tsctl product requires the libreadline5-dev and libbz2-dev packages to
be installed and it is thus recommended to compile on the board.  Any other
app using libtsctl also requires libbz2-dev (for decompression of the 
in-build dioctl.config files).  We have heard reports that it is possible
to compile/install these libraries/headers directly for cross-toolchains, 
however you will still need to install the actual libraries unless you do
a static link.

If you choose to cross-compile with libtsctl, in addition to meeting the
above library requirements, if you use the supplied Makefile, you will also 
need to define TOOL_PREFIX to point to the path prefix to your toolchain,
for example:
    TOOL_PREFIX=/opt/locall/arm-linux/gcc-3.4.5-glibc-2.3.4/bin/arm-linux- make

By default the products go in a sub-directory with the same name of the
architecture.  You can override this using
the DIR variable, e.g.
    DIR=binaries

The resulting binaries can be run from anywhere on your board, although
it is recommended that they go somewhere in your PATH to avoid needing
to specify an explicit path.  If you wish to override or extend any
of the default configuration you can do so by creating an /etc/dioctl.config
file containing name=value assignments as specific in the documentation.

You can also edit the config file for your board; these are in the dioctl.config/
directory.  After making any changes you will need to run the mkdioctlconfig
script in this directory to re-generate all the compressed files to compile
into libtsctl.

If for your own purposes you want to create a stripped-down version
of libtsctl that supports only the specific architecture for your
board, assign the desired architectures to the SUPPORT variable, e.g.
"SUPPORT=4200 81x0 make" would build with only support for the TS-4200 CPU and
the TS-81x0 base board series.

It is possible to use libtsctl from languages other than C is provided by
a SWIG .i file.  Please read the SWIG.txt file for more information.
Please note that this method is provided for your convenience only and is
not officially supported at this time.  Some work will be needed to interact
with functions taking or returning libtsctl Arrays; we do not know enough about
SWIG to know the correct way to generate the interface for this data structure.

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

tsctl: implements the full tsctl client and server. currently or in the future
may also incorporates the canctl, dioctl, and spictl, modbus and http servers 
with compile time options to be added to selectively exclude any of the auxiliary 
(canctl, dioctl, spictl, modbus, http) servers.

spictl: implements the classic standalone spictl server and command line 
options using the libtsctl API.  cannot be run simultaneously with any of the 
other ctl servers documented here.

Additional sample code will be available if there is demand for it:

dioctl: implements the classic standalone dioctl server and command line 
options using the libtsctl API.  cannot be run simultaneously with any of the 
other ctl servers documented here.

