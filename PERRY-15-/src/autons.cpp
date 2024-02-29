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
  chassis.drive_max_voltage = 9;

  while((LIMIT.pressing()==false)){
    CATA.spin(fwd, 8, volt);
  }
  CATA.stop(coast);

  CHAIN.spin(fwd, 180, rpm);
  wait(300, msec);
  CHAIN.stop(hold);

  // first section
  INTAKE.spin(reverse, 11, volt);
  chassis.drive_to_point(7,37);
  wait(1000, msec);
  chassis.turn_to_point(20,37);
  chassis.drive_distance(10);
  INTAKE.spin(fwd, 11, volt);
  chassis.drive_distance(10);
  wait(500, msec);
  INTAKE.spin(reverse, 11, volt);
  INTAKE.spin(fwd, 11, volt);
  chassis.drive_distance(-15);

  // match load area

  wait(100, msec);
  INTAKE.spin(reverse, 11, volt);
  INTAKE.spin(fwd, 11, volt);
  INTAKE.stop(coast);
  chassis.turn_to_point(-20,-5);
  chassis.drive_to_point(-20,-5);
  chassis.drive_distance(10);
  chassis.drive_max_voltage = 4;
  chassis.drive_distance(-10);
  chassis.left_swing_to_angle(-90);
  chassis.drive_distance(-5);
  chassis.left_swing_to_angle(-60);
  chassis.drive_distance(10);
  chassis.left_swing_to_angle(-43);
  chassis.drive_distance(-6);

  // match loading

  chassis.drive_max_voltage = 9;

  LWING.set(true);
  RWING.set(true);
  wait(100, msec);
  for (int i = 0; i < 5; i++) { //22 for matchload
    chassis.drive_distance(-8);
    wait(100, msec);
    chassis.drive_distance(8);
    wait(200, msec);
  }

  float adjustment = 49;

  RWING.set(false);
  chassis.drive_distance(-8);
  chassis.right_swing_to_angle(-18 - adjustment);
  LWING.set(false);
  wait(100, msec);
  chassis.drive_max_voltage = 4;
  chassis.drive_distance(-24);
  chassis.right_swing_to_angle(-33 - adjustment);
  LWING.set(true);
  wait(100, msec);

  chassis.drive_distance(-24 - adjustment);
  chassis.right_swing_to_angle(-44 - adjustment);
  chassis.drive_distance(-20);
  chassis.drive_distance(-20);
  chassis.drive_distance(-24);

  chassis.right_swing_to_angle(-60 - adjustment);
  chassis.drive_distance(-20);
  chassis.right_swing_to_angle(-85 - adjustment);
  chassis.drive_distance(-20);
  chassis.drive_distance(-4);
  chassis.right_swing_to_angle(-105 - adjustment);
  chassis.drive_distance(-4);
  chassis.right_swing_to_angle(-135 - adjustment);

  chassis.drive_max_voltage = 11;
  chassis.drive_distance(-14);
  chassis.drive_distance(14);
  chassis.drive_distance(-14);
  chassis.drive_distance(14);
  chassis.drive_distance(-14);
  chassis.drive_distance(14);

  //go back to other side
  LWING.set(false);
  chassis.right_swing_to_angle(-135);
  // chassis.drive_distance(15);
  // chassis.right_swing_to_angle(-90);
  // chassis.drive_distance(20);
  // chassis.drive_distance(20);
  // chassis.drive_distance(20);
  



  // //first section
  // chassis.drive_to_point(0,-38);
  // chassis.turn_to_point(20,-45);
  // chassis.drive_distance(-30);
  // chassis.drive_distance(8);

  // //match load
  // chassis.turn_to_point(21,2);
  // chassis.drive_to_point(21,2);
  
  // INTAKE.spin(reverse, 11, volt);
  // CHAIN.spin(forward, 11, volt);
  // wait(900, msec);
  // CHAIN.stop(hold);
  // wait(1000,msec);
  // INTAKE.stop(coast);
  // CHAIN.spin(reverse, 11, volt);
  // wait(800, msec);
  // CHAIN.stop(hold);

  // chassis.drive_distance(-15);

  // //goal
  // chassis.left_swing_to_angle(90);
  // chassis.drive_distance(6);
  // chassis.left_swing_to_angle(180);
  // INTAKE.spin(forward, 11, volt);
  // chassis.drive_distance(15);
  // chassis.drive_distance(-15);
  // INTAKE.stop(hold);
  // chassis.drive_distance(15);
  // chassis.drive_distance(-15);

}

