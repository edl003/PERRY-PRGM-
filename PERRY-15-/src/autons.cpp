#include "vex.h"

void default_constants(){
  //Settle Error: how far away from the target will the robot be considered settled. 
  //Settle Time: how long is has to be at the target. 
  //Timeout: If your robot isn't going to get to the target, then it continues with the code.
  
  // Each constant set is in the form of (maxVoltage, kP, kI, kD, startI).
  chassis.set_drive_constants(12, 1.25, 0, 1, 0); //10, 1.5, 0, 10, 0
  chassis.set_heading_constants(12, 0.33, 0, 0.125, 0); //12, .4, 0, 1, 0
  chassis.set_turn_constants(12, 0.2, 0.0, 1.475, 15); //.4, .03, 3 // 12, .19, 0.01, 1.35, 15 ku .2
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
  chassis.drive_max_voltage = 9;

  // //turn PD
  // wait(5000, msec);
  // chassis.turn_to_point(100,0);
  // wait(5000, msec);
  // chassis.turn_to_point(0,-100);
  // wait(5000, msec);
  // chassis.turn_to_point(-100,0);
  // wait(5000, msec);
  // chassis.turn_to_point(0, 100);

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
  chassis.drive_max_voltage = 8;

  float scale15 = 0.98;

  LLIFT.set(false);
  RLIFT.set(false);
  wait(100, msec);
  chassis.drive_distance(-5);
  chassis.drive_distance(5);

  CHAIN.spin(fwd, 180, rpm);
  wait(200, msec);
  CHAIN.stop(hold);



  // first section
  INTAKE.spin(reverse, 11, volt);
  chassis.drive_to_point(9,36);
  wait(500, msec);
  chassis.turn_to_point(0,0);
  chassis.drive_distance(16);
  wait(500, msec);
  INTAKE.spin(fwd, 11, volt);
  INTAKE.spin(reverse, 11, volt);
  INTAKE.spin(fwd, 11, volt);
  wait(500, msec);

  chassis.drive_distance(-10);
  chassis.turn_to_angle(-5);

  INTAKE.spin(reverse, 11, volt);
  chassis.drive_distance(10);
  wait(500, msec);
  chassis.turn_to_point(1,0);
  chassis.drive_distance(25);
  wait(500, msec);
  INTAKE.spin(fwd, 11, volt);
  INTAKE.spin(reverse, 11, volt);
  INTAKE.spin(fwd, 11, volt);
  wait(500, msec);
  chassis.drive_distance(-14);
  chassis.turn_to_angle(88);

  chassis.drive_max_voltage = 3;
  wait(500, msec);
  chassis.drive_distance(16);
  INTAKE.spin(fwd, 11, volt);
  INTAKE.spin(reverse, 11, volt);
  INTAKE.spin(fwd, 11, volt);
  chassis.drive_distance(6);
  wait(500, msec);
  chassis.drive_distance(-8);
  INTAKE.stop(coast);


  //match load area
  chassis.drive_max_voltage = 8; 
  chassis.turn_to_point(45, 80);
  chassis.drive_distance(-20);
  chassis.drive_distance(-20);
  chassis.drive_distance(-20);
  chassis.drive_distance(10);
  chassis.left_swing_to_angle(-50);
  chassis.drive_distance(9);
  chassis.left_swing_to_angle(-42);
  chassis.drive_distance(-4);
  wait(500, msec);


  float adjustment = -132; 


  //matchloading
  chassis.drive_max_voltage = 6.5;

  LWING.set(true);
  RWING.set(true);
  wait(100, msec);

  float backDRIVE = 6;

  for (int i = 0; i < 4; i++) { //5 for matchload
    chassis.drive_distance(-6 * scale15);
    wait(200, msec);
    chassis.drive_distance(backDRIVE * scale15);
    //backDRIVE = backDRIVE * 0.995;
    wait(200, msec);
  }
  RWING.set(false);

  chassis.drive_max_voltage = 8;
  chassis.drive_distance(-12 * scale15);
  chassis.left_swing_to_angle(70 + adjustment); 
  chassis.drive_distance(-8 * scale15);
  chassis.left_swing_to_angle(55 + adjustment);
  chassis.drive_distance(-8 * scale15);
  chassis.left_swing_to_angle(47 + adjustment);
  wait(100, msec);



  //highway
  chassis.drive_max_voltage = 6; 
  chassis.drive_distance(-22 * scale15);
  chassis.drive_distance(-20 * scale15);
  chassis.drive_distance(-18 * scale15);

  chassis.drive_distance(-5 * scale15);
  chassis.right_swing_to_angle(30 + adjustment); 
  chassis.drive_distance(-20 * scale15);
  chassis.left_swing_to_angle(20 + adjustment);
  chassis.drive_distance(-22 * scale15);


  //side scoring
  chassis.drive_max_voltage = 10;
  chassis.right_swing_to_angle(-20 + adjustment);
  chassis.drive_distance(-12 * scale15);
  chassis.right_swing_to_angle(-22 + adjustment);
  chassis.drive_distance(4 * scale15);
  chassis.drive_distance(-16 * scale15);
  chassis.drive_distance(10 * scale15);
  chassis.drive_distance(-14 * scale15);
  LWING.set(false);
  wait(500, msec);
  chassis.drive_distance(10 * scale15);

  //if possible, get this robot to go back to the other side to prevent getting descored on. 

  //move back to other side
  chassis.drive_distance(20);
  chassis.drive_distance(20);
  
}

