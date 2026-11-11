#include "pico/stdlib.h" 
#include "hardware/structs/sio.h" 
 
int main() { 
    sio_hw->gpio_oe_set = (1 << 25); 
    while (1) { 
        sio_hw->gpio_set = (1 << 25); 
        sleep_ms(250); 
        sio_hw->gpio_clr = (1 << 25); 
        sleep_ms(250); 
    } 
} 
