void setup() {
  // put your setup code here, to run once:
  pinMode(A1, INPUT);
  pinMode(A0, INPUT);
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  int adc_val = analogRead(A1);  // read the input pin
  double v_in = (adc_val * 5) / 1024.0;

  Serial.print(v_in);   // debug value
  Serial.println("V");

  delay(500);

  double t_in = (analogRead(A0) * 5 / 1024.0) * (1024 / 165);

  
  Serial.print(t_in);   // debug value
  Serial.println("C");
  delay(500);
}
