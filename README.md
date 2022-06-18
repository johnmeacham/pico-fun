# pico-fun
Various projects with the raspberry pi pico

## onoff.c

use your reset button as a power switch. very useful for the battery powered
lilygo models that don't have a physical way to disconnect the battery. You
can turn off the periherals and shut down the raspberry pi pico clock.

Just call the onoff() function at the beginning of your main program and it
will let you toggle on and off your pico. It checks various hardware
registers and a flag to make sure it was reset due to a power button and not
due to initial power on (which may have garbage values in memory) or
rebooting after programming it with the bootloader so it will automatically
turn on when reprogrammed.

this does not interfere with the double reset to get into the bootloader module
if you have it installed.

