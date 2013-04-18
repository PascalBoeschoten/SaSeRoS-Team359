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

// Turns the motors a certain amount of degrees
void TurnMotor(int deg, int pwr){              //pwr should be anywhere between 0 and 100
	if (deg < 0) {
		RotateMotorEx(OUT_AB, -pwr, deg, -100, true, true);
	}
	else {
		RotateMotorEx(OUT_AB, -pwr, deg, 100, true, true);
	}
}

// Turns the robot approximately a certain amount of degrees
void TurnRobot(int deg, int pwr) {
	float degrees = deg;
	TurnMotor(degrees*3.5, pwr);
}

void Stop_Driving(){
Off(OUT_A);
Off(OUT_B);
}

void Drive_Forward(int pwr){
 OnFwd(OUT_A, -pwr);
 OnFwd(OUT_B, -pwr);
}

void Drive_Backward(int pwr){
 OnRev(OUT_A, -pwr);
 OnRev(OUT_B, -pwr);
}

void ShortBeep() {
	PlayTone(500,100);
}

void LongBeep() {
    PlayTone(200,1000);
}

bool FrontBumperPressed() {
	// Inverted because the sensor is off when bumper is pressed.
	return !Sensor(SENSOR_TOUCH_FRONT_IN); 
}

bool RearBumperPressed() {
	// Inverted because the sensor is off when bumper is pressed.
	return !Sensor(SENSOR_TOUCH_BACK_IN); 
}