#include "clock.h"
#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/clocks.h"
#include "log.h"

#define CLK_SYS_LOW_KHZ 62500
#ifndef SYS_CLK_KHZ
#define SYS_CLK_KHZ 125000
#endif

void clk_info(void) {
    printf("signal     set_khz measured_khz\n");
    printf("clk_ref      %7u      %7u\n", (unsigned)(clock_get_hz(clk_ref)/1000), (unsigned)frequency_count_khz(CLOCKS_FC0_SRC_VALUE_CLK_REF));
    printf("clk_sys      %7u      %7u\n", (unsigned)(clock_get_hz(clk_sys)/1000), (unsigned)frequency_count_khz(CLOCKS_FC0_SRC_VALUE_CLK_SYS));
    printf("clk_peri     %7u      %7u\n", (unsigned)(clock_get_hz(clk_peri)/1000), (unsigned)frequency_count_khz(CLOCKS_FC0_SRC_VALUE_CLK_PERI));
    printf("clk_usb      %7u      %7u\n", (unsigned)(clock_get_hz(clk_usb)/1000), (unsigned)frequency_count_khz(CLOCKS_FC0_SRC_VALUE_CLK_USB));
    printf("clk_adc      %7u      %7u\n", (unsigned)(clock_get_hz(clk_adc)/1000), (unsigned)frequency_count_khz(CLOCKS_FC0_SRC_VALUE_CLK_ADC));
    printf("rosc             -      %7u\n", (unsigned)frequency_count_khz(CLOCKS_FC0_SRC_VALUE_ROSC_CLKSRC));
}

void uptime(void) { printf("uptime: %llu ms\n", (unsigned long long)(time_us_64() / 1000u)); }

void clk_sys_low(void) {
    // При смене частоты ядра (clk_sys) частота периферии (clk_peri) и USB (clk_usb) могут измениться.
    // SYS_CLK_KHZ — рабочую частоту задаёт SDK, вписывать её числом не нужно.
    if (!set_sys_clock_khz(CLK_SYS_LOW_KHZ, true)) {
        LOG_ERR("failed to set clk_sys to %u kHz\n", CLK_SYS_LOW_KHZ);
    } else {
        LOG_INF("clk_sys %u kHz\n", CLK_SYS_LOW_KHZ);
    }
}

void clk_sys_default(void) {
    if (!set_sys_clock_khz(SYS_CLK_KHZ, true)) {
        LOG_ERR("failed to set clk_sys to %u kHz\n", SYS_CLK_KHZ);
    } else {
        LOG_INF("clk_sys %u kHz\n", SYS_CLK_KHZ);
    }
}