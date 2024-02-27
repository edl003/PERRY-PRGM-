
#include "vex.h"

// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// L1                   motor         1               
// L2                   motor         2               
// L3                   motor         3               
// L4                   motor         4               
// R1                   motor         5               
// R2                   motor         6               
// R3                   motor         7               
// R4                   motor         8               
// Inertial             inertial      9               
// Controller1          controller                    
// CATA                 motor_group   20, 19          
// INTAKE               motor         18              
// CHAIN                motor         17              
// LWING                digital_out   A               
// RWING                digital_out   B               
// BLOCKER              digital_out   C               
// LIFT                 digital_out   D               
// ---- END VEXCODE CONFIGURED DEVICES ----

using namespace vex;
competition Competition;

/*---------------------------------------------------------------------------*/
/*                             VEXcode Config                                */
/*                                                                           */
/*  Before you do anything else, start by configuring your motors and        */
/*  sensors using the V5 port icon in the top right of the screen. Doing     */
/*  so will update robot-config.cpp and robot-config.h automatically, so     */
/*  you don't have to. Ensure that your motors are reversed properly. For    */
/*  the drive, spinning all motors forward should drive the robot forward.   */
/*---------------------------------------------------------------------------*/

/*---------------------------------------------------------------------------*/
/*                             JAR-Template Config                           */
/*                                                                           */
/*  Where all the magic happens. Follow the instructions below to input      */
/*  all the physical constants and values for your robot. You should         */
/*  already have configured your robot manually with the sidebar configurer. */
/*---------------------------------------------------------------------------*/

Drive chassis(

//Specify your drive setup below. There are seven options:
//ZERO_TRACKER_NO_ODOM, ZERO_TRACKER_ODOM, TANK_ONE_ENCODER, TANK_ONE_ROTATION, TANK_TWO_ENCODER, TANK_TWO_ROTATION, HOLONOMIC_TWO_ENCODER, and HOLONOMIC_TWO_ROTATION
//For example, if you are not using odometry, put ZERO_TRACKER_NO_ODOM below:
ZERO_TRACKER_ODOM,

//Add the names of your Drive motors into the motor groups below, separated by commas, i.e. motor_group(Motor1,Motor2,Motor3).
//You will input whatever motor names you chose when you configured your robot using the sidebar configurer, they don't have to be "Motor1" and "Motor2".

//Left Motors:
motor_group(L1, L2, L3, L4),

//Right Motors:
motor_group(R1, R2, R3, R4),

//Specify the PORT NUMBER of your inertial sensor, in PORT format (i.e. "PORT1", not simply "1"):
PORT16,

//Input your wheel diameter. (4" omnis are actually closer to 4.125"):
2.75,

//External ratio, must be in decimal, in the format of input teeth/output teeth.
//If your motor has an 84-tooth gear and your wheel has a 60-tooth gear, this value will be 1.4.
//If the motor drives the wheel directly, this value is 1:
0.75,

//Gyro scale, this is what your gyro reads when you spin the robot 360 degrees.
//For most cases 360 will do fine here, but this scale factor can be very helpful when precision is necessary.
360,

/*---------------------------------------------------------------------------*/
/*                                  PAUSE!                                   */
/*                                                                           */
/*  The rest of the drive constructor is for robots using POSITION TRACKING. */
/*  If you are not using position tracking, leave the rest of the values as  */
/*  they are.                                                                */
/*---------------------------------------------------------------------------*/

//If you are using ZERO_TRACKER_ODOM, you ONLY need to adjust the FORWARD TRACKER CENTER DISTANCE.

//FOR HOLONOMIC DRIVES ONLY: Input your drive motors by position. This is only necessary for holonomic drives, otherwise this section can be left alone.
//LF:      //RF:    
PORT1,     -PORT2,

//LB:      //RB: 
PORT3,     -PORT4,

//If you are using position tracking, this is the Forward Tracker port (the tracker which runs parallel to the direction of the chassis).
//If this is a rotation sensor, enter it in "PORT1" format, inputting the port below.
//If this is an encoder, enter the port as an integer. Triport A will be a "1", Triport B will be a "2", etc.
3,

//Input the Forward Tracker diameter (reverse it to make the direction switch):
2.75,

//Input Forward Tracker center distance (a positive distance corresponds to a tracker on the right side of the robot, negative is left.)
//For a zero tracker tank drive with odom, put the positive distance from the center of the robot to the right side of the drive.
//This distance is in inches:
6.00,

//Input the Sideways Tracker Port, following the same steps as the Forward Tracker Port:
1,

//Sideways tracker diameter (reverse to make the direction switch):
-2.75,

//Sideways tracker center distance (positive distance is behind the center of the robot, negative is in front):
5.5

);

int current_auton_selection = 1;
bool auto_started = false;

void pre_auton(void) {
  // Initializing Robot Configuration. DO NOT REMOVE!
  vexcodeInit();
  default_constants();

  Inertial.calibrate();
  while(Inertial.isCalibrating()) {
    wait(100, msec);
  }

  CHAIN.resetPosition();

  while(auto_started == false){            //Changing the names below will only change their names on the
    Brain.Screen.clearScreen();            //brain screen for auton selection.
    switch(current_auton_selection){       //Tap the brain screen to cycle through autons.
      case 0:
        Brain.Screen.printAt(50, 50, "TUNE PID");
        break;
      case 1:
        Brain.Screen.printAt(50, 50, "CLOSE AUTO");
        break;
      case 2:
        Brain.Screen.printAt(50, 50, "FAR AUTO");
        break;
      case 3:
        Brain.Screen.printAt(50, 50, "LEFT SKILLS AUTO");
        break;
      case 4:
        Brain.Screen.printAt(50, 50, "RIGHT SKILLS AUTO");
    }
    if(Brain.Screen.pressing()){
      while(Brain.Screen.pressing()) {}
      current_auton_selection ++;
    } else if (current_auton_selection == 5){
      current_auton_selection = 0;
    }
    task::sleep(10);
  }
}

