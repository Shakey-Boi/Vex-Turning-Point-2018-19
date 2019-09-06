using namespace vex;
#include "robot-config.h"


void RightDriveForward(int speed){
    RightTransmission1.spin(directionType::fwd, speed, velocityUnits::pct);
    RightTransmission2.spin(directionType::fwd, speed, velocityUnits::pct);
    RightFront.spin(directionType::fwd, speed, velocityUnits::pct);
}

void RightDriveBack(int speed){
    RightTransmission1.spin(directionType::rev, speed, velocityUnits::pct);
    RightTransmission2.spin(directionType::rev, speed, velocityUnits::pct);
    RightFront.spin(directionType::rev, speed, velocityUnits::pct);
}

void LeftDriveForward(int speed){
    LeftTransmission1.spin(directionType::fwd, speed, velocityUnits::pct);
    LeftTransmission2.spin(directionType::fwd, speed, velocityUnits::pct);
    LeftFront.spin(directionType::fwd, speed, velocityUnits::pct);
}

void LeftDriveBack(int speed){
    LeftTransmission1.spin(directionType::rev, speed, velocityUnits::pct);
    LeftTransmission2.spin(directionType::rev, speed, velocityUnits::pct);
    LeftFront.spin(directionType::rev, speed, velocityUnits::pct);
}

void flip_up(int speed){
    LeftTransmission1.spin(directionType::fwd, speed, velocityUnits::pct);
    LeftTransmission2.spin(directionType::rev, speed, velocityUnits::pct);
}


void flip_down(int speed){
    LeftTransmission1.spin(directionType::rev, speed, velocityUnits::pct);
    LeftTransmission2.spin(directionType::fwd, speed, velocityUnits::pct);
}

void roller_in(int power){
    Intake.spin(directionType::fwd, power, velocityUnits::pct);
}

void roller_out(int power){
    Intake.spin(directionType::rev, power, velocityUnits::pct);
}

void drive_forward(int speed, float distance, bool brake){
    LeftFront.resetRotation();
    RightFront.resetRotation();

    float ticks = 0;

    ticks = 360*(distance/12.566);


    while(abs(LeftFront.rotation(rotationUnits::deg)) < ticks || abs(RightFront.rotation(rotationUnits::deg)) < ticks){
        RightDriveForward(speed);
        LeftDriveForward(speed);
    }

    if (true){
        RightDriveBack(30);
        LeftDriveBack(30);
        task::sleep(30);
        RightDriveForward(0);
        LeftDriveForward(0);
    }
}



void drive_forward_intake(int speed, float distance, bool brake, int intake_speed){
    LeftFront.resetRotation();
    RightFront.resetRotation();

    float ticks = 0;

    ticks = 360*(distance/12.566);


    while(abs(LeftFront.rotation(rotationUnits::deg)) < ticks || abs(RightFront.rotation(rotationUnits::deg)) < ticks){
        RightDriveForward(speed);
        LeftDriveForward(speed);
        roller_in(intake_speed);
    }

    if (true){
        RightDriveBack(30);
        LeftDriveBack(30);
        roller_in(0);
        task::sleep(30);
        RightDriveForward(0);
        LeftDriveForward(0);
        roller_in(0);
    }
}


void drive_back(int speed, float distance, bool brake){
    LeftFront.resetRotation();
    RightFront.resetRotation();

    float ticks = 0;

    ticks = 360*(distance/12.566);


    while(abs(LeftFront.rotation(rotationUnits::deg)) < ticks || abs(RightFront.rotation(rotationUnits::deg)) < ticks){
        RightDriveBack(speed);
        LeftDriveBack(speed);
    }

    if (true){
        RightDriveForward(30);
        LeftDriveForward(30);
        task::sleep(30);
        RightDriveBack(0);
        LeftDriveBack(0);
    }
}



void turn_right(int speed, float distance, bool brake){
    LeftFront.resetRotation();
    RightFront.resetRotation();

    float ticks = 0;

    ticks = 360*(distance/12.566);


    while(abs(LeftFront.rotation(rotationUnits::deg)) < ticks || abs(RightFront.rotation(rotationUnits::deg)) < ticks){
        RightDriveBack(speed);
        LeftDriveForward(speed);
    }

    if (true){
        RightDriveForward(30);
        LeftDriveBack(30);
        task::sleep(30);
        RightDriveBack(0);
        LeftDriveForward(0);
    }
}


void turn_left(int speed, float distance, bool brake){
    LeftFront.resetRotation();
    RightFront.resetRotation();

    float ticks = 0;

    ticks = 360*(distance/12.566);


    while(abs(LeftFront.rotation(rotationUnits::deg)) < ticks || abs(RightFront.rotation(rotationUnits::deg)) < ticks){
        RightDriveForward(speed);
        LeftDriveBack(speed);
    }

    if (true){
        RightDriveBack(30);
        LeftDriveForward(30);
        task::sleep(30);
        RightDriveForward(0);
        LeftDriveBack(0);
    }
}


void flip(int power, float time){
    float seconds = time*1000;
    flip_up(power);
    task::sleep(seconds);
    flip_down(power);
    task::sleep(seconds);
    flip_up(0);
}



int main() {

}
