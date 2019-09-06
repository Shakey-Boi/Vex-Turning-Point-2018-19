#include "robot-config.h"
using namespace vex;

//Note
//Instead of multiple functions for driving forward/back and right/left, these functions have a boolean operator for both directions

using namespace vex;

int   screen_origin_x = 150;
int   screen_origin_y = 20;
int   screen_width    = 316;
int   screen_height   = 212;

// kP variable for vision sensing and targeting
float kP = -.2;     // must be negative because that way it moves towards the flag and not away


int brightness = 50;

void TurnR(bool direction, int angle, int speed, bool brake, int brakeTime){

    //int left = 1;

    float GyroAngle = angle; //renaming vars

    //turns right if true and turn left if false
    if(direction == true){
        double targetGyroValue = Gyro.value(rotationUnits::deg) - GyroAngle;    //instead of reseting the gyroscope before each turn, just add the degrees to the
                                                                                //current value and moving towards that
        while(Gyro.value(rotationUnits::deg) > targetGyroValue){
            Brain.Screen.printAt(1,60, "%f target", GyroAngle); //print values for debugging purposes
            Brain.Screen.printAt(1,40,"%f degrees rn", Gyro.value(rotationUnits::deg)); //print values to compare both variables
            RightTransmission1.spin(directionType::rev, speed, velocityUnits::pct);
            RightTransmission2.spin(directionType::rev, speed, velocityUnits::pct);
            RightFront.spin(directionType::rev, speed, velocityUnits::pct);
            LeftTransmission1.spin(directionType::fwd, speed, velocityUnits::pct);
            LeftTransmission2.spin(directionType::fwd, speed, velocityUnits::pct);
            LeftFront.spin(directionType::fwd, speed, velocityUnits::pct);
            task::sleep(2); //refresh rate
        }
        if(brake == true){  // to counteract momentum
            RightFront.stop(brakeType::hold);
            RightTransmission1.stop(brakeType::hold);
            RightTransmission2.stop(brakeType::hold);
            LeftFront.stop(brakeType::hold);
            LeftTransmission1.stop(brakeType::hold);
            LeftTransmission2.stop(brakeType::hold);
            task::sleep(20);


        }
        if(brake == false){ //manual brake code
            RightTransmission1.spin(directionType::fwd, 20, velocityUnits::pct);
            RightTransmission2.spin(directionType::fwd, 20, velocityUnits::pct);
            RightFront.spin(directionType::fwd, 20, velocityUnits::pct);
            LeftTransmission1.spin(directionType::rev, 20, velocityUnits::pct);
            LeftTransmission2.spin(directionType::rev, 20, velocityUnits::pct);
            LeftFront.spin(directionType::rev, 20, velocityUnits::pct);
            task::sleep(brakeTime);     //user input time values
            RightFront.stop(brakeType::brake);
            RightTransmission1.stop(brakeType::brake);
            RightTransmission2.stop(brakeType::brake);
            LeftFront.stop(brakeType::brake);
            LeftTransmission1.stop(brakeType::brake);
            LeftTransmission2.stop(brakeType::brake);
            task::sleep(15);
        }

    }




        if(direction == false){
        double targetGyroValue = Gyro.value(rotationUnits::deg) + GyroAngle;
        while(Gyro.value(rotationUnits::deg) < targetGyroValue){
            Brain.Screen.printAt(1,60, "%f target", GyroAngle);
            Brain.Screen.printAt(1,40,"%f degrees rn", Gyro.value(rotationUnits::deg));
            RightTransmission1.spin(directionType::fwd, speed, velocityUnits::pct);
            RightTransmission2.spin(directionType::fwd, speed, velocityUnits::pct);
            RightFront.spin(directionType::fwd, speed, velocityUnits::pct);
            LeftTransmission1.spin(directionType::rev, speed, velocityUnits::pct);
            LeftTransmission2.spin(directionType::rev, speed, velocityUnits::pct);
            LeftFront.spin(directionType::rev, speed, velocityUnits::pct);
            task::sleep(2);
        }
        if(brake == true){
            RightFront.stop(brakeType::hold);
            RightTransmission1.stop(brakeType::hold);
            RightTransmission2.stop(brakeType::hold);
            LeftFront.stop(brakeType::hold);
            LeftTransmission1.stop(brakeType::hold);
            LeftTransmission2.stop(brakeType::hold);
            task::sleep(20);


        }
        if(brake == false){
            RightTransmission1.spin(directionType::rev, 10, velocityUnits::pct);
            RightTransmission2.spin(directionType::rev, 10, velocityUnits::pct);
            RightFront.spin(directionType::rev, 10, velocityUnits::pct);
            LeftTransmission1.spin(directionType::fwd, 10, velocityUnits::pct);
            LeftTransmission2.spin(directionType::fwd, 10, velocityUnits::pct);
            LeftFront.spin(directionType::fwd, 10, velocityUnits::pct);
            task::sleep(brakeTime);
            RightFront.stop(brakeType::brake);
            RightTransmission1.stop(brakeType::brake);
            RightTransmission2.stop(brakeType::brake);
            LeftFront.stop(brakeType::brake);
            LeftTransmission1.stop(brakeType::brake);
            LeftTransmission2.stop(brakeType::brake);
            task::sleep(15);
        }

    }


}

