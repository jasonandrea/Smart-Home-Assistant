// define pin number for photoresistor sensor
#define LIGHT_SENSOR A5

void setup() {
    // set photoresistor pin to input
    pinMode(LIGHT_SENSOR, INPUT);
}

void loop() {
    // read light data and store it to LightValue
    double lightValue = analogRead(LIGHT_SENSOR);
    
    // if sensor detects bright light, publish events
    if (lightValue > 200) {
        Particle.publish("sensors_trigger", "LightSensorTriggered");
    }
    
    // publish light value for thingspeak
    Particle.publish("lightintensity", String(lightValue));
    
    // delay between each data read/publish
    delay(3500);
}