
#define EN1 5//pin for run the left motor 
#define IN1 12//pin for control left motor direction
#define EN2 6//pin for run the right motor 
#define IN2 7//pin for control right motor direction


#define Forward 0      //forward direction
#define Back 1         //backward direction

const int irPins[6] = {A0, A1, A2, A3, A4};
int irSensorAnalog[5] = {0,0,0,0,0}; 

void Read_Value(void)//Read out the return value of 5 line inspection sensor
{  
    for (int i = 0; i < 5; i++) {
    irSensorAnalog[i] = analogRead(irPins[i]);
   // Serial.print(irSensorAnalog[i]);
   // Serial.print("\n");
    }
}



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


void line_follow(int line )//Patrol line function, patrol black line for the white paper, the model black return value is less than 700, white is greater than 800z
{
 
  int stopped=0;
  while(line==1 && stopped!=1)
  {
   Read_Value();
 if((irSensorAnalog[0]<650 || irSensorAnalog[1] <650) && (irSensorAnalog[3]>800 && irSensorAnalog[4]>800))//Black line on the left
  { 
    // Serial.println("right");
    Motor(Forward,0,Forward,60);//turn right
    delay(10);
  }
  else  if((irSensorAnalog[3]<650 || irSensorAnalog[4] <650) && (irSensorAnalog[0]>800 && irSensorAnalog[1]>800))//The right black line
  {
    //Serial.println("left");
    Motor(Forward,60,Forward,0);//Turn left
    delay(10);
  }
  if(irSensorAnalog[2]<700)//Middle black line
  {
    //Serial.println("forward");
    Motor(Forward,30,Forward,30);//carried out
    delay(20);
  }
  else 
  {
    //Motor(Forward,0,Back,0);
    //delay(3000);
   // Serial.println("stop");
    Motor(Forward,60,Back,60);//Unidentified conditions tentatively scheduled for a slower forward
    stopped=1;
    
  }
  }
}
void line_follow2(int line )//Patrol line function, patrol black line for the white paper, the model black return value is less than 700, white is greater than 800z
{
  //Motor(Forward,40,Forward,40);
  int stopped=0;
  while(line==2 && stopped!=1)
  {
   Read_Value();
 if(irSensorAnalog[0]<650 && irSensorAnalog[2]>800)//Black line on the left
  { 
    // Serial.println("right");
    Motor(Forward,0,Forward,130);//turn right
    delay(10);
  }
  else if( irSensorAnalog[2]<650 && irSensorAnalog[0]>800)//The right black line
  {
    //Serial.println("left");
    Motor(Forward,130,Forward,0);//Turn left
    delay(10);
  }
  else if(irSensorAnalog[1]<650)//Middle black line
  {
    //Serial.println("forward");
    Motor(Forward,30,Forward,30);//carried out
    delay(20);
  }
  else 
  {
   // Serial.println("stop");
    Motor(Forward,60,Back,60);//Unidentified conditions tentatively scheduled for a slower forward
    stopped=1;
  }
  }
}
void line_follow3(int line )//Patrol line function, patrol black line for the white paper, the model black return value is less than 700, white is greater than 800z
{
  Motor(Forward,0,Forward,40);
  int stopped=0;
  while(line==3 && stopped!=1)
  {
   Read_Value();
 if(irSensorAnalog[2]<650 && irSensorAnalog[4]>800)//Black line on the left
  { 
    // Serial.println("right");
    Motor(Forward,0,Forward,130);//turn right
    delay(10);
  }
  else  if( irSensorAnalog[4]<650 && irSensorAnalog[2]>800)//The right black line
  {
    //Serial.println("left");
    Motor(Forward,130,Forward,0);//Turn left
    delay(10);
  }
  if(irSensorAnalog[3]<650)//Middle black line
  {
    //Serial.println("forward");
    Motor(Forward,30,Forward,30);//carried out
    delay(20);
  }
  else 
  {
   // Serial.println("stop");
    Motor(Forward,75,Forward,0);//Unidentified conditions tentatively scheduled for a slower forward
    stopped=1;
  }
  }
}
void setup()
{
  pinMode(5,OUTPUT);//Initialize motor control pin to output
  pinMode(6,OUTPUT);
  pinMode(7,OUTPUT);
  pinMode(12,OUTPUT); 
  Motor(Forward,0,Forward,0);//Motor stopped
  for (int i = 0; i < 5; i++) {
   pinMode(irPins[i],INPUT);
  }
  Serial.begin(9600);
}

void loop()
{
 //read sensor values
 line_follow(1);//line following
// line_follow2(2);
//line_follow3(3);
}









