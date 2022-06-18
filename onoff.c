#include <stdio.h>
#include "pico/stdlib.h"
#include "pico/platform.h"
#include "hardware/clocks.h"
#include "hardware/sync.h"
#include "hardware/xosc.h"
#include "hardware/watchdog.h"
#include "hardware/structs/vreg_and_chip_reset.h"
//#include "pico/sleep.h"

/* set a flag and use the reset button as an on off switch. Useful for battery
 * powered devices without a physical switch.
 *
 * It will not treat it as a turning off button press if the reset was not due to
 * pressing the run button nor if the watchdog timer scratch registers were used
 * to override the normal boot sequence.
 *
 * Call this early in main. if you want usb picotool reset support, set up usb
 * stdio before calling it.
 *
 * TODO(jwm): can we do better than wfi for power consumption?  Leaving on usb
 * stdio for picotool support uses power.
 */
void onoff(void)
{
        static uint32_t __uninitialized_ram(flag); bool had_run =
                vreg_and_chip_reset_hw->chip_reset &
                VREG_AND_CHIP_RESET_CHIP_RESET_HAD_RUN_BITS; if
        (!watchdog_hw->scratch[5] && had_run && flag == 42) {
                flag = 0;
// uncomment this if you want to go into really really deep sleep that can't be
// woken by a programmer.
//               clock_disable(clk_adc); xosc_dormant();
                for (;;) __wfi();
        } flag = 42;
}
