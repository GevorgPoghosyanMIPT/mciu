#include "profiling.h"
#include "pico/stdlib.h"

// Расчёт N: используем сдвиг на 4 бита, что эквивалентно делению на 16.
#define SHIFT_N 4

static uint32_t last_time = 0;
static uint32_t avg_time = 0;
static uint32_t max_time = 0;

void profiling_init(void) { last_time = time_us_32(); }

void profiling_iteration(void) {
    const uint32_t now = time_us_32();
    const uint32_t delta = now - last_time;
    last_time = now;
    // Экспоненциальное сглаживание со сдвигом вправо
    avg_time = avg_time - (avg_time >> SHIFT_N) + (delta >> SHIFT_N);
    if (delta > max_time) { max_time = delta; }
}

void profiling_reset_max(void) { max_time = 0; }
uint32_t profiling_avg_us(void) { return avg_time; }
uint32_t profiling_max_us(void) { return max_time; }