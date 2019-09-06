using namespace vex;
#include "robot-config.h"

int   screen_origin_x = 150;
int   screen_origin_y = 20;
int   screen_width    = 316;
int   screen_height   = 212;
float kP = -.2;
int brightness;

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

void targeting(){
    VisionSensor.setLedBrightness(brightness);
    VisionSensor.setSignature(SIG_2);

    int screen_middle_x = screen_width / 2;
    bool linedup = false;

    float error;
    float final_power;
    while(not(linedup)){

        VisionSensor.takeSnapshot(SIG_2);
        error = (VisionSensor.largestObject.centerX - screen_middle_x);

        if(VisionSensor.objectCount > 0){
            if(VisionSensor.largestObject.centerX > 0 or VisionSensor.largestObject.centerX < 0 ){

                final_power = error * kP;
                LeftFront.spin(directionType::fwd, final_power, velocityUnits::pct);
                LeftTransmission1.spin(directionType::fwd, final_power, velocityUnits::pct);
                LeftTransmission2.spin(directionType::fwd, final_power, velocityUnits::pct);
                RightFront.spin(directionType::rev, final_power, velocityUnits::pct);
                RightTransmission1.spin(directionType::rev, final_power, velocityUnits::pct);
                RightTransmission2.spin(directionType::rev, final_power, velocityUnits::pct);
            }
            else if(VisionSensor.largestObject.centerX == 0 or error == 0 or error == -1 or error == 1){
                ControllerMain.rumble(".-");
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


        else{
             RightTransmission1.stop(brakeType::coast);
             RightTransmission2.stop(brakeType::coast);
             RightFront.stop(brakeType::coast);
             LeftTransmission1.stop(brakeType::coast);
             LeftTransmission2.stop(brakeType::coast);
             LeftFront.stop(brakeType::coast);
        }

    }


}
int main() {
    task::sleep(1000);
    brightness_setup();
    task::sleep(500);
    Brain.Screen.printAt(1,80, "Brightness: %f", brightness);
while(true){
    if(ControllerMain.ButtonB.pressing()){
        targeting();
        task::sleep(10);
    }

    else{
             RightTransmission1.stop(brakeType::coast);
             RightTransmission2.stop(brakeType::coast);
             RightFront.stop(brakeType::coast);
             LeftTransmission1.stop(brakeType::coast);
             LeftTransmission2.stop(brakeType::coast);
             LeftFront.stop(brakeType::coast);
    }
}
}
