#include <Arduino.h>
#include <ESP32Servo.h>

Servo s1, s2, s3;

enum State { STATE_0, STATE_1, STATE_2, STATE_3, NUM_STATES };

// Servo angles for each state: {servo1, servo2, servo3}
const int angles[NUM_STATES][3] = {
  {  0,   0,   0},   // STATE_0
  { 90,   0,  90},   // STATE_1
  {  0,  90,   0},   // STATE_2
  {180, 180, 180},   // STATE_3
};

State state = STATE_0;

void applyState(State s) {
  s1.write(angles[s][0]);
  s2.write(angles[s][1]);
  s3.write(angles[s][2]);
}

void setup() {
  s1.attach(4);
  s2.attach(5);
  s3.attach(6);
  applyState(state);
}

void loop() {
  int knob = analogRead(2);                    // 0 to 4095
  int zoneWidth = 4096 / NUM_STATES;
  State zone = (State)constrain(knob / zoneWidth, 0, NUM_STATES - 1);

  // Only change state once the knob is clearly inside a new zone (stops flickering at the edges)
  int low  = state * zoneWidth - 100;
  int high = (state + 1) * zoneWidth + 100;
  if (zone != state && (knob < low || knob > high)) {
    state = zone;
    applyState(state);
  }

  delay(20);
}