#include "NewPing.h"
#include <ArduinoExtra.h>
#include <Servo.h>

/* ultrasonic sensor */
#define TRIGGER_PIN 9
#define ECHO_PIN 10
// Maximum distance we want to ping for (in centimeters).
#define MAX_DISTANCE 400
// NewPing setup of pins and maximum distance.
NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE);

/* Servo motor */
int servoPin = 11; // control pin for servo
Servo servo;

/* PWMMotor */
// Motor A connections
int enA = 6;
int in1 = 8;
int in2 = 7;
// Motor B connections
int enB = 5;
int in3 = 1;
int in4 = 0;

/* Constant */
aex::Array<long> ultraData(3);
int angle = 0;           // servo position in degrees
bool turnStatus = false; // false = ccw, true = cw

void setup() {

  Serial.begin(9600);

  servo.attach(servoPin);
  servo.write(angle); // initial to 0
  // Set all the motor control pins to outputs
  pinMode(enA, OUTPUT);
  pinMode(enB, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);
  // Turn off motors - Initial state
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in4, LOW);
}

void loop() {

  detect();
  if (ultraData[0] < 10 || ultraData[1] < 10 || ultraData[2] < 10) {
    moveBackward();
    delay(1000);
    stop();
    delay(1000);
  } else {
    moveForward();
  }
}

void detect() {
  stop();
  delay(200);
  for (int i = 0; i < 3; i++) {
    /* code */
    ultraData[i] = sonar.ping_cm(); // get distance in cm
    turnStatus = turnServo(turnStatus);
    delay(100);
  }
}

bool turnServo(bool status) {
  if (status >= 175) {
    status = false;
  }
  if (status <= 5) {
    status = true;
  }
  if (status) {
    angle += 90;
  } else {
    angle -= 90;
  }
  servo.write(angle);
  return status;
}

void moveForward() {
  // Set motors to maximum speed
  // For PWM maximum possible values are 0 to 255
  analogWrite(enA, 255);
  analogWrite(enB, 255);

  // Turn on motor A & B
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
}

void moveBackward() {
  // Set motors to maximum speed
  // For PWM maximum possible values are 0 to 255
  analogWrite(enA, 255);
  analogWrite(enB, 255);

  // Turn on motor A & B
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);
}

void moveForwardLeft() {
  // Set motors to maximum speed
  // For PWM maximum possible values are 0 to 255
  analogWrite(enA, 128);
  analogWrite(enB, 255);

  // Turn on motor A & B
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
}

void moveForwardRight() {
  // Set motors to maximum speed
  // For PWM maximum possible values are 0 to 255
  analogWrite(enA, 255);
  analogWrite(enB, 128);

  // Turn on motor A & B
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
}

void moveBackwardLeft() {
  // Set motors to maximum speed
  // For PWM maximum possible values are 0 to 255
  analogWrite(enA, 128);
  analogWrite(enB, 255);

  // Turn on motor A & B
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);
}

void moveBackwardRight() {
  // Set motors to maximum speed
  // For PWM maximum possible values are 0 to 255
  analogWrite(enA, 255);
  analogWrite(enB, 128);

  // Turn on motor A & B
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);
}

void stop() {
  // Now turn off motors
  analogWrite(enA, 0);
  analogWrite(enB, 0);
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in4, LOW);
}