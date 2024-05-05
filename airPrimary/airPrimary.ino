//Primary
#include <programmable_air.h>

const int transmitPin1 = 7;
const int transmitPin2 = 8;
const int transmitPin3 = 9;

const int greenBtnPin = A4;
const int blueBtnPin = A1;
const int redBtnPin = A0;

int redBtnPrev = 0;
int greenBtnPrev = 0;
int blueBtnPrev = 0;

bool redExtended = false;
bool greenExtended = false;
bool blueExtended = false;

void sendToSecondary(int i, int value) {
  switch (i) {
    case 4:
      digitalWrite(transmitPin3, value);
      break;
    case 5:
      digitalWrite(transmitPin2, value);
      break;
    case 6:
      digitalWrite(transmitPin1, value);
      break;
  }
}

void setSuckValves(int value) {
  for (int i = 2; i <= 6; i += 2) {
    Serial.print("Setting valve ");
    Serial.print(i);
    Serial.print(" to ");
    Serial.println(value);
    setValve(i, value);
    sendToSecondary(i, value);
  }
}

void setBlowValves(int value) {
  for (int i = 1; i <= 6; i += 2) {
    Serial.print("Setting valve ");
    Serial.print(i);
    Serial.print(" to ");
    Serial.println(value);
    setValve(i, value);
    sendToSecondary(i, value);
  }
}

void extendColor(int blowValve, int suckValve, bool isExtended, String color) {
  if (!isExtended) {
    Serial.println(color + " OUT");
    setValve(blowValve, OPEN);
    switchOnPump(1, 100);
    delay(1000);

    switchOffPumps();
    setValve(blowValve, CLOSED);
  } else {
    Serial.println(color + " IN");
    setValve(suckValve, OPEN);
    switchOnPump(2, 100);
    delay(1000);

    switchOffPumps();
    setValve(suckValve, CLOSED);
  }
}

void setup() {
  initializePins();
  pinMode(transmitPin1, OUTPUT);
  pinMode(transmitPin2, OUTPUT);
  pinMode(transmitPin3, OUTPUT);

  pinMode(redBtnPin, INPUT);
  pinMode(greenBtnPin, INPUT);
  pinMode(blueBtnPin, INPUT);

  setBlowValves(CLOSED);
  setSuckValves(CLOSED);
}

void loop() {
  int redBtnValue = digitalRead(redBtnPin);
  int greenBtnValue = digitalRead(greenBtnPin);
  int blueBtnValue = digitalRead(blueBtnPin);

  if (redBtnValue == HIGH && redBtnPrev == 0) {
    extendColor(1, 2, redExtended, "RED");
    redExtended = !redExtended;
  }


  if (greenBtnValue == HIGH && greenBtnPrev == 0) {
    extendColor(3, 4, greenExtended, "GREEN");
    greenExtended = !greenExtended;
  }
  if (blueBtnValue == HIGH && blueBtnPrev == 0) {
    extendColor(5, 6, blueExtended, "BLUE");
    blueExtended = !blueExtended;
  }

  redBtnPrev = redBtnValue;
  greenBtnPrev = greenBtnValue;
  blueBtnPrev = blueBtnValue;

  if (readBtn(RED)) {
    switchOffPump(2);
    switchOnPump(1, 100);
    setBlowValves(OPENED);
    setSuckValves(CLOSED);
    Serial.println("EXTEND");
  }
  if (readBtn(BLUE)) {
    switchOffPump(1);
    switchOnPump(2, 100);
    setBlowValves(CLOSED);
    setSuckValves(OPENED);
    Serial.println("RETRACT");
  }
}