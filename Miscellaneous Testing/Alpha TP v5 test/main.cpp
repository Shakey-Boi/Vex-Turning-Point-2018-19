using namespace vex;
#include "robot-config.h"

int fullSpeed = 100;
int halfSpeed = 50;

int lock = 1;
void unlock(){
    lock = 1;
}

void test(int power){
    LeftMotor.spin(directionType::fwd, power, velocityUnits::pct);
    task::sleep(200);
    LeftMotor.stop(brakeType::brake);
}

void test2(int power){
    LeftMotor.spin(directionType::fwd, power, velocityUnits::pct);
    task::sleep(200);
    LeftMotor.stop(brakeType::hold);
}

void drive_forward(int speed, int distance, bool brake){    //may not need the brake
    // this functions takes in user inputted speed (till 100), distance(inches), and a boolean for a counter action with a brake

    RightMotor.resetRotation();             // reset internal motor values
    LeftMotor.resetRotation();

    float ticks = 0;                        // define ticks variable

    ticks = 360*(distance/12.566);          // 360 degrees in a rotation times circumference of a 4 inch wheel

    while ((LeftMotor.rotation(rotationUnits::deg) < ticks) && (RightMotor.rotation(rotationUnits::deg) < ticks)){  //while the encoder value is less than ticks
        RightMotor.spin(directionType::fwd, speed, velocityUnits::pct);     //run forward at user input speed
        LeftMotor.spin(directionType::fwd, speed, velocityUnits::pct);

    }

    if (brake){
        RightMotor.spin(directionType::rev, 10, velocityUnits::pct);      //applies a small force in the opposite directions. dont know how the v5 will handle it
        LeftMotor.spin(directionType::rev, 10, velocityUnits::pct);
        task::sleep(200);
        RightMotor.stop(brakeType::brake);
        LeftMotor.stop(brakeType::brake);
    }

    else{
        RightMotor.stop(brakeType::brake);      //standard brake
        LeftMotor.stop(brakeType::brake);
    }


}

void puncher_hold(int time, int power){ //power till 100 time in seconds
    //converts s --> milisec
    int time_wait = time/1000; //could just make it time = time/ 1000 ig

    //makes a test template for the v5 hold function on the puncher
    Puncher1.spin(directionType::fwd, power, velocityUnits::pct);       //wind up at specified power but not all the way
    Puncher2.spin(directionType::fwd, power, velocityUnits::pct);

    task::sleep(time_wait);      // wait

    Puncher1.stop(brakeType::hold);     //takes the place of a ratchet for instant shot
    Puncher2.stop(brakeType::hold);
}

void lockdown(){

    RightMotor.stop(brakeType::hold);
    LeftMotor.stop(brakeType::hold);



}

void tank_control(){
    RightMotor.spin(directionType::fwd, ControllerMain.Axis2.value(), velocityUnits::pct);      // right motor to channel 3
    RightMotor2.spin(directionType::fwd, ControllerMain.Axis2.value(), velocityUnits::pct);
    RightMotor3.spin(directionType::fwd, ControllerMain.Axis2.value(), velocityUnits::pct);
    LeftMotor.spin(directionType::fwd, ControllerMain.Axis3.value(), velocityUnits::pct);       // left motor to cahnnel 2
    LeftMotor2.spin(directionType::fwd, ControllerMain.Axis3.value(), velocityUnits::pct);
    LeftMotor3.spin(directionType::fwd, ControllerMain.Axis3.value(), velocityUnits::pct);

    task::sleep(20);
}

void split_arcade_control(){
        int X2 = 0, Y1 = 0, X1 = 0, threshold = 15;    //defining variables

    // deadzone for Y1/Ch3
	if(abs(ControllerMain.Axis3.value()) > threshold){
	Y1 = ControllerMain.Axis3.value();
    }

	else{
	Y1 = 0;
    }

    //deadzone for X2/Ch1
	if(abs(ControllerMain.Axis1.value()) > threshold){
		X2 = (.75*ControllerMain.Axis1.value());
    }

	else{
		X2 = 0;
    }


    RightMotor.spin(directionType::fwd, Y1-X2-X1, velocityUnits::pct);  //forward back on ch 1
    RightMotor2.spin(directionType::fwd, Y1-X2-X1, velocityUnits::pct);
    RightMotor3.spin(directionType::fwd, Y1-X2-X1, velocityUnits::pct);
    LeftMotor.spin(directionType::fwd, Y1+X2+X1, velocityUnits::pct);   //turning on ch 2
    LeftMotor2.spin(directionType::fwd, Y1+X2+X1, velocityUnits::pct);
    LeftMotor3.spin(directionType::fwd, Y1+X2+X1, velocityUnits::pct);
    task::sleep(20);

}

void arcade_control(){
    RightMotor.spin(directionType::fwd, (ControllerMain.Axis3.value() - ControllerMain.Axis4.value()) / 2, velocityUnits::pct); //everything on one stick
    LeftMotor.spin(directionType::fwd, (ControllerMain.Axis3.value() + ControllerMain.Axis4.value()) / 2, velocityUnits::pct);

    task::sleep(20);

}

int main() {
    lock = true;
    //display the program is starting
    Brain.Screen.print("Shake's Godly Skill");

    //infinite loop so the controller can pull values every iteration
 /*   while(1){


   ///////////////////////////////////////////////////////////////////////
   /////CONTROL LAYOUT////////////////////////////////////////////////////
         tank_control(); //////////////////////////////////////////////////
   ///////////////////////////////////////////////////////////////////////
   // options are tank_control, arcade_control, and split_arcade_control//
   ///////////////////////////////////////////////////////////////////////


        //puncher control       need to test directions
       if(ControllerMain.ButtonR2.pressing()){  //pressing takes the place of == 1
           //pull back
           Puncher1.spin(directionType::fwd, halfSpeed, velocityUnits::pct);
           Puncher2.spin(directionType::fwd, halfSpeed, velocityUnits::pct);
       }

        else if(ControllerMain.ButtonR1.pressing()){
            //other way
            Puncher1.spin(directionType::rev, halfSpeed, velocityUnits::pct);
            Puncher2.spin(directionType::rev, halfSpeed, velocityUnits::pct);
        }

        else{
            //if not pressing either button then stop both
            Puncher1.stop(brakeType::brake);
            Puncher2.stop(brakeType::brake);

        }

       if(ControllerMain.ButtonY.pressing()){   // change to pressed once you get the callback void figured out
        test(100);
       }

       if(ControllerMain.ButtonA.pressing()){
           test2(100);          //engages base lockdown function
       }

       if(ControllerMain.ButtonX.pressing()){
           drive_forward(50, 12, true );           //auton template testing
                                                   //makes base move forward at 50 speed for 12 inches with a brake
       }

    }   */
 while(true){
    if (lock == 1){
        split_arcade_control();
        if(ControllerMain.ButtonUp.pressing()){
            lock = 0;
            Brain.Screen.print("change");
        }
    }

    else if (lock == 0){
        lockdown();
        if(ControllerMain.ButtonDown.pressing()){
            Brain.Screen.print("change");
            unlock();
        }
    }
 }
}