void autonomous(void) {
  auto_started = true;
  switch(current_auton_selection){  
    case 0:
      tune_PID();
      break;        
    case 1:         
      close_auto();
      break;
    case 2:
      far_auto();
      break;
    case 3:
      left_skills_auto();
      break;
    case 4:
      right_skills_auto();
      break;
 }
}

/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                              User Control Task                            */
/*                                                                           */
/*  This task is used to control your robot during the user control phase of */
/*  a VEX Competition.                                                       */
/*                                                                           */
/*  You must modify the code to add your own robot specific commands here.   */
/*---------------------------------------------------------------------------*/

void usercontrol(void) {
  // User control code here, inside the loop
  int CHAIN_speed = 180;
  int CATA_state = 0;

  bool wingsToggle = false;
  bool wingsButton = false;

  bool wingLToggle = false;
  bool wingLButton = false;

  bool wingRToggle = false;
  bool wingRButton = false;

  bool liftToggle = false;
  bool liftButton = false; 

  bool cataKEY1 = false;
  bool cataKEY2 = false;

  bool intakeKEY1 = false;
  bool intakeKEY2 = false;

  bool chainKEY1 = false;
  bool chainKEY2 = false;

  bool wingsKEY = false;
  bool wingsLKEY = false;
  bool wingsRKEY = false;

  bool liftKEY = false;

  while (1) {
    // This is the main execution loop for the user control program.
    // Each time through the loop your program should update motor + servo
    // values based on feedback from the joysticks.

    // ........................................................................
    // Insert user code here. This is where you use the joystick values to
    // update your motors, etc.
    // ........................................................................

    cataKEY1 = Controller1.ButtonA.pressing();
    cataKEY2 = Controller1.ButtonY.pressing();

    intakeKEY1 = Controller1.ButtonR1.pressing();
    intakeKEY2 = Controller1.ButtonR2.pressing();
    
    chainKEY1 = Controller1.ButtonL1.pressing();
    chainKEY2 = Controller1.ButtonL2.pressing();
    
    wingsKEY = Controller1.ButtonX.pressing();
    wingsLKEY = Controller1.ButtonLeft.pressing();
    wingsRKEY = Controller1.ButtonRight.pressing();

    liftKEY = Controller1.ButtonUp.pressing();

    if(cataKEY2){
      CATA_state = 1;
    }

    if((LIMIT.pressing()==false) && (CATA_state == 0)){
      wait(250, msec);
      CATA.spin(fwd, 9, volt);
    }else if(cataKEY1){
      CATA.spin(fwd, 9, volt);
    }else{
      CATA.stop(hold);
    }
    
    if(intakeKEY1){
      INTAKE.spin(reverse, 11, volt);
    }else if(intakeKEY2){
      INTAKE.spin(fwd, 11, volt); 
    }else{
      INTAKE.spin(reverse, 2, volt);
    }

    if (chainKEY1){
      CHAIN.spin(reverse, CHAIN_speed, rpm);
    } else if (chainKEY2){
      CHAIN.spin(fwd, CHAIN_speed, rpm);
    } else{
      CHAIN.stop(hold);
    }

    if ((wingsKEY && !wingsButton)){
      wingsButton = true; 
      wingsToggle = !wingsToggle;
    }
    else if ((!wingsKEY)) wingsButton = false;

    if (wingsToggle){
      LWING.set(true);
      RWING.set(true);
    } else if (!wingsToggle) {
      LWING.set(false);
      RWING.set(false);
    }

    if ((wingsLKEY && !wingLButton)){
      wingLButton = true; 
      wingLToggle = !wingLToggle;
    }
    else if ((!wingsLKEY)) wingLButton = false;

    if (wingLToggle){
      LWING.set(true);
    } else if (!wingLToggle && !wingsToggle) {
      LWING.set(false);
    }

    if ((wingsRKEY && !wingRButton)){
      wingRButton = true; 
      wingRToggle = !wingRToggle;
    }
    else if ((!wingsRKEY)) wingRButton = false; 

    if (wingRToggle){
      RWING.set(true);
    } else if (!wingRToggle && !wingsToggle) {
      RWING.set(false);
    }

    if (liftKEY && !liftButton){
      liftButton = true; 
      liftToggle = !liftToggle;
    }
    else if (!liftKEY) liftButton = false;

    if (liftToggle){
      LLIFT.set(true);
      RLIFT.set(true);
    } else {
      LLIFT.set(false);
      RLIFT.set(false);
    }

    //Replace this line with chassis.control_tank(); for tank drive 
    //or chassis.control_holonomic(); for holo drive.
    chassis.control_arcade();

    wait(20, msec); // Sleep the task for a short amount of time to
                    // prevent wasted resources.
  }
}

//
// Main will set up the competition functions and callbacks.
//
int main() {
  // Set up callbacks for autonomous and driver control periods.
  Competition.autonomous(autonomous);
  Competition.drivercontrol(usercontrol);

  // Run the pre-autonomous function.
  pre_auton();

  // Prevent main from exiting with an infinite loop.
  while (true) {
    wait(100, msec);
  }
}
