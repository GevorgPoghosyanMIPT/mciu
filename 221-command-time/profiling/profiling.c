#include "profiling.h"
#include "pico/stdlib.h"
static uint64_t last_time = 0;
static uint64_t total_time = 0;
static uint32_t count = 0;
static uint32_t max_time = 0;
void profiling_init(void) { last_time = time_us_64(); }
void profiling_iteration(void) {
    const uint64_t now = time_us_64();
    const uint32_t delta = (uint32_t)(now - last_time);
    last_time = now;
    if (count < 1000000) { total_time += delta; count++; }
    if (delta > max_time) { max_time = delta; }
}
void profiling_reset_max(void) { max_time = 0; }
uint32_t profiling_avg_us(void) { return count ? (uint32_t)(total_time / count) : 0; }
uint32_t profiling_max_us(void) { return max_time; }