#EDGE_LIGHT_THRESHOLD 100

// Returns true if an edge is detected, false if not.
bool DetectEdge() {
	while(true) {
		if(Sensor(SENSOR_LIGHT_EDGE) >= EDGE_LIGHT_THRESHOLD) {
			// The sensor is pressed so there is no edge.
			return false;
        } else {
			// The sensor isn't pressed so there is an edge.
        	return true;
        }
	}
}
