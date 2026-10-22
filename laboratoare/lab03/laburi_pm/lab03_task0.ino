int int_cnt = 0;

ISR(TIMER1_COMPA_vect) {
  // cod întrerupere 
  int_cnt++;
  if (int_cnt == 5) {
    Serial.write("5 seconde");
    int_cnt = 0;
  }
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
  Serial.begin(9600);
}
 
void loop() {
 
}