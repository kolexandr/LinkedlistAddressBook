#ifndef SIGNAL_UTILS
#define SIGNAL_UTILS

#include <stdbool.h>

void register_cleanup(void (*cleanup)(void));

void setup_signals(void);

bool is_interrupted(void);

#endif