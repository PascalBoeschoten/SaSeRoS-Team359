// Note: For the scanner to work, the turret has to be set manually by the
// user to point straight ahead before starting the robot.

#define TURRET_ROTATION_DELAY 300

#define ULTRASONIC_IN IN_4
#define MOTOR_TURRET_OUT OUT_C
#define MOTOR_TURRET_PWR 30

#define TURRET_ROTATION_AMOUNT 20

// Procedure for making a full scan
void ultrasonic_scan() {
    int currentRotation = 0;
    int sensorValue = 0;
    SetSensorUltrasonic(ULTRASONIC_IN);
    
    // Turn turret completely to the left
    RotateMotor(MOTOR_TURRET_OUT, MOTOR_TURRET_PWR, -180);
    currentRotation += -180;
    
    while(currentRotation < 180){
        // Turn turret a little to the right
        RotateMotor(MOTOR_TURRET_OUT, MOTOR_TURRET_PWR, 
            TURRET_ROTATION_AMOUNT);
        currentRotation += TURRET_ROTATION_AMOUNT;
        
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
            TurnRobot(currentRotation, 50);

            // Test message
            ClearScreen();
            TextOut(0,0,"Found free direction! :)");
            Wait(1000);
            break;
        }
    }

    // No free direction was found
    // Turn the turret back to its original position
    RotateMotor(MOTOR_TURRET_OUT, MOTOR_TURRET_PWR, -currentRotation);
}