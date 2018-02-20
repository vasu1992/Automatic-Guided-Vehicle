/* 
This program can receive the IR data from the IR transmitter mounted on the AGV.
It uses IRremote library to decode the IR data
It uses NEC protocal of IR library for decoding
the AGV selects the line based on received signal
the speed of the motors can be defined program based on the Track designed.
we can set the speed by changing from o to 255 
based on IR line following sensors AGV follows the Black line


*/

#include <IRremote.h>
const int RECV_PIN = 17;

IRrecv irrecv(RECV_PIN);
decode_results results;


#define EN1 5//pin for run the left motor 
#define IN1 12//pin for control left motor direction
#define EN2 6//pin for run the right motor 
#define IN2 7//pin for control right motor direction


#define Forward 0      //forward direction
#define Back 1         //backward direction

const int irPins[6] = {A0, A1, A2, A3, A4};
int irSensorAnalog[5] = {0,0,0,0,0}; 
//Read out the return value of 5 line inspection sensor
void Read_Value(void)
{  
    for (int i = 0; i < 5; i++) {
    irSensorAnalog[i] = analogRead(irPins[i]);
   // Serial.print(irSensorAnalog[i]);
   Serial.print("read");
    }
}
//initilize the motors
void Motor(int M1_DIR,int M1_EN,int M2_DIR,int M2_EN)//control the motor
{
  //////////M1 left motor////////////////////////
  if(M1_DIR==Forward)//direction of motor 1
    digitalWrite(IN1,Forward);//forward
  else
    digitalWrite(IN1,Back);//back
  if(M1_EN==0)
    analogWrite(EN1,LOW);//stop 
 else
    analogWrite(EN1,M1_EN);//speed control

  ///////////M2 right motor//////////////////////
  if(M2_DIR==Forward)
    digitalWrite(IN2,Forward);
  else
    digitalWrite(IN2,Back);
  if(M2_EN==0)
    analogWrite(EN2,LOW);
  else
    analogWrite(EN2,M2_EN);
}
void turn_right()
{
  Serial.println("yes its left");
    Motor(Forward,60,Forward,0);//turn right
    delay(1000);
    
  }

void turn_left()
{
  Serial.println("yes its left");
    Motor(Forward,0,Forward,60);//turn right
    delay(1000);
    
  }
  void go_forward()
{
  Serial.println("yes its left");
    Motor(Forward,40,Forward,40);//turn right
    delay(1000);
    
  }
  void stop_a()
  {
    Motor(Forward,0,Forward,0);
    delay(500);
    }
// after serving conveyor system this function will be excuted to reach start point
void line_follow2(int line)//black return value is less than 700, white is greater than 800z
{
  go_forward();
  int stopped=0;
   while(line==2 && stopped!=1)
   {  
     Read_Value();
 if((irSensorAnalog[0]<650 || irSensorAnalog[1] <650) && (irSensorAnalog[3]>800 && irSensorAnalog[4]>800))//Black line on the left
  { 
    Motor(Forward,0,Forward,80);//turn right
    delay(10);
  }
  else  if((irSensorAnalog[3]<650 || irSensorAnalog[4] <650) && (irSensorAnalog[0]>800 && irSensorAnalog[1]>800))//The right black line
  {
    Motor(Forward,80,Forward,0);//Turn left
    delay(10);
  }
  else if(irSensorAnalog[2]<700)//Middle black line
  {
    Motor(Forward,30,Forward,30);//carried out
    delay(20);
  }
  else if ((irSensorAnalog[3]>800 && irSensorAnalog[4] >800) && (irSensorAnalog[0]>800 && irSensorAnalog[1]>800)&&(irSensorAnalog[2]>800))
  {
    Motor(Forward,60,Back,60);
     delay(10);
    }
    else 
    {
    Motor(Forward,0,Back,0);
    stopped=1;
    }
   }
}
//Line following function towards conveyor system 
void line_follow(int line)// black return value is less than 700, white is greater than 800
{
  int stopped=0;
   while(line==1 && stopped!=1)
   {  
     Read_Value();// reading line follow sensor values
   if((irSensorAnalog[0]<650 || irSensorAnalog[1] <650) && (irSensorAnalog[3]>800 && irSensorAnalog[4]>800))//Black line on the left
   { 
    Motor(Forward,0,Forward,80);//turn right
    delay(10);
    }
   else  if((irSensorAnalog[3]<650 || irSensorAnalog[4] <650) && (irSensorAnalog[0]>800 && irSensorAnalog[1]>800))//The right black line
   {
    Motor(Forward,80,Forward,0);//Turn left
    delay(10);
    }
   else if(irSensorAnalog[2]<700)//Middle black line
   {
    Motor(Forward,30,Forward,30);//carried out
    delay(20);
    }
   else if ((irSensorAnalog[3]>800 && irSensorAnalog[4] >800) && (irSensorAnalog[0]>800 && irSensorAnalog[1]>800)&&(irSensorAnalog[2]>800))
    {
     stop_a();
     line_follow2(2);//follows line towards starting point
     delay(10);
    }
   else 
    {
    Motor(Forward,0,Back,0);//stop the vehicle 
    stopped=1;
    }
   }
}

void setup() {
  pinMode(5,OUTPUT);//Initialize motor control pin to output
  pinMode(6,OUTPUT);
  pinMode(7,OUTPUT);
  pinMode(12,OUTPUT); 
  Motor(Forward,0,Forward,0);//Motor stopped
  for (int i = 0; i < 5; i++) {
   pinMode(irPins[i],INPUT);
  }
  Serial.begin(9600);
  irrecv.enableIRIn();//enabling IR reception
  
}

void loop() {
  //Receives IR data from transmitter and decode the data received
  if (irrecv.decode(&results)) {
    Serial.println(results.value, HEX);
     irrecv.resume();//resuming IR reception
  }
  if (results.value == 0x00fd20df) { //select line 1
    turn_left(); //turn left to follow line one
    line_follow(1);//line following
    results.value = 0x00000000;// clearing IR data after finishing task
  }
  if (results.value == 0x00fda05f) { //select line 2
    go_forward();// go forward to follow line 2
    line_follow(1);//line following
    results.value = 0x00000000; // clearing IR data after finishing task
  }
  if (results.value == 0x00fd609f) { //select line 3
    turn_right();//turn right to follow line3
    line_follow(1);// line following
    results.value = 0x00000000;// clearing IR data after finishing task
  }
}

