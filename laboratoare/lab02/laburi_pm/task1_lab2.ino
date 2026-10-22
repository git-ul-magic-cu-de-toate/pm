#define LED PB5

char command[30];

void setup()
{
  DDRB |= (1 << LED);

  DDRD &= ~(1 << PD2);
  PORTD |= (1 << PD2);

  Serial.begin(9600);
  Serial.println("astept comenzi");
}
char cuvant[1000];
int blink = 0;

void loop()
{

  if (Serial.available()) {
    char a = Serial.read();

    int next_char = strlen(cuvant);
    cuvant[next_char] = a;
    cuvant[next_char + 1] = '\0';
    if (a == '\n' || a == ' ') {
      cuvant[0] = '\0';
    }
    if (strcmp(cuvant, "on") == 0) {
      if (blink == 1) {
        blink = 0;
      }
      PORTB |= (1 << LED);
      delay(1000);
    } else if (strcmp(cuvant, "off") == 0) {
      if (blink == 1) {
        blink = 0;
      }

      PORTB &= ~(1 << LED);
      delay(1000);
    } else if (strcmp(cuvant, "get") == 0) {
      if (blink == 1) {
        blink = 0;
      }
      
      if (PORTB & (1 << LED)) {
        Serial.println("ON");
      } else {
        Serial.println("OFF");
      }

    } else if  (strcmp(cuvant, "blink") == 0) {
      blink = 1;
    }
    Serial.println(cuvant);
  }

  while (blink) {
    PORTB |= (1 << LED); // ori _BV(LED)
    delay(100); // functie din framework-ul de Arduino pentru a simplifica momentan programarea
    PORTB &= ~(1 << LED); // ori _BV(LED)
    delay(100);

    if (Serial.available()) {
      return;
    }
  }
}