void strafeR(bool direction, int speed, float distance, bool brake){
    if(direction == true){  //strafes right if true
    LeftFront.resetRotation();  //reset values in encoders
    RightFront.resetRotation();
    float degrees = 0;
    degrees = 360*(distance/12.566);        //converts inches to degrees understood by the motors
        // left front wheel forward to go right
        //right back wheel goes forward
    while(LeftFront.rotation(rotationUnits::deg) < degrees){
        LeftFront.spin(directionType::fwd, speed, velocityUnits::pct);
        LeftTransmission1.spin(directionType::rev, speed, velocityUnits::pct);
        LeftTransmission2.spin(directionType::rev, speed, velocityUnits::pct);
        RightFront.spin(directionType::rev, speed, velocityUnits::pct);
        RightTransmission1.spin(directionType::fwd, speed, velocityUnits::pct);
        RightTransmission2.spin(directionType::fwd, speed, velocityUnits::pct);
    }
        if(brake == true){
            RightFront.stop(brakeType::hold);
            RightTransmission1.stop(brakeType::hold);
            RightTransmission2.stop(brakeType::hold);
            LeftFront.stop(brakeType::hold);
            LeftTransmission1.stop(brakeType::hold);
            LeftTransmission2.stop(brakeType::hold);
            task::sleep(20);
        }
    }



    if(direction == false){ //strafes left if false
    LeftFront.resetRotation();//reset encoder values
    RightFront.resetRotation();
    float degrees = 0;
    degrees = 360*(distance/12.566);
        // left front wheel forward to go right
        //right back wheel goes forward
    while(RightFront.rotation(rotationUnits::deg) < degrees){
        LeftFront.spin(directionType::rev, speed, velocityUnits::pct);
        LeftTransmission1.spin(directionType::fwd, speed, velocityUnits::pct);
        LeftTransmission2.spin(directionType::fwd, speed, velocityUnits::pct);
        RightFront.spin(directionType::fwd, speed, velocityUnits::pct);
        RightTransmission1.spin(directionType::rev, speed, velocityUnits::pct);
        RightTransmission2.spin(directionType::rev, speed, velocityUnits::pct);
    }
        if(brake == true){
            RightFront.stop(brakeType::hold);
            RightTransmission1.stop(brakeType::hold);
            RightTransmission2.stop(brakeType::hold);
            LeftFront.stop(brakeType::hold);
            LeftTransmission1.stop(brakeType::hold);
            LeftTransmission2.stop(brakeType::hold);
            task::sleep(20);
        }
    }


}


