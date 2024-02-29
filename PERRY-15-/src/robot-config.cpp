#include "vex.h"

using namespace vex;
using signature = vision::signature;
using code = vision::code;

// A global instance of brain used for printing to the V5 Brain screen
brain  Brain;

// VEXcode device constructors
motor L1 = motor(PORT8, ratio6_1, true);
motor L2 = motor(PORT7, ratio6_1, true);
motor L3 = motor(PORT6, ratio6_1, false);
motor L4 = motor(PORT5, ratio6_1, false);
motor R1 = motor(PORT1, ratio6_1, false);
motor R2 = motor(PORT2, ratio6_1, false);
motor R3 = motor(PORT3, ratio6_1, true);
motor R4 = motor(PORT4, ratio6_1, true);
inertial Inertial = inertial(PORT16);
controller Controller1 = controller(primary);
motor INTAKE = motor(PORT19, ratio18_1, false);
motor CHAIN = motor(PORT15, ratio18_1, false);
digital_out LWING = digital_out(Brain.ThreeWirePort.H);
digital_out RWING = digital_out(Brain.ThreeWirePort.G);
digital_out LLIFT = digital_out(Brain.ThreeWirePort.F);
digital_out RLIFT = digital_out(Brain.ThreeWirePort.E);
limit LIMIT = limit(Brain.ThreeWirePort.D);
motor CATAMotorA = motor(PORT13, ratio36_1, true);
motor CATAMotorB = motor(PORT14, ratio36_1, false);
motor_group CATA = motor_group(CATAMotorA, CATAMotorB);

// VEXcode generated functions
// define variable for remote controller enable/disable
bool RemoteControlCodeEnabled = true;

/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Pro.
 * 
 * This should be called at the start of your int main function.
 */
void vexcodeInit( void ) {
  // nothing to initialize
}