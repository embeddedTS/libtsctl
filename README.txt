Herein lies all the source code for libtsctl, which is the library
implementing the tsctl C API ("libtsctl"), as well as all sample code
which uses this API.

The CHANGES.txt file contains a summary of changes for each release.
For more in depth information, please visit the libtsctl blog at:
http://libtsctl.blogspot.com

Before you can compile you must do two things:
1. make sure that libtsctl.h is symlinked properly

Currently it is only possible to do two compiles.

If you want to compile for a Non-cavium based CPU board (TS-4200, TS-4700,
TS-4800), then libtsctl.h must be symlinked to libtsctl-noncavium.h

If you want to compile for a Cavium based CPU board (TS-4500, TS-75XX),
then libtsctl.h must be symlinked to libtsctl-cavium.h

For simplicity, you may run "make cavium" to set the symlink to cavium, or
"make noncavium" to set the symlink to non-cavium.

In the past, libtsctl has only supported compilation for a single architecture
at a time.  If you wish to strip down libtsctl to support this mode, you
will need to edit ts4200.c or ts4500.c to remove references to architectures
you do not wish to support.  Then, edit libtsctl.h to remove include
references to those same architectures.

The remainder of this section is retained for reference purposes, but its
instructions should no longer be followed due to the fact that libtsctl
now supports multiple architectures in a single binary.

Your architecture consists of all the boards you have connected together,
starting with the CPU board, followed by a base board, followed by any
peripheral boards.  Your system will contain at least the CPU board.

You must #include the C file for each component of your architecture in the
order specified above.  You must also #include "ts/tsinit.c" after all
arch files are included.   The C files for each arch are found in the ts/
sub-directory, and are named according to the name of the board.

Here is the current list of architecture files:

  CPU boards
  ts4200.c
  ts4500.c
  ts4700.c
  ts4800.c
  ts7552.c
  ts7553.c
  ts7558.c

  Base boards
  ts81x0.c
  ts8820.c
  ts8900.c

  Peripheral boards
  tsdio24.c
  tsrelay8.c

Note that it is not necessary to #include "libtsctl.h" in your own project.
Instead, you can directly include the required files as specified above in
your own program.  The only purpose for libtsctl.h here is to allow all
sample files to use the architecture as specified in a single place, and to
remain compatible with the previous method of using the API.  The libtsctl.h
that you are editing should not be confused with "ts/libtsctl.h".

2. edit Makefile, or replace it with your own

A Makefile is supplied for convenience in compiling all the provided sample
applications.  For your own project you can use whatever build mechanism you
wish.  All that is required is that you include the correct arch files as
specified in step 1 above.  It is also recommended that you keep the libtsctl
files in the sub-directory ts/ to keep it separate from your own code.

If you wish to use the included Makefile, at the least you must modify the CC 
variable assignment to point to your compiler.  You will also need to modify 
LDFLAGS if you are not using uclibc.

After you have done the above two steps run 'make' in the directory with
the Makefile to build all the sample source code for your architecture.
The binaries will be placed in the same directory.

After you compile and before you use the resulting binaries, it is highly
recommended to install the appropriate dioctl.config file in the /etc
directory of your board.  Without this file you will not have available the
default name to number lookups for DIOs specific to your board.

All available config files are in the config/ directory.  To find the 
appropriate dioctl.config file for your board, select the file which has
the list of architecture names corresponding to the architecture you selected
in step 1, above. Note that dioctl.config architectures are more specific
in some cases (e.g. ts8160 or ts8100 instead of ts81x0, or ts8200 which
does not have a specific arch support C file.)

IMPORTANT NOTE: The sample Makefile does not contain any provision to detect
whether the sample code you are compiling is appropriate for your architecture.
For instance, canctl will not work on the TS-4200 since it does not support CAN.

Support for using libtsctl from languages other than C is provided by
a SWIG .i file.  Please read the SWIG.txt file for more information.

Currently the following sample programs are included:

diotoggle: toggles a DIO specified by name or number from the command line

spi8200: displays the A/D readings from various power rails.  Requires a
TS-8200 with populated U3 and U4 to be present. (These chips are not populated
on stock models.)

ts8160ctl: interacts with the AVR on the TS-8160 to get info and put the
board into sleep mode.  Requires a TS-8160 base board to be present.

DIOTest: interacts with a test harness to test DIOs.  Some base boards have
this harness (e.g. TS-8200).  The /etc/dioctl.config file must define the
wires in the test harness.

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

tsctl: implements the tsctl client and server. also incorporates the canctl, 
dioctl, and spictl servers.  in addition, implements modbus and http servers.
compile time options can selectively exclude any of the auxiliary (canctl, 
dioctl, spictl, modbus, http) servers.
