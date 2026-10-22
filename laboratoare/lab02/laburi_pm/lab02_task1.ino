#define LED PD7
unsigned long lastDebounceTimeINT = 0;  // the last time the output pin was toggled
unsigned long lastDebounceTimePCINT = 0;  // the last time the output pin was toggled
unsigned long debounceDelay = 50;    // the debounce time; increase if the output flickers

ISR(INT0_vect)
{
  // cod întrerupere externă
  if (millis() - lastDebounceTimeINT > debounceDelay) {
    PORTD ^= (1 << LED);
  }

  lastDebounceTimeINT = millis();
}


ISR(PCINT2_vect) {
  // cod întrerupere de tip pin change
  // TODO
  if (millis() - lastDebounceTimePCINT > debounceDelay) {
    PORTD ^= (1 << LED);
  }

  lastDebounceTimePCINT = millis();
}
 
void setup_interrupts() {
  // buton 1: PD2 / INT0
  // buton 2: PD4 / PCINT20
  cli();
 
  // input
  DDRD &= ~(1 << PD2) & ~(1 << PD4);
  // input pullup
  PORTD |= (1 << PD2) | (1 << PD4);
 
  // configurare intreruperi
  // intreruperi externe
  // TODO
  EICRA |= (1 << ISC01);
  EICRA &= ~(1 << ISC00);  
 
  // întreruperi de tip pin change (activare vector de întreruperi)
  // TODO
  PCICR |= (1 << PCIE2);

  // activare intreruperi
  // intrerupere externa
  // TODO
  EIMSK |= (1 << INT0);
 
  // întrerupere de tip pin change
  // TODO
  PCMSK2 |= (1 << PCINT20);

  sei();
}
 
void setup() {
  setup_interrupts();
  DDRD |= (1 << LED);
  PORTD &= ~(1 << LED);
}
 
void loop() {  
 
}