#define EDGE_LIGHT_THRESHOLD 300

// Returns true if an edge is detected, false if not.
bool DetectEdge() {
	if(SENSOR_LIGHT_EDGE >= EDGE_LIGHT_THRESHOLD) {
		// The sensor is detecting a lot of light so there is no edge.
		return false;
    } else {
		// The sensor is detecting not much light so there is an edge.
    	return true;
    }
}
