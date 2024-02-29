#pragma once
#include "JAR-Template/drive.h"

class Drive;

extern Drive chassis;

void default_constants();

void tune_PID();

void close_auto();
void far_auto();
void left_skills_auto();
void right_skills_auto();
void driver_skills();

// code below is just example code (may be helpful for future)

void tank_odom_test();
void holonomic_odom_test();