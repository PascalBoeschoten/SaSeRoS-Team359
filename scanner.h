// Note: For the scanner to work, the turret has to be set manually by the
// user to point straight ahead before starting the robot.

#define TURRET_ROTATION_DELAY 300

#define ULTRASONIC_IN IN_4
#define MOTOR_TURRET_OUT OUT_C
#define MOTOR_TURRET_PWR 30

#define TURRET_ROTATION_AMOUNT 20

int scanner_currentRotation = 0;

void turnTurret(int deg) {
    RotateMotor(MOTOR_TURRET_OUT, MOTOR_TURRET_PWR, deg);
    scanner_currentRotation += deg;
}

void centerTurret() {
    RotateMotor(MOTOR_TURRET_OUT, MOTOR_TURRET_PWR,
     -scanner_currentRotation);
    scanner_currentRotation = 0;
}

// Procedure for making a full scan
// Returns an angle where the free direction is, or 0 if there was no
// direction found.
int ultrasonic_scan() {
    int sensorValue = 0;
    SetSensorUltrasonic(ULTRASONIC_IN);
    
    // Turn turret completely to the left
    turnTurret(-180);
    
    while(scanner_currentRotation < 180){
        // Turn turret a little to the right
        turnTurret(TURRET_ROTATION_AMOUNT);

        // Wait for turret to rotate and the sensor to get a value
        Wait(TURRET_ROTATION_DELAY);
        
        // Measure distance with the sensor
        sensorValue = SensorUS(ULTRASONIC_IN);
        
        // (for testing) Print the value on the LCD
        ClearScreen();
        NumOut(0, 0, SensorUS(ULTRASONIC_IN));

        // Check if the value is above the threshold
        if (sensorValue > ULTRASONIC_THRESHOLD) {
            // Return the found direction
            return sensorValue;
        }
    }

    // No free direction was found
    // Turn the turret back to its original position
    centerTurret();
    return 0;
}