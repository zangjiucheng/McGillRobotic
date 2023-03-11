#include <Servo.h>

Servo servo;

void setup() {
  servo.attach(9); // Attach servo to pin 9
}

void loop() {
  servo.write(0); // Set servo position to 0 degrees
  _delay_ms(1000); // Wait 1 second
  servo.write(180); // Set servo position to 180 degrees
  _delay_ms(1000); // Wait 1 second
}
