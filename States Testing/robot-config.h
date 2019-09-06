using namespace vex;

/*
motor RightTransmission1 = motor(PORT1);
motor RightFront = motor(PORT2);
motor RightTransmission2 = motor(PORT3, true);
motor LeftTransmission1 = motor(PORT4);
motor LeftFront = motor(PORT5, true);
motor LeftTransmission2 = motor(PORT6, true);
motor Intake = motor(PORT7);
motor Puncher = motor(PORT8);
brain Brain;
gyro Gyro = gyro(Brain.ThreeWirePort.A);
controller ControllerMain = controller();
vision VisionSensor(PORT10);
vision::signature SIG_1 (1, 0, 0, 0, 0, 0, 0, 2.5, 0);
*/

brain Brain;
encoder Encoder = encoder(Brain.ThreeWirePort.C);
pot BrightnessPot = pot(Brain.ThreeWirePort.B);
motor RightTransmission1 = motor(PORT1);
motor RightFront = motor(PORT2);
motor RightTransmission2 = motor(PORT3, true);
motor LeftTransmission1 = motor(PORT4, true);
motor LeftFront = motor(PORT5, true);
motor LeftTransmission2 = motor(PORT6);
motor Intake = motor(PORT7);
motor Puncher = motor(PORT8);
gyro Gyro = gyro(Brain.ThreeWirePort.A);
controller ControllerMain = controller();
vision::signature SIG_1 (1,101,3217,1659,-4681,-3869,-4275,2.3,0);
vision::signature SIG_2 (2, -3985, -2081, -3033, -4629, 14141, 4756, 1.2, 0);
vision::signature SIG_3 (3, -4323, -1093, -2708, -2713, 12435, 4861, 1.1, 0);
vision::signature SIG_4 (4, 0, 0, 0, 0, 0, 0, 3, 0);
vision::signature SIG_5 (5, 0, 0, 0, 0, 0, 0, 3, 0);
vision::signature SIG_6 (6, 0, 0, 0, 0, 0, 0, 3, 0);
vision::signature SIG_7 (7, 0, 0, 0, 0, 0, 0, 3, 0);
vision VisionSensor (PORT11, 75, SIG_1, SIG_2, SIG_3, SIG_4, SIG_5, SIG_6, SIG_7);
