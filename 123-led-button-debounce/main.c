#include "pico/stdlib.h"
#include "hardware/gpio.h"

bool get_button_debounce(uint pin) {
    if (gpio_get(pin) == 0) {
        sleep_ms(20);
        if (gpio_get(pin) == 0) {
            return true;
        }
    }
    return false;
}

int main() {
    gpio_init(25);
    gpio_set_dir(25, GPIO_OUT);
    gpio_init(15);
    gpio_set_dir(15, GPIO_IN);
    gpio_pull_up(15);

    bool led_state = false;

    while (1) {
        if (get_button_debounce(15)) {
            led_state = !led_state;
            gpio_put(25, led_state);
            while (get_button_debounce(15)) {
                sleep_ms(1);
            }
        }
        sleep_ms(1);
    }
}
