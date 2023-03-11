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
aex::Array<long, 3> ultraData;
int SonarTime = 200;
bool turnStatus;

void setup() {
  turnStatus = false;
  Serial.begin(9600);
  servo.attach(servoPin);
  turnStatus = true;
  servo.write(0); // initial to 0
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
  Serial.print("[");
  for (int i; i < ultraData.getSize(); i++) {
    Serial.print(ultraData[i] + ", ");
  }
  Serial.println("]");
  DriveMoudle();
  delay(100);
}

void DriveMoudle() {
  /* 0 -> left, 1 -> front, 2 -> right */
  if (ultraData[1] < 10 && ultraData[2] > 10) {
    moveBackward();
    delay(100);
    moveBackwardRight();
    delay(100);
  } else if (ultraData[1] < 10 && ultraData[1] > 10) {
    moveBackward();
    delay(100);
    moveBackwardRight();
    delay(100);
  } else if (ultraData[1] < 10) {
    moveBackward();
    delay(100);
  } else if (ultraData[1] < 25 && ultraData[2] > 15) {
    moveForwardLeft();
    delay(100);
  } else if (ultraData[1] < 25 && ultraData[0] < 15) {
    moveForwardRight();
    delay(100);
  } else {
    moveForward();
  }
}

void detect() {
  stop();
  delay(200);
  if (turnStatus) {
    servo.write(30);
    ultraData[0] = sonar.ping_cm();
    delay(SonarTime);
    servo.write(90);
    ultraData[1] = sonar.ping_cm();
    delay(SonarTime);
    servo.write(150);
    ultraData[2] = sonar.ping_cm();
    turnStatus = false;
  } else {
    servo.write(150);
    ultraData[2] = sonar.ping_cm();
    delay(SonarTime);
    servo.write(90);
    ultraData[1] = sonar.ping_cm();
    delay(SonarTime);
    servo.write(30);
    ultraData[0] = sonar.ping_cm();
    turnStatus = true;
  }
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
