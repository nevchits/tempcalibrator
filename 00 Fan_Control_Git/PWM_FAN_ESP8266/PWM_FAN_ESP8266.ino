/*********
  Credit: Rui Santos
  Complete project details at https://randomnerdtutorials.com  
*********/

const int FAN = 2; 

void setup() {
    Serial.begin(4800);
  Serial.println("PWM FAN Test");
}

void loop() {
  
  for(int dutyCycle = 0; dutyCycle < 255; dutyCycle++){   
    
    analogWrite(FAN, dutyCycle);
    int fan_percent = map(dutyCycle, 0, 255, 0, 100);
    Serial.print(fan_percent);
    Serial.println("%");
    delay(20);
  }

delay(5000);   //run at full speed for 5 seconds
  
  for(int dutyCycle = 255; dutyCycle > 0; dutyCycle--){
   
    analogWrite(FAN, dutyCycle);
    int fan_percent = map(dutyCycle, 0, 255, 0, 100);
    Serial.print(fan_percent);
    Serial.println("%");
    delay(20);
  }

delay(5000); 
}
