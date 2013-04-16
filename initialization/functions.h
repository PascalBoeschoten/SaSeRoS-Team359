#include "NBCCommon.h"
#include "NXCDefs.h"

void Touch_Init(int Port){
 SetSensorType(Port, SENSOR_TYPE_TOUCH);
 SetSensorMode(Port, SENSOR_MODE_BOOL);
}

void Range_Sens_Init(int Port){
 SetSensorUltrasonic(Port);
 SetSensorMode(Port, SENSOR_MODE_RAW);
}

void Light_Sens_Init(int Port){
 SetSensorLight(Port);
 SetSensorMode(Port, SENSOR_MODE_RAW);
}

void Turn(int deg, int pwr){              //pwr should be anywhere between 0 and 100
 RotateMotor(OUT_A, pwr, deg);
 RotateMotor(OUT_B, pwr, -deg);
}

void Stop_Driving(){
Off(OUT_A);
Off(OUT_B);
}

void Drive_Forward(int pwr){
 OnFwd(OUT_A, pwr);
 OnFwd(OUT_B, pwr);
}

void Drive_Backward(int pwr){
 OnRev(OUT_A, pwr);
 OnRev(OUT_B, pwr);
}