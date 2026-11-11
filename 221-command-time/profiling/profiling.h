#pragma once
#include <stdint.h>
void profiling_init(void);
void profiling_iteration(void);
void profiling_reset_max(void);
uint32_t profiling_avg_us(void);
uint32_t profiling_max_us(void);