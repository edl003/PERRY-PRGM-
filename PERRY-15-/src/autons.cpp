#include "vex.h"

void default_constants(){
  // Each constant set is in the form of (maxVoltage, kP, kI, kD, startI).
  // chassis.set_drive_constants(12, 1.25, 0, 1.5, 0);
  // chassis.set_heading_constants(12, 0.34, 0, 0.2, 0);
  // chassis.set_turn_constants(12, 0.25, 0, 1.475, 15);
  // chassis.set_swing_constants(12, 0.3, 0.001, 2, 15);

  chassis.set_drive_constants(12, 1.25, 0, 1, 0); //10, 1.5, 0, 10, 0
  chassis.set_heading_constants(12, 0.33, 0, 0.125, 0); //12, .4, 0, 1, 0
  chassis.set_turn_constants(12, 0.2, 0.0, 1.475, 15); //.4, .03, 3 // 12, .19, 0.01, 1.35, 15 ku .2
  // 180 deg constants chassis.set_turn_constants(12, 0.2, 0.0, 1.9, 15);
  chassis.set_swing_constants(12, .3, .001, 2, 15);

  // Each exit condition set is in the form (settle_error, settle_time, timeout).
  chassis.set_drive_exit_conditions(1.5, 75, 1000);
  chassis.set_turn_exit_conditions(5, 75, 1000);
  chassis.set_swing_exit_conditions(1, 75, 1000);
}

void odom_constants(){
  default_constants();
  chassis.drive_max_voltage = 12;
  chassis.drive_settle_error = 3;
}

void tune_PID(){
  odom_constants();
  chassis.set_coordinates(0, 0, 0);
  chassis.drive_max_voltage = 11;

  //turn PD
  wait(5000, msec);
  chassis.turn_to_point(100,0);
  wait(5000, msec);
  chassis.turn_to_point(0,-100);
  wait(5000, msec);
  chassis.turn_to_point(-100,0);
  wait(5000, msec);
  chassis.turn_to_point(0, 100);

  // //drive PD
  // wait(5000, msec);
  // chassis.drive_distance(20);
  // wait(5000, msec);
  // chassis.drive_distance(-20);

  // //heading PD
  // wait(5000, msec);
  // chassis.drive_to_point(-20,40);
  // wait(5000, msec);
  // chassis.drive_to_point(0,0);

  // //swing PID
  // wait(5000, msec);
  // chassis.left_swing_to_angle(90);
  // wait(5000, msec);
  // chassis.left_swing_to_angle(180);
  // wait(5000, msec);
  // chassis.left_swing_to_angle(270);
  // wait(5000, msec);
  // chassis.left_swing_to_angle(360);
}

void close_auto(){
  odom_constants();
  chassis.set_coordinates(0, 0, 0);
  chassis.drive_max_voltage = 11;

  //first section
  chassis.drive_to_point(0,-40);
  chassis.turn_to_point(24,-40);
  chassis.drive_distance(-25);
  chassis.drive_distance(10);

  //second section
  chassis.turn_to_point(2,40);
  chassis.drive_distance(20);
  // chassis.turn_to_point(20,40);
  // chassis.drive_distance(17);
  // chassis.drive_distance(-16);

  // //match load
  // chassis.turn_to_point(-8,-5);
  // chassis.drive_to_point(-8,-5);
  // wait(1000, msec);
  // chassis.drive_distance(15);
  // wait(1000, msec);
  // chassis.drive_distance(-12);
}

void far_auto(){
  odom_constants();
  chassis.set_coordinates(0, 0, 0);
  chassis.drive_max_voltage = 10; 

  //highway
  chassis.drive_to_point(-4,50);
  chassis.right_swing_to_angle(235);

  // //goal
  // chassis.drive_distance(-15);

  // //middle
  // chassis.turn_to_point(50, -20);

}

void left_skills_auto(){
  odom_constants();
  chassis.set_coordinates(0, 0, 0);

  chassis.drive_max_voltage = 11;
  chassis.left_swing_to_angle(46);

  // //highway
  chassis.left_swing_to_angle(-20);
  chassis.drive_distance(-18);
  chassis.turn_to_point(19,95);
  chassis.drive_distance(-82);

  //goal
  chassis.right_swing_to_angle(45);
  chassis.drive_distance(-24);
  chassis.turn_to_point(40,-90);
  chassis.drive_distance(-15);
  chassis.drive_distance(15);
  
  //middle
  chassis.drive_max_voltage = 8;
  chassis.turn_to_point(-65,-9);
  chassis.drive_to_point(-65,-9);
}

void right_skills_auto(){
  odom_constants();
  chassis.set_coordinates(0, 0, 0);

  chassis.drive_max_voltage = 11;
  chassis.right_swing_to_angle(-46);

  //highway
  chassis.drive_distance(-10);
  chassis.turn_to_point(-5,-8);
  chassis.drive_distance(14);
  chassis.turn_to_point(-10,-85);
  chassis.drive_to_point(-10,-85);

  //goal
  chassis.right_swing_to_angle(135);
  chassis.drive_distance(28);
  chassis.turn_to_point(20,-100);
  chassis.drive_distance(15);
  chassis.drive_distance(-15);
  
  //middle
  chassis.turn_to_point(20, -60);
}

// code below is just example code (may be helpful for future)

void tank_odom_test(){
  odom_constants();
  chassis.set_coordinates(0, 0, 0);
  chassis.turn_to_point(24, 24);
  chassis.drive_to_point(24,24);
  chassis.drive_to_point(0,0);
  chassis.turn_to_angle(0);
}

void holonomic_odom_test(){
  odom_constants();
  chassis.set_coordinates(0, 0, 0);
  chassis.holonomic_drive_to_point(0, 18, 90);
  chassis.holonomic_drive_to_point(18, 0, 180);
  chassis.holonomic_drive_to_point(0, 18, 270);
  chassis.holonomic_drive_to_point(0, 0, 0);
}