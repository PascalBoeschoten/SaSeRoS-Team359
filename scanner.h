// Note: For the scanner to work, the turret has to be set manually by the
// user to point straight ahead before starting the robot.

#define TURRET_ROTATION_DELAY 300

#define MOTOR_TURRET_PWR 30

#define TURRET_ROTATION_AMOUNT 20

#define ULTRASONIC_THRESHOLD 30

#define MOTOR_TURRET_OUT OUT_C

int scanner_currentRotation = 0;

void TurnTurret(int deg) {
    RotateMotor(MOTOR_TURRET_OUT, MOTOR_TURRET_PWR, deg);
    scanner_currentRotation += deg;
}

bool ObstacleSighted() {
    return SensorUS(ULTRASONIC_IN) < ULTRASONIC_THRESHOLD;
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
    if (ObstacleSighted()) {
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
    
        // Check if there is an obstacle
        if (ObstacleSighted()) {
            // Return the found direction
            int returnval = scanner_currentRotation;
            CenterTurret();
            return returnval;
        }
    }

    // No free direction was found
    // Turn the turret back to its original position
    CenterTurret();
    return 0;
}
