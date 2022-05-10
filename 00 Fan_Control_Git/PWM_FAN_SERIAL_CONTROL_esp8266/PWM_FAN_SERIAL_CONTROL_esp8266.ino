

// the setup function runs once when you press reset or power the board
#define FAN 2
#define FAN_MAX_RATE 255


int fan_rate = 0;
int init_speed = 0;
int time_check = 0;
int interval = 2000;
int prev_time_check = 0;



void setup() {
  // initialize digital pin LED_BUILTIN as an output.
  pinMode(FAN, OUTPUT);
  Serial.begin(4800);
  Serial.println("PWM FAN Test");
  //time_check = millis();  //no need
}

// the loop function runs over and over again forever
void loop() {

    
  while (Serial.available() > 0) {

    int top_speed = Serial.parseInt();
    int acceleration = Serial.parseInt();

    

    if (Serial.read() == '\n') {
      // constrain the values to 0 - 255
      top_speed = constrain(top_speed, 0, 255);

      Serial.print("Top Speed: ");
      Serial.println(top_speed);
      Serial.print("Delay time: ");
      Serial.println(acceleration);

      //for (int fan_rate = 0; fan_rate < FAN_MAX_RATE; fan_rate++){
       for (int i=init_speed; i <= top_speed; i++) {
        fan_rate = i;
        analogWrite(FAN, fan_rate);
        int fan_percent = map(fan_rate, 0, 255, 0, 100);
        Serial.print(fan_percent);
        Serial.println("%");
        delay(acceleration);  //should take 15.3 seconds to full speed. you should put in validation controls. like what if someone doest enter a second int?
      }

      //for deceleration:
        if (init_speed > top_speed){
          for (int i=init_speed; i > top_speed; i--) {
          fan_rate = i;
          analogWrite(FAN, fan_rate);
          int fan_percent = map(fan_rate, 0, 255, 0, 100);
          Serial.print(fan_percent);
          Serial.println("%");
          delay(acceleration);  //should take 15.3 seconds to full speed. you should put in validation controls. like what if someone doest enter a second int?
        }
      }

      init_speed = top_speed;
//       delay(5000);   //run at full speed for 5 seconds
//    
//       //for (int fan_rate =  FAN_MAX_RATE; fan_rate > 0;  fan_rate --){
//       for (int i=top_speed; i > 0; i--) {
//        fan_rate = i;
//        analogWrite(FAN, fan_rate);
//        int fan_percent = map(fan_rate, 0, 255, 0, 100);
//        Serial.print(fan_percent);
//        Serial.println("%");
//        delay(20);  //should take 5.1 seconds to 0 speed 
//       }
//    
//       delay(5000);
    } 
  }
  //Write Temp here

  if ((millis() - time_check) > interval){
    time_check = millis();
    Serial.println("Temp = NOT CONNECTED!");
  }
  
  
}
