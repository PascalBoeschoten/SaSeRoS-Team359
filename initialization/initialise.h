#include "NBCCommon.h"
#include "NXCDefs.h"
#include "functions.h"

#define front_bumper IN_1
#define back_bumper IN_3
#define range_sensor IN_4
#define light_sensor IN_2

void initialise(){

int  Range;
int  Light;

 Touch_Init(front_bumper);
 Wait(1000);
TextOut(0, 1, "Push front bumper");
     while(Sensor(front_bumper)){}
     ClearLine(1);
TextOut(0, 1, "Sensor works");
 Wait(5000);
     ClearLine(1);
 Touch_Init(back_bumper);
  Wait(1000);
  TextOut(0, 1, "Push Back bumper");
     while(!Sensor(back_bumper)){}
     ClearLine(1);
TextOut(0, 1, "Sensor works");
Range_Sens_Init(range_sensor);
 Wait(1000);
Range = SensorUS(range_sensor);
     ClearLine(1);
TextOut(0, 1, "Test Range Sensor");
     while((SensorUS(range_sensor) > (Range - 10)) && (SensorUS(range_sensor) < (Range + 10))){}
     ClearLine(1);
TextOut(0, 1, "Sensor works");
 Wait(5000);
 Light_Sens_Init(light_sensor);
 Wait(1000);
Light = Sensor(light_sensor);
TextOut(0, 1, "Test Light Sensor");
//while(TRUE){NumOut(1, 1, Sensor(IN_2));}
     while((Sensor(light_sensor) > (Light - 100)) && (Sensor(light_sensor) < (Light + 100))){}
     ClearLine(1);
TextOut(0, 1, "Sensor works");
 Wait(5000);
     ClearLine(1);
 TextOut(0, 1, "DONE!");
 }