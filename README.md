# pico-fun
Various projects with the raspberry pi pico

## c3bridge

USB->serial bridge with command line editing.

If you have one of the pico/esp32 hybrid boards, this is a simple proram
that lets you use your usb serial port to talk directly to the esp32 via the
pico. It has full line editing and history capabilty, and is a good demo of
http://github.com/johnmeacham/tiny_editline as well.

This can be used as a generic USB to serial bridge that allows command line
history and editing as well and is not esp32 specific.

Example board: https://www.aliexpress.com/item/3256803977826910.html

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

