/*
  Blink

  Turns an LED on for one second, then off for one second, repeatedly.

  Most Arduinos have an on-board LED you can control. On the UNO, MEGA and ZERO
  it is attached to digital pin 13, on MKR1000 on pin 6. LED_BUILTIN is set to
  the correct LED pin independent of which board is used.
  If you want to know what pin the on-board LED is connected to on your Arduino
  model, check the Technical Specs of your board at:
  https://www.arduino.cc/en/Main/Products

  modified 8 May 2014
  by Scott Fitzgerald
  modified 2 Sep 2016
  by Arturo Guadalupi
  modified 8 Sep 2016
  by Colby Newman

  This example code is in the public domain.

  https://www.arduino.cc/en/Tutorial/BuiltInExamples/Blink
*/

// the setup function runs once when you press reset or power the board
#define FAN 9

#define FAN_MAX_RATE 255;

int fan_rate = 0;
int init_speed = 0;



void setup() {
  // initialize digital pin LED_BUILTIN as an output.
  pinMode(FAN, OUTPUT);
  Serial.begin(9600);
  Serial.println("PWM FAN Test");
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
}
