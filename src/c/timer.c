#include <pebble.h>
#include <stdio.h>

#include "timer.h"
#include "src/c/main_window.h"

static int seconds;
static int minutes;
static bool breakOff = true;

void timer_event_loop(){
  printf("looper");
    app_timer_register(1000, handle_second_counting_down, NULL);
}

void handle_second_counting_down(void *data) {
  if(breakOff)
    return;
  
  seconds--;
  if(seconds == 0 && minutes != 0) {
    minutes--;
    update_nap_timer(minutes, seconds);
    timer_event_loop();
  } else if (seconds == 0 && minutes == 0) {
    end_nap();
  } else {
    update_nap_timer(minutes, seconds);
    timer_event_loop();
  }
}

void flipBreak() {
  breakOff = !breakOff;
}

void initialize_timer(int nap_minutes) {
  minutes = nap_minutes - 1;
  seconds = 60;
  timer_event_loop();
}
