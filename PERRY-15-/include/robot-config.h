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
extern inertial Inertial;
extern controller Controller1;
extern motor INTAKE;
extern motor CHAIN;
extern digital_out LWING;
extern digital_out RWING;
extern digital_out LLIFT;
extern digital_out RLIFT;
extern motor_group CATA;
extern digital_out CLIMB1;
extern digital_out CLIMB2;

/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Pro.
 * 
 * This should be called at the start of your int main function.
 */
void  vexcodeInit( void );