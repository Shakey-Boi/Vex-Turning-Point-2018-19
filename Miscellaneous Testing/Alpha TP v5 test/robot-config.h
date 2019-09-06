using namespace vex;

//alpha testing
brain Brain;
motor LeftMotor = motor(PORT1);
motor LeftMotor2 = motor(PORT2);
motor LeftMotor3 = motor(PORT3);
motor RightMotor = motor(PORT4, true);
motor RightMotor2 = motor(PORT5, true);
motor RightMotor3 = motor(PORT6, true);
motor ArmMotor = motor(PORT10);
motor ClawMotor = motor(PORT13);
motor Puncher1 = motor(PORT7, true);
motor Puncher2 = motor(PORT8);
controller ControllerMain = controller();       
