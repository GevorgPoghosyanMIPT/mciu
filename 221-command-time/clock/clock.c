#include "clock.h"
#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/clocks.h"
#include "log.h"
void clk_info(void) {
    printf("signal     set_khz measured_khz\n");
    printf("clk_ref      %7u      %7u\n", (unsigned)(clock_get_hz(clk_ref) / 1000), (unsigned)(clock_get_hz(clk_ref) / 1000));
    printf("clk_sys      %7u      %7u\n", (unsigned)(clock_get_hz(clk_sys) / 1000), (unsigned)(clock_get_hz(clk_sys) / 1000));
    printf("clk_peri     %7u      %7u\n", (unsigned)(clock_get_hz(clk_peri) / 1000), (unsigned)(clock_get_hz(clk_peri) / 1000));
    printf("clk_usb      %7u      %7u\n", (unsigned)(clock_get_hz(clk_usb) / 1000), (unsigned)(clock_get_hz(clk_usb) / 1000));
    printf("clk_adc      %7u      %7u\n", (unsigned)(clock_get_hz(clk_adc) / 1000), (unsigned)(clock_get_hz(clk_adc) / 1000));
    printf("rosc             -      %7u\n", (unsigned)(clock_get_hz(clk_rosc) / 1000));
}
void uptime(void) { printf("uptime: %llu ms\n", (unsigned long long)(time_us_64() / 1000u)); }
static void clk_sys_set(uint32_t hz) {
    set_sys_clock_khz(hz / 1000, true);
    LOG_INF("clk_sys %u kHz\n", (unsigned)(hz / 1000));
}
void clk_sys_low(void) { clk_sys_set(62500000); }
void clk_sys_default(void) { clk_sys_set(125000000); }