int int_cnt = 0;

ISR(TIMER1_COMPA_vect) {
  // cod întrerupere 
  int_cnt++;
  if (int_cnt == 1) {
    ADCSRA |= (1 << ADSC);
    ADCSRA |= (1 << ADIE);
    /* wait until conversion is complete */
  }
}

ISR(ADC_vect){		
    uint16_t adc_val = ADC;
    double v_in = (adc_val * 5) / 1024.0;

    Serial.print(v_in);   // debug value
    Serial.println("V");
    int_cnt = 0;	
}
 
void configure_timer1() {
  // exemplu de configurare pentru Timer 1 în mod CTC
  // care va genera întreruperi cu frecvența de 1Hz
  TCCR1A = 0;
  TCCR1B = 0;
  TCNT1 = 0;
  OCR1A = 62500;            // compare match register 16MHz/256/2Hz-1
  TCCR1B |= (1 << WGM12);   // CTC mode
  TCCR1B |= (1 << CS12);    // 256 prescaler 
}
 
void init_timer1() {
  TIMSK1 |= (1 << OCIE1A);  // enable timer compare interrupt
}
 
void setup() {
  // dezactivăm întreruperile globale
  cli();  
  configure_timer1();
  init_timer1();
  // activăm întreruperile globale
  sei();
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
 
}