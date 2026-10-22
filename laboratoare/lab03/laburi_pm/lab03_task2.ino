#include <Servo.h>

Servo myservo;  // create servo object to control a servo
// twelve servo objects can be created on most boards

int pos = 0;    // variable to store the servo position
int int_cnt = 0;

ISR(TIMER0_COMPA_vect) {
  // cod întrerupere 
  int_cnt++;
  if (int_cnt == 150) {
    pos += 20;
    if (pos == 180) {
    	pos = 0;
    }
    Serial.write("hi");
    myservo.write(pos);
    int_cnt = 0;
  }
}
 
void configure_timer0() {
  // exemplu de configurare pentru Timer 0 în mod CTC
  // care va genera întreruperi cu frecvența de 1Hz
  TCCR0A = 0;
  TCCR0B = 0;
  TCNT0 = 0;
  OCR0A = 156;            // compare match register 16MHz/256/2Hz-1
  TCCR0A |= (1 << WGM01);   // CTC mode
  TCCR0B |= (1 << CS00);
  TCCR0B |= (1 << CS02);

}
 
void init_timer0() {
  TIMSK0 |= (1 << OCIE0A);  // enable timer compare interrupt
}
 
void setup() {
  // dezactivăm întreruperile globale
  cli();  
  configure_timer0();
  init_timer0();
  // activăm întreruperile globale
  sei();
  
  myservo.attach(3);  // attaches the servo on pin 3 to the servo object
  // test led
  DDRD |= (1 << PD7);
  PORTD &= ~(1 << PD7);
  Serial.begin(9600);
}

void loop() {

}
