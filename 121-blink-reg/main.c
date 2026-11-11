#include "pico/stdlib.h"
#include "hardware/gpio.h"
#include "hardware/structs/sio.h"

int main() {
    gpio_set_dir(25, GPIO_OUT);
    while (1) {
        sio_hw->gpio_out_set = 1 << 25;
        sleep_ms(250);
        sio_hw->gpio_out_clr = 1 << 25;
        sleep_ms(250);
    }
}
