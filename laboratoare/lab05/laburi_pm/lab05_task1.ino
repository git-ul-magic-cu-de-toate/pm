//Master Arduino Code:
#include<SPI.h>                             //Library for SPI 

char mes[40] = "ne plac cartofii\n";
int index = 0;

void setup (void){
  Serial.begin(9600);
  SPI.begin();
  SPI.setClockDivider(SPI_CLOCK_DIV8);
  digitalWrite(SS, HIGH); 
  delay(2000);
}

void loop(void) {
  if (index < strlen(mes)) {
      byte master_send, master_receive;          
      digitalWrite(SS, LOW);
      delay(500);
      
      master_send = mes[index];                            
      master_receive = SPI.transfer(master_send);
      Serial.print((char)master_receive);
      index++;
      if (index == strlen(mes)) {
        Serial.print("\ngata!\n");
      }
      delay(1000);
  }
}
