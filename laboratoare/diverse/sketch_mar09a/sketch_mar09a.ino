#define LED 13

int delayVal = 100;

void setup() {
  // put your setup code here, to run once:
  pinMode(LED, OUTPUT);
  pinMode(PD2, INPUT_PULLUP);
  pinMode(PD3, INPUT_PULLUP);
}

void loop() {
  // put your main code here, to run repeatedly:
  int incr = digitalRead(PD2);
  int decr = digitalRead(PD3);

  if (incr == 0) {
    delayVal += 200;
  }

  if (decr == 0) {
    delayVal -= 200;

    if (delayVal < 0) {
      delayVal = 1;
    }
  }

  digitalWrite(LED, HIGH);
  delay(delayVal);

  digitalWrite(LED, LOW);
  delay(delayVal);
}
