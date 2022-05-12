/********************************************************
 * PID Fan Test 
 * Adopted from PID basic example
 * Reading analog input A0 to control analog PWM output 9
 ********************************************************/

#include <PID_v1.h>

#define PIN_INPUT A2
#define PIN_OUTPUT 9

//Define Variables we'll be connecting to
double oldSetpoint, Setpoint, Input, Output;


//Specify the links and initial tuning parameters
double Kp=2, Ki=5, Kd=1;
PID myPID(&Input, &Output, &Setpoint, Kp, Ki, Kd, DIRECT);

void setup()
{

  Serial.begin(9600);

  Serial.println("-------------- PID Test ---------------");
  //initialize the variables we're linked to
  Input = analogRead(PIN_INPUT);
  
  //initial set point value somewhere inbetween : 44
  Setpoint = 44;
  oldSetpoint = 44;

  //turn the PID on
  myPID.SetMode(AUTOMATIC);
}

void loop()
{
  //be able to change set point using Serial input

  //while (Serial.available() > 0){
    //rest of code stays in here
      //change set point:
      getSetPoint();
      
      Input = analogRead(PIN_INPUT);

      Serial.print ("Input --> ");
      Serial.println(Input);
      
      myPID.Compute();
      Serial.print ("Calculated output --> ");
      Serial.println(Output);
      Serial.println();
      analogWrite(PIN_OUTPUT, Output);

      
 // }
  

}

void getSetPoint(){
  while (Serial.available() > 0) {
    Setpoint = Serial.parseInt();   //int to double... hmmm...
    if (Setpoint ==0){
      Setpoint = oldSetpoint;
    }
    else {
      oldSetpoint = Setpoint;
    }
    Serial.print("New Set Point = ");
    Serial.println(Setpoint);
  }
}
