#pragma once
#include "src/c/timer.h"

void main_window_create();

void end_nap();

void update_nap_timer(int minutes, int seconds);

void main_window_destroy();

Window *main_window_get_window();