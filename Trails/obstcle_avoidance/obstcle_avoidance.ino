
#define EN1 6//
#define IN1 7//
#define EN2 5//
#define IN2 12//
#define Forward 0//
#define Back 1//

#define IR_IN  17//
#define L_IR 13//
#define R_IR 8//


//
void Motor(int M1_DIR,int M1_EN,int M2_DIR,int M2_EN)
{
  //////////M1////////////////////////
  if(M1_DIR==Forward)  digitalWrite(IN1,Forward); else digitalWrite(IN1,Back);
  if(M1_EN==0)       analogWrite(EN1,LOW);  else analogWrite(EN1,M1_EN);
  ///////////M2//////////////////////
  if(M2_DIR==Forward) digitalWrite(IN2,Forward);  else digitalWrite(IN2,Back);
  if(M2_EN==0)     analogWrite(EN2,LOW);    else analogWrite(EN2,M2_EN);
}



void turn_right()
{
  Serial.println("yes its left");
    Motor(Forward,60,Back,60);//turn right
    delay(1000);
    
  }

void turn_left()
{
  Serial.println("yes its left");
    Motor(Back,60,Forward,60);//turn right
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

void Obstacle_Avoidance()
{
  stop_a();
  turn_right();
  stop_a();
  go_forward();
  turn_left();
  stop_a();
  go_forward();
  stop_a();
  turn_left();
  go_forward();
  turn_right();
  }

void setup()
{
  pinMode(5,OUTPUT);
  pinMode(6,OUTPUT);
  pinMode(7,OUTPUT);
  pinMode(12,OUTPUT);
  
  pinMode(8,OUTPUT);
  pinMode(10,OUTPUT);
  pinMode(13,OUTPUT);
  pinMode(14,OUTPUT);
  pinMode(16,OUTPUT);
  pinMode(17,INPUT);

}

void loop()
{
  int l1=digitalRead(IR_IN);
  Serial.print(l1);
  Serial.println("bo");
Motor(Forward,40,Forward,40);
    if (l1==0)
    {
      //obscle detected
      Obstacle_Avoidance();
      delay(20); 
      }
}
