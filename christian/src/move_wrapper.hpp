#ifndef MOVE_WRAPPER_HEADER_DEF
#define MOVE_WRAPPER_HEADER_DEF
#include "stepper_move.hpp"

// to halt the robot
void total_stop(int file);

// slight turn to left or right
void pitch_left(int file);
void pitch_righ(int file);

//turn to left or right
void turn_left(int file);
void turn_right(int file);

// sharpest possible turning action
void haul_left(int file);
void haul_right(int file);
#endif
