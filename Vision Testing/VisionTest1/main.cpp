using namespace vex;
#include "robot-config.h"

int   screen_origin_x = 150;
int   screen_origin_y = 20;
int   screen_width    = 316;
int   screen_height   = 212;
float kP = .15;
void targeting(){
    VisionSensor.setLedBrightness(50);
    VisionSensor.setSignature(SIG_2);

    int screen_middle_x = screen_width / 2;
    bool linedup = false;

    //take it slow maybe before loop?


    while(not(linedup)){

        VisionSensor.takeSnapshot(SIG_2);

        if(VisionSensor.objectCount > 0){
            if(VisionSensor.largestObject.centerX > screen_middle_x - 5){
                LeftFront.spin(directionType::rev, 7, velocityUnits::pct);
                LeftTransmission1.spin(directionType::rev, 7, velocityUnits::pct);
                LeftTransmission2.spin(directionType::rev, 7, velocityUnits::pct);
                RightFront.spin(directionType::fwd, 7, velocityUnits::pct);
                RightTransmission1.spin(directionType::fwd, 7, velocityUnits::pct);
                RightTransmission2.spin(directionType::fwd, 7, velocityUnits::pct);
            }

            else if(VisionSensor.largestObject.centerX < screen_middle_x + 5){
                LeftFront.spin(directionType::fwd, 7, velocityUnits::pct);
                LeftTransmission1.spin(directionType::fwd, 7, velocityUnits::pct);
                LeftTransmission2.spin(directionType::fwd, 7, velocityUnits::pct);
                RightFront.spin(directionType::rev, 7, velocityUnits::pct);
                RightTransmission1.spin(directionType::rev, 7, velocityUnits::pct);
                RightTransmission2.spin(directionType::rev, 7, velocityUnits::pct);
            }


            else{
                linedup = true;
                RightTransmission1.stop(brakeType::coast);
                RightTransmission2.stop(brakeType::coast);
                RightFront.stop(brakeType::coast);
                LeftTransmission1.stop(brakeType::coast);
                LeftTransmission2.stop(brakeType::coast);
                LeftFront.stop(brakeType::coast);
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
    while(true){
        if(ControllerMain.ButtonB.pressing()){
            targeting();
            task::sleep(.5);
        }
             RightTransmission1.stop(brakeType::coast);
             RightTransmission2.stop(brakeType::coast);
             RightFront.stop(brakeType::coast);
             LeftTransmission1.stop(brakeType::coast);
             LeftTransmission2.stop(brakeType::coast);
             LeftFront.stop(brakeType::coast);
    }
}
