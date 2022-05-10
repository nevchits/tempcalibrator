//LM35 Test on NodeMCU

// initializes or defines the output pin of the LM35 temperature sensor
int LM35output= A2;

#define FAN 9

#define FAN_MAX_RATE 255;

int fan_rate = 0;
int init_speed = 0;

int top_speed = 0;
int acceleration = 5;

float celsius;

void setup() {
  pinMode(FAN, OUTPUT);
  Serial.begin(9600);
  Serial.println("LM35 PWM FAN Test");
}

void loop(){

  fanControl();  

}

void fanControl(){
  while (Serial.available() > 0) {

    //int top_speed = Serial.parseInt();
    //int acceleration = Serial.parseInt();
    getTemp();

    

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
    }
  }
}

void getTemp(){
  int analogValue = analogRead(LM35output);
  //float millivolts = (analogValue/1024.0) * 1000; //3300 is the voltage provided by NodeMCU. 1000mv is the maximum the node can read :(
  float millivolts = (analogValue/1024.0) * 5000; //for Arduino UNO
  celsius = millivolts/10;
  //Serial.print(analogValue);
  //Serial.print(" -> ");
  //Serial.println(millivolts);
  Serial.print("in DegreeC=   ");
  Serial.println(celsius);
  
  //---------- Here is the calculation for Fahrenheit ----------//
  
  //float fahrenheit = ((celsius * 9)/5 + 32);
  //Serial.print(" in Farenheit=   ");
  //Serial.println(fahrenheit);
  //delay(1000);

  //map temperature between 25 and 35 degrees to the 0 to 100 of the fan speed
  top_speed = map(celsius, 25,35,0,100);
  acceleration = 5; //let's use a constant 5 for now
  
}