void far_auto(){
  odom_constants();
  chassis.set_coordinates(0, 0, 0);
  chassis.drive_max_voltage = 8;

  float scale24 = 0.94;

  LLIFT.set(false);
  RLIFT.set(false);
  wait(500, msec);

  CHAIN.spin(fwd, 180, rpm);
  INTAKE.spin(reverse, 11, volt);
  wait(870, msec);
  CHAIN.stop(hold);
  
  //goal
  chassis.drive_distance(-4 * scale24);
  chassis.turn_to_angle(85);
  chassis.drive_distance(10 * scale24);
  chassis.turn_to_angle(135);
  chassis.drive_distance(-2 * scale24);
  CHAIN.spin(reverse, 180, rpm);
  wait(725, msec);
  CHAIN.stop(hold);
  INTAKE.stop(coast);
  chassis.drive_distance(14 * scale24);
  chassis.drive_distance(-12 * scale24);



  //matchload
  chassis.drive_max_voltage = 4;
  chassis.left_swing_to_angle(120);
  chassis.drive_distance(-9 * scale24);
  chassis.left_swing_to_angle(100);
  chassis.drive_distance(-8 * scale24);
  chassis.left_swing_to_angle(90);
  chassis.drive_distance(6 * scale24);

  chassis.drive_max_voltage = 6.5;

  LWING.set(true);
  RWING.set(true);
  wait(100, msec);

  float backDRIVE = 6;

  for (int i = 0; i < 2; i++) { //5 for matchload
    chassis.drive_distance(-6 * scale24);
    wait(200, msec);
    chassis.drive_distance(backDRIVE * scale24);
    //backDRIVE = backDRIVE * 0.995;
    wait(200, msec);
  }
  RWING.set(false);

  chassis.drive_max_voltage = 8;
  chassis.drive_distance(-12 * scale24);
  chassis.left_swing_to_angle(70); 
  chassis.drive_distance(-8 * scale24);
  chassis.left_swing_to_angle(55);
  chassis.drive_distance(-8 * scale24);
  chassis.left_swing_to_angle(47);
  wait(100, msec);



  //highway
  chassis.drive_max_voltage = 6; 
  chassis.drive_distance(-22 * scale24);
  chassis.drive_distance(-20 * scale24);
  chassis.drive_distance(-18 * scale24);

  chassis.drive_distance(-5 * scale24);
  chassis.right_swing_to_angle(30); 
  chassis.drive_distance(-16 * scale24);
  chassis.left_swing_to_angle(20);
  chassis.drive_distance(-24 * scale24);


  //side scoring
  chassis.drive_max_voltage = 10;
  chassis.right_swing_to_angle(-20);
  chassis.drive_distance(-12 * scale24);
  chassis.right_swing_to_angle(-22);
  chassis.drive_distance(4 * scale24);
  chassis.drive_distance(-16 * scale24);
  chassis.drive_distance(10 * scale24);
  chassis.drive_distance(-14 * scale24);
  LWING.set(false);
  wait(500, msec);
  chassis.drive_distance(10 * scale24);
  chassis.drive_distance(-14 * scale24);
  chassis.drive_distance(10 * scale24);



  //middle scoring
  chassis.drive_max_voltage = 6; 
  chassis.turn_to_point(0, -55);
  
  wait(1000, msec);
  chassis.drive_distance(20);
  chassis.drive_distance(20);
  chassis.drive_distance(5);
  chassis.turn_to_point(-80,0);

  LWING.set(true);
  RWING.set(true);
  wait(100, msec);

  chassis.drive_distance(-22);
  chassis.turn_to_angle(50);
  chassis.drive_distance(-26);
  chassis.drive_distance(24);

}

void left_skills_auto(){
  odom_constants();
  chassis.set_coordinates(0, 0, 0);
}

void right_skills_auto(){
  odom_constants();
  chassis.set_coordinates(0, 0, 0);
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