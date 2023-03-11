#define trigPin 9
#define echoPin 10
long duration;
int distance;
void setup() {
  // put your setup code here, to run once:
pinMode(trigPin, OUTPUT);
pinMode(echoPin, INPUT);
Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
digitalWrite(trigPin, LOW);
_delay_ms(10);
digitalWrite(trigPin, HIGH);
_delay_ms(20);
digitalWrite(trigPin,LOW);
duration = pulseIn(echoPin,HIGH);
distance = duration/58.2;
_delay_ms(500);
}
