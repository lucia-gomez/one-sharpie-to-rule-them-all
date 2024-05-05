//Secondary:
#include <programmable_air.h>

const int receivePin1 = 7;
const int receivePin2 = 8;
const int receivePin3 = 9;

int pin1Prev = 0;
int pin2Prev = 0;
int pin3Prev = 0;

void setup() {
  initializePins();
  pinMode(receivePin1, INPUT);
  pinMode(receivePin2, INPUT);
  pinMode(receivePin3, INPUT);
}

void loop() {
  int valve4 = digitalRead(receivePin3);
  int valve5 = digitalRead(receivePin2);
  int valve6 = digitalRead(receivePin1);

  if (valve4 != pin1Prev || valve5 != pin2Prev || valve6 != pin3Prev) {
    Serial.print(valve4);
    Serial.print(", ");
    Serial.print(valve5);
    Serial.print(", ");
    Serial.print(valve6);
    Serial.println("");

    setValve(1, valve4);
    setValve(2, valve5);
    setValve(3, valve6);
  }

  pin1Prev = valve4;
  pin2Prev = valve5;
  pin3Prev = valve6;
}