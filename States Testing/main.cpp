#include "robot-config.h"
using namespace vex;

//Vision sensing problems
//brightness calibration
//maybe take a pot for brightness calibration


//specifying vision sensor specs
int   screen_origin_x = 150;
int   screen_origin_y = 20;
int   screen_width    = 316;
int   screen_height   = 212;

// kP variable for vision sensing and targeting
float kP = -.2;     // must be negative because that way it moves towards the flag and not away

int brightness;



void windup(float degrees, float target){
    Encoder.setRotation(-50, rotationUnits::deg);

    while(Encoder.rotation(rotationUnits::deg) < 0){
        Puncher.spin(directionType::fwd,100,velocityUnits::pct);
    }
    while(Encoder.rotation(rotationUnits::deg) >= 0 || Encoder.rotation(rotationUnits::deg) < target){
        Puncher.spin(directionType::fwd, 100, velocityUnits::pct);
    //    Brain.Screen.print("Puncher: %f" Encoder.rotation(rotationUnits::deg));
    }

}

void shoot(int time){
    Puncher.spin(directionType::fwd,100, velocityUnits::pct);
    task::sleep(time);
}

void angler(){
    Puncher.spin(directionType::rev, 100, velocityUnits::pct);
    task::sleep(2000);
}

void brightness_setup(){
    if(BrightnessPot.value(analogUnits::range8bit) > 0 || BrightnessPot.value(analogUnits::range8bit) < 36.5){
        brightness = 0;
     }
    else if(BrightnessPot.value(analogUnits::range8bit) > 36.5 || BrightnessPot.value(analogUnits::range8bit) < 73){
        brightness = 25;
    }
    else if(BrightnessPot.value(analogUnits::range8bit) > 73 || BrightnessPot.value(analogUnits::range8bit) < 109.5){
        brightness = 50;
    }
    else if(BrightnessPot.value(analogUnits::range8bit) > 109.5 || BrightnessPot.value(analogUnits::range8bit) < 146){
        brightness = 75;
    }
    else if(BrightnessPot.value(analogUnits::range8bit) > 146 || BrightnessPot.value(analogUnits::range8bit) < 182.5){
        brightness = 100;
    }
    else if(BrightnessPot.value(analogUnits::range8bit) > 182.5 || BrightnessPot.value(analogUnits::range8bit) < 219){
        brightness = 125;
    }
    else if(BrightnessPot.value(analogUnits::range8bit) > 219 || BrightnessPot.value(analogUnits::range8bit) < 256){
        brightness = 150;
    }
    else{
        brightness = 50;
    }
}

// this void is the function for the vision sensor targeting, It utilizes a p loop to make sure the farther away the robot is from the signature, the more power it exerts
// and the closer it gets to the target, it slows down
void targeting(float time){
    float final_time = time * 1000;     //converting user seconds to milisecond
    Brain.resetTimer();                 //reset the timer

    //vision sensor calibration (setting brightness and signature)
    VisionSensor.setLedBrightness(50);
    VisionSensor.setSignature(SIG_2);

    //finding the middle of sensor to accurately line up with it
    int screen_middle_x = screen_width / 2;
    bool linedup = false;

    // variable for a p loop
    float error;
    float final_power;




    while(not(linedup)){        // quite literally while not lined up

        VisionSensor.takeSnapshot(SIG_2);
        error = (VisionSensor.largestObject.centerX - screen_middle_x); //finds the error by subtracting the value of the x coordinate minus the target value

        if(VisionSensor.objectCount > 0){   //runs if the number of signatures are greater than 0
            if(VisionSensor.largestObject.centerX > 0 or VisionSensor.largestObject.centerX < 0 ){  // if the center of the signature is not centered

                final_power = error * kP;           // error times the kP factor to determine the motor power
                LeftFront.spin(directionType::fwd, final_power, velocityUnits::pct);            //final power is the motor power for all the drive
                LeftTransmission1.spin(directionType::fwd, final_power, velocityUnits::pct);
                LeftTransmission2.spin(directionType::fwd, final_power, velocityUnits::pct);
                RightFront.spin(directionType::rev, final_power, velocityUnits::pct);
                RightTransmission1.spin(directionType::rev, final_power, velocityUnits::pct);
                RightTransmission2.spin(directionType::rev, final_power, velocityUnits::pct);
                if(Brain.Timer.time() > final_time){
                    linedup = true;
                }
            }
            else if(VisionSensor.largestObject.centerX == 0 or error == 0 or error == -1 or error == 1){
                ControllerMain.rumble("."); //gives user feedback
                linedup = true;
                RightTransmission1.stop(brakeType::hold);
                RightTransmission2.stop(brakeType::hold);
                RightFront.stop(brakeType::hold);
                LeftTransmission1.stop(brakeType::hold);
                LeftTransmission2.stop(brakeType::hold);
                LeftFront.stop(brakeType::hold);
            }
            else{
                linedup = true;
                RightTransmission1.stop(brakeType::hold);
                RightTransmission2.stop(brakeType::hold);
                RightFront.stop(brakeType::hold);
                LeftTransmission1.stop(brakeType::hold);
                LeftTransmission2.stop(brakeType::hold);
                LeftFront.stop(brakeType::hold);
            }
        }


        else{   // this is the else for if no signatures are recognized
            linedup = true;
             RightTransmission1.stop(brakeType::coast);
             RightTransmission2.stop(brakeType::coast);
             RightFront.stop(brakeType::coast);
             LeftTransmission1.stop(brakeType::coast);
             LeftTransmission2.stop(brakeType::coast);
             LeftFront.stop(brakeType::coast);
        }

     }



}