void driveF(bool direction, int speed, float distance, bool brake){
    if(direction == true){
    LeftFront.resetRotation();
    RightFront.resetRotation();
    float ticks = 0;
    float degrees = 360*(distance/12.566);
        // left front wheel forward to go right
        //right back wheel goes forward
    while(abs(RightFront.rotation(rotationUnits::deg)) < degrees || abs(LeftFront.rotation(rotationUnits::deg)) < degrees){
        LeftFront.spin(directionType::fwd, speed, velocityUnits::pct);
        LeftTransmission1.spin(directionType::fwd, speed, velocityUnits::pct);
        LeftTransmission2.spin(directionType::fwd, speed, velocityUnits::pct);
        RightFront.spin(directionType::fwd, speed, velocityUnits::pct);
        RightTransmission1.spin(directionType::fwd, speed, velocityUnits::pct);
        RightTransmission2.spin(directionType::fwd, speed, velocityUnits::pct);
    }
        if(brake == true){
            RightFront.stop(brakeType::hold);
            RightTransmission1.stop(brakeType::hold);
            RightTransmission2.stop(brakeType::hold);
            LeftFront.stop(brakeType::hold);
            LeftTransmission1.stop(brakeType::hold);
            LeftTransmission2.stop(brakeType::hold);
            task::sleep(10);
        }
    }





    if(direction == false){
    LeftFront.resetRotation();
    RightFront.resetRotation();
    float ticks = 0;
    float degrees = 360*(distance/12.566);
        // left front wheel forward to go right
        //right back wheel goes forward
    while(abs(RightFront.rotation(rotationUnits::deg)) < degrees || abs(LeftFront.rotation(rotationUnits::deg)) < degrees){
        LeftFront.spin(directionType::rev, speed, velocityUnits::pct);
        LeftTransmission1.spin(directionType::rev, speed, velocityUnits::pct);
        LeftTransmission2.spin(directionType::rev, speed, velocityUnits::pct);
        RightFront.spin(directionType::rev, speed, velocityUnits::pct);
        RightTransmission1.spin(directionType::rev, speed, velocityUnits::pct);
        RightTransmission2.spin(directionType::rev, speed, velocityUnits::pct);
    }
        if(brake == true){
            RightFront.stop(brakeType::hold);
            RightTransmission1.stop(brakeType::hold);
            RightTransmission2.stop(brakeType::hold);
            LeftFront.stop(brakeType::hold);
            LeftTransmission1.stop(brakeType::hold);
            LeftTransmission2.stop(brakeType::hold);
            task::sleep(10);
        }
    }
}






