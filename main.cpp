/*Servo brown/black  → external supply GND + board GND
Servo red          → external 5V+
Servo signal 1/2/3 → GPIO4 / GPIO5 / GPIO6*/

#include <ESP32Servo.h>
Servo s1, s2, s3;

void setup() {
  s1.attach(4);
  s2.attach(5);
  s3.attach(6);
}

void loop() {
  s1.write(90);
  s2.write(90);
  s3.write(90);
}