//void for the robot to drive forward (version one)
void drive_forward(int speed, float distance, bool brake){
    LeftFront.resetRotation();
    RightFront.resetRotation();

    float ticks = 0;

    ticks = 360*(distance/12.566);

    float left_value = LeftFront.rotation(rotationUnits::deg);
    float right_value = RightFront.rotation(rotationUnits::deg);


    while((left_value < ticks) and (right_value < ticks)){
        RightFront.spin(directionType::fwd, speed,  velocityUnits::pct);
        RightTransmission1.spin(directionType::fwd, speed, velocityUnits::pct);
        RightTransmission2.spin(directionType::fwd, speed, velocityUnits::pct);
        LeftFront.spin(directionType::fwd, speed,  velocityUnits::pct);
        LeftTransmission1.spin(directionType::fwd, speed, velocityUnits::pct);
        LeftTransmission2.spin(directionType::fwd, speed, velocityUnits::pct);
    }
    if(brake == true){
        RightFront.stop(brakeType::hold);
        RightTransmission1.stop(brakeType::hold);
        RightTransmission2.stop(brakeType::hold);
        LeftFront.stop(brakeType::hold);
        LeftTransmission1.stop(brakeType::hold);
        LeftTransmission2.stop(brakeType::hold);
    }
    else{
        RightFront.stop(brakeType::hold);
        RightTransmission1.stop(brakeType::hold);
        RightTransmission2.stop(brakeType::hold);
        LeftFront.stop(brakeType::hold);
        LeftTransmission1.stop(brakeType::hold);
        LeftTransmission2.stop(brakeType::hold);
    }

}


//version to drive forward (version 2)
void rotate_forward(int speed, float distance, bool brake){
    LeftFront.resetRotation();
    RightFront.resetRotation();

    float ticks = 0;

    ticks = 360*(distance/12.566);

    float left_value = LeftFront.rotation(rotationUnits::deg);
    float right_value = RightFront.rotation(rotationUnits::deg);

    RightFront.rotateTo(right_value, rotationUnits::deg, speed);
    LeftFront.rotateTo(left_value, rotationUnits::deg, speed);


    if(brake == true){
        RightFront.stop(brakeType::hold);
        RightTransmission1.stop(brakeType::hold);
        RightTransmission2.stop(brakeType::hold);
        LeftFront.stop(brakeType::hold);
        LeftTransmission1.stop(brakeType::hold);
        LeftTransmission2.stop(brakeType::hold);
    }
    else{
        RightFront.stop(brakeType::brake);
        RightTransmission1.stop(brakeType::brake);
        RightTransmission2.stop(brakeType::brake);
        LeftFront.stop(brakeType::brake);
        LeftTransmission1.stop(brakeType::brake);
        LeftTransmission2.stop(brakeType::brake);
    }

}
/*
void target(){
    VisionSensor.takeSnapshot(SIG_1);
    if(VisionSensor.largestObject. < 0){
        RightFront.spin(directionType::fwd, 10,  velocityUnits::pct);
        RightTransmission1.spin(directionType::fwd, 10, velocityUnits::pct);
        RightTransmission2.spin(directionType::fwd, 10, velocityUnits::pct);
        LeftFront.spin(directionType::rev, 10,  velocityUnits::pct);
        LeftTransmission1.spin(directionType::rev, 10, velocityUnits::pct);
        LeftTransmission2.spin(directionType::rev, 10, velocityUnits::pct);
    }
    else{
   // ControllerMain.rumble('.-');

    }
}*/









