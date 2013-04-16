// Note: For the scanner to work, the turret has to be set manually by the
// user to point straight ahead before starting the robot.

#define TURRET_ROTATION_DELAY 300

#define ULTRASONIC_IN IN_4
#define MOTOR_TURRET_OUT OUT_C
#define MOTOR_TURRET_PWR 30

#define TURRET_ROTATION_AMOUNT 20

int scanner_currentRotation = 0;

void TurnTurret(int deg) {
    RotateMotor(MOTOR_TURRET_OUT, MOTOR_TURRET_PWR, deg);
    scanner_currentRotation += deg;
}

void CenterTurret() {
    RotateMotor(MOTOR_TURRET_OUT, MOTOR_TURRET_PWR,
     -scanner_currentRotation);
    scanner_currentRotation = 0;
}

// Procedure for checking a single direction
bool CheckDirection(int dir) {
    TurnTurret(dir);
    Wait(TURRET_ROTATION_DELAY);
    if (SensorUS(ULTRASONIC_IN) > ULTRASONIC_THRESHOLD) {
        TurnTurret(-dir);
        return true;
    }
    else {
        TurnTurret(-dir);
        return false;
    }
}

// Procedure for making a full scan
// Returns an angle where the free direction is, or 0 if there was no
// direction found.
int UltrasonicScan() {
    int sensor_value = 0;
    SetSensorUltrasonic(ULTRASONIC_IN);
    
    // Turn turret completely to the left
    TurnTurret(-180);
    
    while(scanner_currentRotation < 180){
        // Turn turret a little to the right
        TurnTurret(TURRET_ROTATION_AMOUNT);

        // Wait for turret to rotate and the sensor to get a value
        Wait(TURRET_ROTATION_DELAY);
        
        // Measure distance with the sensor
        sensor_value = SensorUS(ULTRASONIC_IN);
        
        // (for testing) Print the value on the LCD
        ClearScreen();
        NumOut(0, 0, SensorUS(ULTRASONIC_IN));

        // Check if the value is above the threshold
        if (sensor_value > ULTRASONIC_THRESHOLD) {
            // Return the found direction
            CenterTurret();
            return sensor_value;
        }
    }

    // No free direction was found
    // Turn the turret back to its original position
    CenterTurret();
    return 0;
}