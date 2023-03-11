#include <Servo.h>
Servo servo;
void setup() {
  // put your setup code here, to run once:
servo.attach(9);
}

void loop() {
  // put your main code here, to run repeatedly:
servo.write(90);
_delay_ms(1000);
servo.write(0);
_delay_ms(1000);
}
