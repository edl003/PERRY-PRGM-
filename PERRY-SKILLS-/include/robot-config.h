using namespace vex;

extern brain Brain;

// VEXcode devices
extern motor L1;
extern motor L2;
extern motor L3;
extern motor L4;
extern motor R1;
extern motor R2;
extern motor R3;
extern motor R4;
extern inertial Inertial9;
extern controller Controller1;
extern motor_group CATA;
extern motor INTAKE;
extern motor CHAIN;
extern digital_out WINGS;
extern digital_out LIFT;
extern digital_out BLOCKER;

/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Pro.
 * 
 * This should be called at the start of your int main function.
 */
void  vexcodeInit( void );