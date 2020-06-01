// define pins for all leds
#define LIGHT_SENSOR_LED A3
#define ULTRASONIC_SENSOR_LED A1

// blink led 10 times. 100ms delay between blink
void ledBlink(int color) {
    for (int i = 0; i < 10; i++) {
        digitalWrite(color, HIGH);
        delay(100);
        digitalWrite(color, LOW);
        delay(100);
    }
}

// handler for reading published event from the other Argon device (argon-biscuit) and raspberry pi (pi-cookie)
void handler(const char *event, const char *data) {
    if (strcmp(data, "LightSensorTriggered")) {
        ledBlink(LIGHT_SENSOR_LED);
    }
    else if (strcmp(data, "UltrasonicSensorTriggered")) {
        ledBlink(ULTRASONIC_SENSOR_LED);
    }
}

void setup() {
    // set all LED pins to output
    pinMode(LIGHT_SENSOR_LED, OUTPUT);
    pinMode(ULTRASONIC_SENSOR_LED, OUTPUT);
    
    // turn off all led, just to make sure
    digitalWrite(LIGHT_SENSOR_LED, LOW);
    digitalWrite(ULTRASONIC_SENSOR_LED, LOW);
    
    // subscribe
    Particle.subscribe("sensors_trigger", handler);
}

void loop() {
    // nothing
}