void far_auto(){
  odom_constants();
  chassis.set_coordinates(0, 0, 0);

  chassis.drive_max_voltage = 9;

  LWING.set(true);
  RWING.set(true);
  wait(100, msec);
  for (int i = 0; i < 1; i++) { //22 for matchload
    chassis.drive_distance(-8);
    wait(100, msec);
    chassis.drive_distance(8);
    wait(200, msec);
  }
  RWING.set(false);
  chassis.drive_distance(-8);
  chassis.right_swing_to_angle(-18);
  LWING.set(false);
  wait(100, msec);
  chassis.drive_max_voltage = 4;
  chassis.drive_distance(-24);
  chassis.right_swing_to_angle(-33);
  LWING.set(true);
  wait(100, msec);

  chassis.drive_distance(-24);
  chassis.right_swing_to_angle(-44);
  chassis.drive_distance(-20);
  chassis.drive_distance(-20);
  chassis.drive_distance(-24);

  chassis.right_swing_to_angle(-60);
  chassis.drive_distance(-20);
  chassis.right_swing_to_angle(-85);
  chassis.drive_distance(-20);
  chassis.drive_distance(-4);
  chassis.right_swing_to_angle(-105);
  chassis.drive_distance(-4);
  chassis.right_swing_to_angle(-135);

  chassis.drive_max_voltage = 11;
  chassis.drive_distance(-14);
  chassis.drive_distance(14);
  chassis.drive_distance(-14);
  chassis.drive_distance(14);
  chassis.drive_distance(-14);
  chassis.drive_distance(14);

  wait(100, msec);

  chassis.drive_max_voltage = 4;
  chassis.turn_to_point(40, -60);
  chassis.drive_distance(2);
  chassis.right_swing_to_angle(-180);
  chassis.drive_distance(-25);
  chassis.turn_max_voltage = 4;
  chassis.right_swing_to_angle(-130);
  chassis.drive_distance(-15);
  chassis.drive_distance(15);

  LWING.set(false);
  
  chassis.turn_max_voltage = 11;
  chassis.right_swing_to_angle(-195);
  chassis.drive_distance(-30);

  wait(5000, msec); //wait for other robot
  
  RWING.set(true);
  LWING.set(true);
  wait(100, msec);
  chassis.right_swing_to_angle(-60);

  chassis.drive_distance(-10);

  chassis.drive_max_voltage = 11;
  chassis.drive_distance(-20);
  chassis.drive_distance(20);
  chassis.drive_distance(-20);
  chassis.drive_distance(25);

  // //highway
  // chassis.drive_to_point(-4,50);
  // wait(1000,msec);
  // chassis.right_swing_to_angle(230);

  // //middle
  // chassis.drive_distance(45);
  // wait(1000,msec);
  // chassis.turn_to_point(-70,50);
  // chassis.drive_distance(10);
  // wait(1000,msec);
  // chassis.right_swing_to_angle(0);
  // chassis.left_swing_to_angle(170);
  // chassis.left_swing_to_angle(0);

  // //goal corner
  // chassis.turn_to_point(-4,57);
  // chassis.drive_distance(55);
  // wait(1000,msec);

  // //goal zone
  // chassis.drive_distance(-15);
  // chassis.right_swing_to_angle(-30);
  // chassis.drive_distance(10);
  // chassis.right_swing_to_angle(-90);

  // //score!
  // chassis.drive_max_voltage = 12;
  // chassis.drive_distance(15);
  // chassis.drive_distance(-15);
  // chassis.drive_distance(15);
  // chassis.drive_distance(-15);

}

