#include "pico/stdlib.h" 
#include "hardware/gpio.h" 
 
int main() { 
    gpio_init(25); 
    gpio_set_dir(25, GPIO_OUT); 
    gpio_init(15); 
    gpio_set_dir(15, GPIO_IN); 
    gpio_pull_up(15); 
 
    bool led_state = false; 
    bool last_button_state = true; 
 
    while (1) { 
        bool current_button_state = gpio_get(15); 
        if (current_button_state == 0 && last_button_state == 1) { 
            led_state = !led_state; 
            gpio_put(25, led_state); 
        } 
        last_button_state = current_button_state; 
        sleep_ms(1); 
    } 
} 
