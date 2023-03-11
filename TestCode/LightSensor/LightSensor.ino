// https://www.allaboutcircuits.com/projects/an-arduino-controlled-light-sensor/\

int sensor_value = 0;
void setup() {}

void loop() {
  sensor_value = analogRead(A0);
  Serial.print("Sensor value: " + sensor_value);
  delay(100);
}