#define LED PD7
unsigned long lastDebounceTimeINT = 0;  // the last time the output pin was toggled
unsigned long lastDebounceTimePCINT = 0;  // the last time the output pin was toggled
unsigned long debounceDelay = 50;    // the debounce time; increase if the output flickers

ISR(INT0_vect)
{
  // cod întrerupere externă
  if (millis() - lastDebounceTimeINT > debounceDelay) {
      ADCSRA |= (1 << ADSC);
    /* wait until conversion is complete */
    while (!(ADCSRA & (1 << ADIF)));
    uint16_t adc_val = ADC;
    double v_in = (adc_val * 5) / 1024.0;

    Serial.print(v_in);   // debug value
    Serial.println("V");
  }

  lastDebounceTimeINT = millis();
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
  // put your setup code here, to run once:

  setup_interrupts();
  DDRD |= (1 << LED);
  PORTD &= ~(1 << LED);

  pinMode(A1, INPUT);
  pinMode(A0, INPUT);
  Serial.begin(9600);

  ADMUX = 0;
  /* ADC1 - channel 1 */
  ADMUX |= (1 << MUX0);
  /* AVCC with external capacitor at AREF pin */
  ADMUX |= (1 << REFS0);

  ADCSRA = 0;
  /* set prescaler at 128 */
  ADCSRA |= (7 << ADPS0);
  /* enable ADC */
  ADCSRA |= (1 << ADEN);
}

void loop() {
  // put your main code here, to run repeatedly:
    /* start conversion */


  // delay(500);

  // double t_in = (analogRead(A0) * 5 / 1024.0) * (1024 / 165);

  
  // Serial.print(t_in);   // debug value
  // Serial.println("C");
  // delay(500);
}
