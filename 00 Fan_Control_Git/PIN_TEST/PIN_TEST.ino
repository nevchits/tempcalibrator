void setup() {

  pinMode(3, OUTPUT);
}

void loop() {

  digitalWrite(3, HIGH);   
  delay(1000);                        //wait for a second
  
  digitalWrite(3, LOW);    
  delay(1000);                       // wait for a second
}