void left_skills_auto(){
  odom_constants();
  chassis.set_coordinates(0, 0, 0);

  chassis.drive_max_voltage = 9;

  LWING.set(true);
  RWING.set(true);
  wait(100, msec);

  for (int i = 0; i < 1; i++) { //22 for matchload
    chassis.drive_distance(-8);
    wait(100, msec);
    chassis.drive_distance(8);
    wait(200, msec);
  }

  LWING.set(false);
  chassis.drive_distance(-8);
  chassis.left_swing_to_angle(18);
  RWING.set(false);
  wait(100, msec);
  chassis.drive_max_voltage = 4;
  chassis.drive_distance(-24);
  chassis.left_swing_to_angle(33);
  RWING.set(true);
  wait(100, msec);
  chassis.drive_distance(-24);
  chassis.left_swing_to_angle(44);
  chassis.drive_distance(-20);
  chassis.drive_distance(-20);
  chassis.drive_distance(-24);

  chassis.left_swing_to_angle(60);
  chassis.drive_distance(-20);
  chassis.left_swing_to_angle(85);
  chassis.drive_distance(-20);
  chassis.drive_distance(-4);
  chassis.left_swing_to_angle(105);
  chassis.drive_distance(-4);
  chassis.left_swing_to_angle(135);

  chassis.drive_max_voltage = 11;
  chassis.drive_distance(-14);
  chassis.drive_distance(14);
  chassis.drive_distance(-14);
  chassis.drive_distance(14);
  chassis.drive_distance(-14);
  chassis.drive_distance(14);

  wait(100, msec);

  chassis.drive_max_voltage = 4;
  chassis.turn_to_point(60, -40);
  chassis.drive_distance(2);
  chassis.left_swing_to_angle(180);
  chassis.drive_distance(-25);
  chassis.turn_max_voltage = 4;
  chassis.left_swing_to_angle(130);
  chassis.drive_distance(-15);
  chassis.drive_distance(15);

  RWING.set(false);
  
  chassis.turn_max_voltage = 11;
  chassis.left_swing_to_angle(195);
  chassis.drive_distance(-30);

  wait(1000, msec); //wait for other robot
  
  RWING.set(true);
  LWING.set(true);
  wait(100, msec);

  chassis.left_swing_to_angle(60);
  chassis.drive_distance(-10);

  chassis.drive_max_voltage = 11;
  chassis.drive_distance(-20);
  chassis.drive_distance(20);
  chassis.drive_distance(-20);
  chassis.drive_distance(25);


  // // //highway
  // chassis.left_swing_to_angle(-20);
  // chassis.drive_distance(-18);
  // chassis.turn_to_point(18,95);
  // chassis.drive_distance(-80);
  // chassis.drive_distance(-14);

  // //goal
  // chassis.right_swing_to_angle(45);
  // chassis.drive_distance(-20);
  // chassis.turn_to_point(40,-110);
  // chassis.drive_max_voltage = 12;
  // chassis.drive_distance(-15);
  // chassis.drive_distance(12);
  // chassis.drive_distance(-15);
  // chassis.drive_distance(10);
  
  // //middle
  // chassis.drive_max_voltage = 6;
  // chassis.turn_to_point(-40,10);
  // chassis.drive_distance(25);
  // chassis.drive_distance(20);
  
  // //collect
  // chassis.turn_to_point(20,-50);
  // chassis.drive_distance(-10);
  // wait(1000,msec);
  // chassis.drive_distance(-10);
  // wait(1000,msec);
  // chassis.left_swing_to_angle(-2);

  // //score
  // chassis.drive_max_voltage = 12;
  // chassis.drive_distance(-15);
  // chassis.drive_distance(15);
  // chassis.drive_distance(-15);
  // chassis.drive_distance(15);
}

