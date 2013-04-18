int angle;
int turret_angle;
bool stuck = false;
bool reverse = false;
bool direction = false;

int Random_Angle(){             //returns a random value between -180 and 180
 int x;
 x = (Random() % 360);
 x  -= 180;
 return x;
}

task Look_Back() {
   while(!reverse){
        if(!Sensor(back_bumper)){
        Stop_Driving();
        Drive_Backward(ENGINE_POWER);
//        TurnRobot(360, ENGINE_POWER);
        Wait(1000);
        Stop_Driving();
        Drive_Forward(ENGINE_POWER);
     }
   }
   while(reverse){
      if(!Sensor(back_bumper)){
           stuck = true;
           TextOut(1, 1, "Stuck restart required");
      }
   }
}

task Object_Detection() {
    while(!stuck){
     if(SensorUS(range_sensor) < ULTRASONIC_THRESHOLD){
        Stop_Driving();
        while(direction){
           angle = Random_Angle();
           direction = !CheckDirection(angle);
        }
//        ClearScreen();
//        NumOut(1, 1, angle);
        TurnRobot(angle, ENGINE_POWER);
        Drive_Forward(ENGINE_POWER);
        direction = true;
        ShortBeep();
     }
     if(!Sensor(front_bumper)){
        Stop_Driving();
        reverse = true;
        Drive_Backward(ENGINE_POWER);
        Wait(1000);
        Stop_Driving();
        reverse = false;
        while(direction){
           angle = Random_Angle();
           direction = !CheckDirection(angle);
        }
//        ClearScreen();
//        NumOut(1, 1, angle);
        TurnRobot(angle, ENGINE_POWER);
        Drive_Forward(ENGINE_POWER);
        direction = true;
        LongBeep();
     }

  }
}