void ram(float degrees){
        LeftTransmission1.resetRotation();
        while(LeftTransmission1.rotation(rotationUnits::deg) < degrees){
        LeftTransmission1.spin(directionType::fwd, 75, velocityUnits::pct);     // for cap flipper down
        LeftTransmission2.spin(directionType::rev, 75, velocityUnits::pct);
        }
}











void gyro_print(){

    Brain.Screen.printAt(1,40, "%f degrees", Gyro.value(rotationUnits::deg));
    task::sleep(5);

}




int main() {
task::sleep(1500);  //calibration for gyroscope
brightness_setup();
task::sleep(500);
while(true){
    Brain.Screen.printAt(1,80, "Brightness: %f", brightness);
    Brain.Screen.printAt(1, 60, "%d seconds", Brain.Timer.time());                  //prints values of the timer for debugging
    Brain.Screen.printAt(1,40, "%f degrees", Gyro.value(rotationUnits::deg));       //prints values of the gyro for debugging
    Brain.Screen.printAt(1,100, "%f Puncher degrees", Encoder.rotation(rotationUnits::deg));
    task::sleep(5); //controls refresh rate

if(ControllerMain.ButtonLeft.pressing()){
    targeting(2.5); //whenever the right scuff is toggled the robot utilizes it vision sensor to aim for 2.5 seconds
}

int X2 = 0, Y1 = 0, X1 = 0;                 // defining all the direction variables
int threshold = 10;                         // deadzone value for the controller

//////////////////////////////////////////////////////////////////
    //Deadzone for Y1/Axis 3                                    //
    if(abs(ControllerMain.Axis3.value()) > threshold){          //
        Y1= ControllerMain.Axis3.value();                       //
    }                                                           //
                                                                //
    //Deadzone for X1/Axis 4                                    //
    if(abs(ControllerMain.Axis4.value()) > threshold){          //  This block is equivalent to
        X1 = ControllerMain.Axis4.value();                      //  "If the absolute value of the ___ Axis of the controller
    }                                                           //   is greater than the threshold value I defined earlier,
                                                                //   then set the value of the controller at that time to be __ (Direction Variable)"
    //Deadzone for X2/Ch1                                       //   Uses a decimal in X2 to control turning speed
    if(abs(ControllerMain.Axis1.value()) > threshold){          //
        X2 = -.8*ControllerMain.Axis1.value();                  //
    }                                                           //
//////////////////////////////////////////////////////////////////

    if(ControllerMain.ButtonL2.pressing()){
        RightTransmission1.spin(directionType::rev, 100, velocityUnits::pct);   //for the descorer down
        RightTransmission2.spin(directionType::fwd, 100, velocityUnits::pct);
        //RightTransmission1.stop(brakeType::brake);
        //RightTransmission2.stop(brakeType::brake);

    }

    else if(ControllerMain.ButtonL1.pressing()){
        RightTransmission1.spin(directionType::fwd, 100, velocityUnits::pct);   //for descorer up
        RightTransmission2.spin(directionType::rev, 100, velocityUnits::pct);
        //RightTransmission1.stop(brakeType::brake);
        //RightTransmission2.stop(brakeType::brake);
    }
    else if(ControllerMain.ButtonR1.pressing()){
        LeftTransmission1.spin(directionType::rev, 100, velocityUnits::pct);    //for cap flipper up
        LeftTransmission2.spin(directionType::fwd, 100, velocityUnits::pct);
        //LeftTransmission1.stop(brakeType::brake);
        //LeftTransmission2.stop(brakeType::brake);
    }
    else if(ControllerMain.ButtonR2.pressing()){
        LeftTransmission1.spin(directionType::fwd, 75, velocityUnits::pct);     // for cap flipper down
        LeftTransmission2.spin(directionType::rev, 75, velocityUnits::pct);
        //LeftTransmission1.stop(brakeType::brake);
        //LeftTransmission2.stop(brakeType::brake);
    }




    else if((ControllerMain.ButtonL2.pressing()) and (abs(ControllerMain.Axis1.value()) > threshold)){
        RightTransmission1.spin(directionType::rev, 100, velocityUnits::pct);
        RightTransmission2.stop(brakeType::hold);
    }
    else if((ControllerMain.ButtonL2.pressing()) and (abs(ControllerMain.Axis2.value()) > threshold)){
        RightTransmission1.spin(directionType::rev, 100, velocityUnits::pct);
        RightTransmission2.stop(brakeType::hold);
    }
    else if((ControllerMain.ButtonL2.pressing()) and (abs(ControllerMain.Axis4.value()) > threshold)){
        RightTransmission1.spin(directionType::rev, 100, velocityUnits::pct);
        RightTransmission2.stop(brakeType::hold);
    }




    else if((ControllerMain.ButtonL1.pressing()) and (abs(ControllerMain.Axis1.value()) > threshold)){
        RightTransmission1.spin(directionType::fwd, 100, velocityUnits::pct);
        RightTransmission2.stop(brakeType::hold);
    }
    else if((ControllerMain.ButtonL1.pressing()) and (abs(ControllerMain.Axis2.value()) > threshold)){
        RightTransmission1.spin(directionType::fwd, 100, velocityUnits::pct);
        RightTransmission2.stop(brakeType::hold);
    }
    else if((ControllerMain.ButtonL1.pressing()) and (abs(ControllerMain.Axis4.value()) > threshold)){
        RightTransmission1.spin(directionType::fwd, 100, velocityUnits::pct);
        RightTransmission2.stop(brakeType::hold);
    }





    else if((ControllerMain.ButtonR2.pressing()) and (abs(ControllerMain.Axis1.value()) > threshold)){
        LeftTransmission2.spin(directionType::rev, 90, velocityUnits::pct);
        LeftTransmission1.stop(brakeType::hold);
    }
    else if((ControllerMain.ButtonR2.pressing()) and (abs(ControllerMain.Axis2.value()) > threshold)){
        LeftTransmission2.spin(directionType::rev, 90, velocityUnits::pct);
        LeftTransmission1.stop(brakeType::hold);
    }
    else if((ControllerMain.ButtonR2.pressing()) and (abs(ControllerMain.Axis4.value()) > threshold)){
        LeftTransmission2.spin(directionType::rev, 90, velocityUnits::pct);
        LeftTransmission1.stop(brakeType::hold);
    }




    else if((ControllerMain.ButtonR1.pressing()) and (abs(ControllerMain.Axis1.value()) > threshold)){
        LeftTransmission2.spin(directionType::fwd, 90, velocityUnits::pct);
        LeftTransmission1.stop(brakeType::hold);
    }
    else if((ControllerMain.ButtonR1.pressing()) and (abs(ControllerMain.Axis2.value()) > threshold)){
        LeftTransmission2.spin(directionType::fwd, 90, velocityUnits::pct);
        LeftTransmission1.stop(brakeType::hold);
    }
    else if((ControllerMain.ButtonR1.pressing()) and (abs(ControllerMain.Axis4.value()) > threshold)){
        LeftTransmission2.spin(directionType::fwd, 90, velocityUnits::pct);
        LeftTransmission1.stop(brakeType::hold);
    }



    else{
    // not so fancy math that equates the final value to certain directions || inverse the signs of the equation if you want to reverse something here
    RightTransmission1.spin(directionType::fwd, Y1-X2+X1, velocityUnits::pct);      //split arcade drive w mecanum
    RightTransmission2.spin(directionType::fwd, Y1-X2+X1, velocityUnits::pct);
    RightFront.spin(directionType::fwd, Y1-X2-X1, velocityUnits::pct);
    LeftTransmission1.spin(directionType::fwd, Y1+X2-X1, velocityUnits::pct);
    LeftTransmission2.spin(directionType::fwd, Y1+X2-X1, velocityUnits::pct);
    LeftFront.spin(directionType::fwd, Y1+X2+X1, velocityUnits::pct);

    }


    if(ControllerMain.ButtonDown.pressing()){
        Intake.spin(directionType::fwd, 75, velocityUnits::pct);    //intake running at 75 for testing
    }
    else if(ControllerMain.ButtonB.pressing()){
        Intake.spin(directionType::rev, 75, velocityUnits::pct);
    }
    else{
        Intake.stop(brakeType::coast);                              // coast rather than brake
    }

    if(ControllerMain.ButtonA.pressing()){
        Puncher.spin(directionType::fwd ,100, velocityUnits::pct);

    }
    else if(ControllerMain.ButtonRight.pressing()){
        Puncher.spin(directionType::rev, 60, velocityUnits::pct);
    }

    else if(ControllerMain.ButtonY.pressing()){
        shoot(250);
    }
    else if(ControllerMain.ButtonUp.pressing()){
        Puncher.spin(directionType::fwd, 100, velocityUnits::pct);
        task::sleep(3100);
    }
    else{
        Puncher.stop(brakeType::hold);
    }

}//end while

}// end task