void right_skills_auto(){
  odom_constants();
  chassis.set_coordinates(0, 0, 0);

  chassis.drive_max_voltage = 9;

  while((LIMIT.pressing()==false)){
    CATA.spin(fwd, 8, volt);
  }
  CATA.stop(coast);

  CHAIN.spin(fwd, 180, rpm);
  wait(300, msec);
  CHAIN.stop(hold);

  LWING.set(true);
  RWING.set(true);
  wait(100, msec);
  for (int i = 0; i < 1; i++) { //22 for matchload
    chassis.drive_distance(-8);
    wait(100, msec);
    chassis.drive_distance(8);
    wait(200, msec);
  }
  RWING.set(false);
  chassis.drive_distance(-8);
  chassis.right_swing_to_angle(-18);
  LWING.set(false);
  wait(100, msec);
  chassis.drive_max_voltage = 4;
  chassis.drive_distance(-24);
  chassis.right_swing_to_angle(-33);
  LWING.set(true);
  wait(100, msec);

  chassis.drive_distance(-24);
  chassis.right_swing_to_angle(-44);
  chassis.drive_distance(-20);
  chassis.drive_distance(-20);
  chassis.drive_distance(-24);

  chassis.right_swing_to_angle(-60);
  chassis.drive_distance(-20);
  chassis.right_swing_to_angle(-85);
  chassis.drive_distance(-20);
  chassis.drive_distance(-4);
  chassis.right_swing_to_angle(-105);
  chassis.drive_distance(-4);
  chassis.right_swing_to_angle(-135);

  chassis.drive_max_voltage = 11;
  chassis.drive_distance(-14);
  chassis.drive_distance(14);
  chassis.drive_distance(-14);
  chassis.drive_distance(14);
  chassis.drive_distance(-14);
  chassis.drive_distance(14);

  wait(100, msec);

  chassis.drive_max_voltage = 4;
  chassis.turn_to_point(40, -60);
  chassis.drive_distance(2);
  chassis.right_swing_to_angle(-180);
  chassis.drive_distance(-25);
  chassis.turn_max_voltage = 4;
  chassis.right_swing_to_angle(-130);
  chassis.drive_distance(-15);
  chassis.drive_distance(15);

  LWING.set(false);
  
  chassis.turn_max_voltage = 11;
  chassis.right_swing_to_angle(-195);
  chassis.drive_distance(-30);
  
  RWING.set(true);
  LWING.set(true);
  wait(100, msec);
  chassis.right_swing_to_angle(-60);

  chassis.drive_distance(-10);

  chassis.drive_max_voltage = 11;
  chassis.drive_distance(-20);
  chassis.drive_distance(20);
  chassis.drive_distance(-20);
  chassis.drive_distance(25);



  // odom_constants();
  // chassis.set_coordinates(0, 0, 0);

  // chassis.drive_max_voltage = 11;
  // chassis.right_swing_to_angle(-48);
  // wait(1000,msec);

  // //highway
  // chassis.right_swing_to_angle(20);
  // chassis.drive_distance(-18);
  // chassis.turn_to_point(-16,80);
  // chassis.drive_distance(-80);
  // chassis.drive_distance(-11);

  // //goal
  // chassis.left_swing_to_angle(-45);
  // chassis.drive_distance(-20);
  // chassis.turn_to_point(-40,-110);
  // chassis.drive_max_voltage = 12;
  // chassis.drive_distance(-15);
  // chassis.drive_distance(12);
  // chassis.drive_distance(-15);
  // chassis.drive_distance(10);
  
  // //middle
  // chassis.drive_max_voltage = 6;
  // chassis.turn_to_point(40,10);
  // chassis.drive_distance(25);
  // chassis.drive_distance(20);
  
  // //collect
  // chassis.turn_to_point(-20,-50);
  // chassis.drive_distance(-10);
  // wait(1000,msec);
  // chassis.drive_distance(-10);
  // wait(1000,msec);
  // chassis.right_swing_to_angle(2);

  // //score
  // chassis.drive_max_voltage = 12;
  // chassis.drive_distance(-15);
  // chassis.drive_distance(15);
  // chassis.drive_distance(-15);
  // chassis.drive_distance(15);
}

void driver_skills(){
  odom_constants();
  chassis.set_coordinates(0, 0, 0);

  chassis.drive_max_voltage = 9;

  while((LIMIT.pressing()==false)){
    CATA.spin(fwd, 8, volt);
  }
  CATA.stop(coast);

  LWING.set(true);
  RWING.set(true);
  wait(100, msec);
  for (int i = 0; i < 1; i++) { //22 for matchload
    chassis.drive_distance(-8);
    wait(100, msec);
    chassis.drive_distance(8);
    wait(200, msec);
  }
  RWING.set(false);
  LWING.set(false);
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