#pragma once
#include "JAR-Template/drive.h"

class Drive;

extern Drive chassis;

void default_constants();

void tune_PID();

void left_auto();
void right_auto();
void skills_auto();

// code below is just example code (may be helpful for future)

void tank_odom_test();
void holonomic_odom_test();