// Task that beeps every second so you know the system
// is running
task heartbeat() {
    while(true) {
        PlayTone(500, 100);
        Wait(1000);
    }
}