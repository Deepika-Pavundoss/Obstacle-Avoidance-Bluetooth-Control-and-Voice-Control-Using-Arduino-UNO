#include <AFMotor.h>
#define Speed 170
#define Echo A4
#define Trig A5
char value;
int distance;
AF_DCMotor M1(1);
AF_DCMotor M2(2);
AF_DCMotor M3(3);
AF_DCMotor M4(4);
void setup() {
   Serial.begin(9600);
   pinMode(Trig, OUTPUT);
   pinMode(Echo, INPUT);
   M1.setSpeed(Speed);
   M2.setSpeed(Speed);
   M3.setSpeed(Speed);
   M4.setSpeed(Speed);
}
// Ultrasonic sensor distance reading function
int ultrasonic() {
 digitalWrite(Trig, LOW);
 delayMicroseconds(4);
 digitalWrite(Trig, HIGH);
 delayMicroseconds(10);
digitalWrite(Trig, LOW);
 long t = pulseIn(Echo, HIGH);
 long cm = t / 29 / 2; //time convert distance
 return cm;
}
void Obstacle() {
 distance = ultrasonic();
 if (distance <= 12) {
 Stop();
 delay(100);
 }
}
void Stop() {
 M1.run(RELEASE);
 M2.run(RELEASE);M3.run(RELEASE);
 M4.run(RELEASE);
}
void loop() {
   Bluetoothcontrol();
   Obstacle();
}
void Bluetoothcontrol() {
   if (Serial.available() > 0) {
   value = Serial.read();
   Serial.println(value);
   }
   if (value == 'F') {
   forward();
   } else if (value == 'B') {
   backward();
   } else if (value == 'L') {
   left();
   } else if (value == 'R') {
   right();
   } else if (value == 'S') {
   Stop();
   }
}
void forward() {
 M1.run(BACKWARD);
 M2.run(FORWARD);
 M3.run(BACKWARD);
 M4.run(BACKWARD);
}
void backward() {
 M1.run(FORWARD);
 M2.run(BACKWARD);
 M3.run(FORWARD);
 M4.run(FORWARD);
}
void right() {
 M1.run(FORWARD);
 M2.run(BACKWARD);
 M3.run(BACKWARD);
 M4.run(BACKWARD);
}
void left() {
 M1.run(BACKWARD);
 M2.run(FORWARD);
 M3.run(FORWARD);
 M4.run(FORWARD);
}
