int redInPin = A2;
int blueInPin = A0;
int greenInPin = A1;

int redOutPin = 10;
int greenOutPin = 11;
int blueOutPin = 12;

int redPrev = 0;
int greenPrev = 0;
int bluePrev = 0;

bool redOn = false;
bool greenOn = false;
bool blueOn = false;

void setup() {
  pinMode(redInPin, INPUT);
  pinMode(greenInPin, INPUT);
  pinMode(blueInPin, INPUT);

  pinMode(redOutPin, OUTPUT);
  pinMode(greenOutPin, OUTPUT);
  pinMode(blueOutPin, OUTPUT);
}

void loop() {
  int redIn = digitalRead(redInPin);
  int greenIn = digitalRead(greenInPin);
  int blueIn = digitalRead(blueInPin);

  if (redIn == HIGH && redPrev == 0) {
    Serial.println(redOn ? "RED OFF" : "RED ON");
    digitalWrite(redOutPin, redOn ? LOW : HIGH);
    redOn = !redOn;
  } 

  if (greenIn == HIGH && greenPrev == 0) {
    Serial.println(greenOn ? "GREEN OFF" : "GREEN ON");
    digitalWrite(greenOutPin, greenOn ? LOW : HIGH);
    greenOn = !greenOn;
  } 

  if (blueIn == HIGH && bluePrev == 0) {
    Serial.println(blueOn ? "BLUE OFF" : "BLUE ON");
    digitalWrite(blueOutPin, blueOn ? LOW : HIGH);
    blueOn = !blueOn;
  } 

  redPrev = redIn;
  greenPrev = greenIn;
  bluePrev = blueIn;

  delay(10);
}
