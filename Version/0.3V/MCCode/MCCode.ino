#include "NewPing.h"
#include <Servo.h>

/* ultrasonic sensor */
#define TRIGGER_PIN A3
#define ECHO_PIN A2
// Maximum distance we want to ping for (in centimeters).
#define MAX_DISTANCE 400
// NewPing setup of pins and maximum distance.
NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE);

/* Servo motor */
int servoPin = 3; // control pin for servo
Servo servo;

/* PWMMotor */
// Motor A connections
int enA = 10;
int in1 = 9;
int in2 = 8;
// Motor B connections
int enB = 7;
int in3 = 6;
int in4 = 5;

/* LightSensor */
int lightPin0 = A2; // analog pin for light sensor (forwards)
int lightPin1 = A1; // analog pin for light sensor (left)
int lightPin2 = A6; // analog pin for light sensor (right)
// int lightPin3 = A3; // analog pin for light sensor (backwards)

/* Constant */
int[4] lightData;
int[3] ultraData;
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
  DriveMoudle();
  delay(100);
  printData();
}

void printData() {
  Serial.print("UltraSound: [");
  for (int i; i < ultraData.getSize(); i++) {
    Serial.print(ultraData[i] + ", ");
  }
  Serial.println("]");

  Serial.println();

  Serial.print("LightSensor: [");
  for (int i; i < lightData.getSize(); i++) {
    Serial.print(lightData[i] + ", ");
  }
  Serial.println("]");
}

void DriveMoudle() {
  /* LightSensorData */
  /* 0 -> forward, 1 -> left, 2 -> right, 3-> backwards */
  if (lightData[2] > lightData[1]) {
    frountRight();
  } else if (lightData[1] > lightData[2]) {
    frountLeft();
  }
}

void frountRight() {
  /* 0 -> left, 1 -> front, 2 -> right */
  if (ultraData[1] < 10 && ultraData[2] > 10) {
    moveBackward();
    delay(100);
    moveBackwardRight();
    delay(100);
  } else if (ultraData[1] < 10 && ultraData[0] > 10) {
    moveBackward();
    delay(100);
    moveBackwardLeft();
    delay(100);
  } else if (ultraData[1] < 10) {
    moveBackward();
    delay(100);
  } else if (ultraData[1] < 25 && ultraData[2] > 15) {
    moveForwardRight();
    delay(100);
  } else if (ultraData[1] < 25 && ultraData[0] > 15) {
    moveForwardLeft();
    delay(100);
  } else {
    moveForward();
  }
}

void frountLeft() {
  /* 0 -> left, 1 -> front, 2 -> right */
  if (ultraData[1] < 10 && ultraData[0] > 10) {
    moveBackward();
    delay(100);
    moveBackwardLeft();
    delay(100);
  } else if (ultraData[1] < 10 && ultraData[2] > 10) {
    moveBackward();
    delay(100);
    moveBackwardRight();
    delay(100);
  } else if (ultraData[1] < 10) {
    moveBackward();
    delay(100);
  } else if (ultraData[1] < 25 && ultraData[0] > 15) {
    moveForwardLeft();
    delay(100);
  } else if (ultraData[1] < 25 && ultraData[1] > 15) {
    moveForwardRight();
    delay(100);
  } else {
    moveForward();
  }
}

void detect() {
  stop();
  delay(200);
  detectLigtSensor();
  detectUltraSound();
}

void detectLigtSensor() {
  lightData[0] = analogRead(lightPin0);
  lightData[1] = analogRead(lightPin1);
  lightData[2] = analogRead(lightPin2);
  lightData[3] = analogRead(lightPin3);
}
void detectUltraSound() {
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