void driveF_Intake(bool direction, int speed, float distance, bool brake, bool intake_dir){
    if(direction == true){
    LeftFront.resetRotation();
    RightFront.resetRotation();
    float ticks = 0;
    float degrees = 360*(distance/12.566);
        // left front wheel forward to go right
        //right back wheel goes forward
        if(intake_dir == true){
                while(abs(RightFront.rotation(rotationUnits::deg)) < degrees || abs(LeftFront.rotation(rotationUnits::deg)) < degrees){
        LeftFront.spin(directionType::fwd, speed, velocityUnits::pct);
        LeftTransmission1.spin(directionType::fwd, speed, velocityUnits::pct);
        LeftTransmission2.spin(directionType::fwd, speed, velocityUnits::pct);
        RightFront.spin(directionType::fwd, speed, velocityUnits::pct);
        RightTransmission1.spin(directionType::fwd, speed, velocityUnits::pct);
        RightTransmission2.spin(directionType::fwd, speed, velocityUnits::pct);
        Intake.spin(directionType::fwd, 75, velocityUnits::pct);
    }
        if(brake == true){
            RightFront.stop(brakeType::hold);
            RightTransmission1.stop(brakeType::hold);
            RightTransmission2.stop(brakeType::hold);
            LeftFront.stop(brakeType::hold);
            LeftTransmission1.stop(brakeType::hold);
            LeftTransmission2.stop(brakeType::hold);
            Intake.stop(brakeType::coast);
            task::sleep(10);
        }
        }

        if(intake_dir == false){
                while(abs(RightFront.rotation(rotationUnits::deg)) < degrees || abs(LeftFront.rotation(rotationUnits::deg)) < degrees){
        LeftFront.spin(directionType::fwd, speed, velocityUnits::pct);
        LeftTransmission1.spin(directionType::fwd, speed, velocityUnits::pct);
        LeftTransmission2.spin(directionType::fwd, speed, velocityUnits::pct);
        RightFront.spin(directionType::fwd, speed, velocityUnits::pct);
        RightTransmission1.spin(directionType::fwd, speed, velocityUnits::pct);
        RightTransmission2.spin(directionType::fwd, speed, velocityUnits::pct);
        Intake.spin(directionType::rev, 75, velocityUnits::pct);
    }
        if(brake == true){
            RightFront.stop(brakeType::hold);
            RightTransmission1.stop(brakeType::hold);
            RightTransmission2.stop(brakeType::hold);
            LeftFront.stop(brakeType::hold);
            LeftTransmission1.stop(brakeType::hold);
            LeftTransmission2.stop(brakeType::hold);
            Intake.stop(brakeType::coast);
            task::sleep(10);
        }
        }
    }


 //////////////////////////////////////////


    if(direction == false){
    LeftFront.resetRotation();
    RightFront.resetRotation();
    float ticks = 0;
    float degrees = 360*(distance/12.566);
        // left front wheel forward to go right
        //right back wheel goes forward
    while(abs(RightFront.rotation(rotationUnits::deg)) < degrees || abs(LeftFront.rotation(rotationUnits::deg)) < degrees){
        LeftFront.spin(directionType::rev, speed, velocityUnits::pct);
        LeftTransmission1.spin(directionType::rev, speed, velocityUnits::pct);
        LeftTransmission2.spin(directionType::rev, speed, velocityUnits::pct);
        RightFront.spin(directionType::rev, speed, velocityUnits::pct);
        RightTransmission1.spin(directionType::rev, speed, velocityUnits::pct);
        RightTransmission2.spin(directionType::rev, speed, velocityUnits::pct);
    }
        if(brake == true){
            RightFront.stop(brakeType::hold);
            RightTransmission1.stop(brakeType::hold);
            RightTransmission2.stop(brakeType::hold);
            LeftFront.stop(brakeType::hold);
            LeftTransmission1.stop(brakeType::hold);
            LeftTransmission2.stop(brakeType::hold);
            task::sleep(10);
        }
    }
}

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
    VisionSensor.setSignature(SIG_1);

    //finding the middle of sensor to accurately line up with it
    int screen_middle_x = screen_width / 2;
    bool linedup = false;

    // variable for a p loop
    float error;
    float final_power;




    while(not(linedup)){        // quite literally while not lined up

        VisionSensor.takeSnapshot(SIG_1);
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
        //red auton
        // double shot, 1 flag, 2 caps, and park
        // time is issue so do some of the following
        //  -reduce time inbetween
        //  -increase power at the risk of inaccuracy
        //  -cut out bottom flag and go straight to caps or vica versa
        // 5.2 seconds of pause
  //      task::sleep(1500);  //  Gyro initialization
        driveF_Intake(true, 75, 36, true, true);
        task::sleep(150);
        Intake.spin(directionType::fwd, 75, velocityUnits::pct);
        task::sleep(200);
        Intake.stop(brakeType::coast);
        driveF(false,75, 36, true);
        task::sleep(150);



        TurnR(false, 90, 75, true, 90);
        task::sleep(100);
        driveF(true, 75, 12, true);
        task::sleep(100);

        TurnR(true, 90, 75, true, 90);
        task::sleep(100);
        driveF_Intake(true, 75, 36, true, false);

    //      task::sleep(150);
    //    strafeR(false, 80, 8, true);
      //  task::sleep(150);
     //   Puncher.spin(directionType::fwd, 100, velocityUnits::pct);
     //   task::sleep(1500);
     /*   driveF(false, 80, 30, true);
        task::sleep(150);
        driveF(true, 80, 6, true);
        task::sleep(150);
        TurnR(true, 90, 75, true, 140);
        task::sleep(150);
        driveF_Intake(true, 80, 12, true, false);
        task::sleep(150);
        strafeR(true, 90, 30, true);
        task::sleep(150);
        driveF(true, 100, 20, true);
        task::sleep(150);
      */



}
