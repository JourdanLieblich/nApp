#pragma once

// Here will go all of the timer handler functions to perform the countdown

// Will only update the screen with the time remaining for every minute thats passed until the final 
// 60 seconds where it'll show the complete countdown.

void handle_second_counting_down();

void flipBreak();

void initialize_timer(int nap_minutes);