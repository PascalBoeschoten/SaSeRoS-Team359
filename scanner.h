// Note: For the scanner to work, the turret has to be set manually by the
// user to point straight ahead before starting the robot.

#define TURRET_ROTATION_DELAY 300

#define ULTRASONIC_IN IN_4
#define MOTOR_TURRET_OUT OUT_C
#define MOTOR_TURRET_PWR 30

// Procedure for making a full scan
void ultrasonic_scan() {
    int currentRotation = 0;
    int turnAmount = 10;
    int sensorValue = 0;
    SetSensorUltrasonic(ULTRASONIC_IN);
    
    // Turn turret completely to the left
    RotateMotor(MOTOR_TURRET_OUT, MOTOR_TURRET_PWR, -180);
    currentRotation += -180;
    
    while(currentRotation < 180){
        // Turn turret 10 degrees to the right
        RotateMotor(MOTOR_TURRET_OUT, MOTOR_TURRET_PWR, 10);
        currentRotation += 10;
        
        // Wait for turret to rotate and the sensor to get a value
        Wait(TURRET_ROTATION_DELAY);
        
        // Measure distance with the sensor
        sensorValue = SensorUS(ULTRASONIC_IN);
        
        // (for testing) Print the value on the LCD
        ClearScreen();
        NumOut(0, 0, SensorUS(ULTRASONIC_IN));

        // Check if the value is above the threshold
        if (sensorValue > ULTRASONIC_THRESHOLD) {
            // Found a clear direction, turn and stop scanning
            Turn(currentRotation, 0);
            break;
        }
    }
    // No free direction was found
    // Turn the turret back to its original position
    RotateMotor(MOTOR_TURRET_OUT, MOTOR_TURRET_PWR, -currentRotation);
}