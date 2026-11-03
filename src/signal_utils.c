#include <signal.h>
#include <stdio.h>
#include "signal_utils.h"

static volatile sig_atomic_t interrupted = 0;

static void signal_handler(int signal_number){
    switch (signal_number){
        case SIGINT:
        case SIGQUIT:
        case SIGTERM:
            interrupted = signal_number;
            break;
        default:
            break;
    }
}

void setup_signals(void){
    struct sigaction action = {0};
    sigemptyset(&action.sa_mask);
    action.sa_handler = &signal_handler;
    action.sa_flags = 0;
    sigaction(SIGINT, &action, NULL);
    sigaction(SIGQUIT, &action, NULL);
    sigaction(SIGTERM, &action, NULL);
}

bool is_interrupted(void){
    return interrupted != 0;
}