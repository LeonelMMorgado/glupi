#ifndef _BUTTON_H
#define _BUTTON_H

#include <stdbool.h>

typedef struct _button {
    bool down, last, last_tick, pressed, pressed_tick;
} Button;

#endif

