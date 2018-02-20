/*
The main idea is to select line to where the AGV has to go.
For that here three different lines are defined as line1,line2,lin3.
Based on active signal from particular line the AGV serves accoringly.
*/

//declaring lines as pushbuttons
int line1=7;//button1 as line1
int line2=8;//button2 as line2
int line3=9;//button3 as line3
//defining variables for reading line information
int value1=0; //variable reading line1 status
int value2=0; //variable reading line2 status
int value3=0; //variable reading line3 status

void setup() {
  Serial.begin(9600);// Default communication rate of the Bluetooth module
  //setting lines as inputs to Arduino UNO
  pinMode(line1, INPUT);
  pinMode(line2, INPUT);
  pinMode(line3, INPUT);
   
}
void loop() {
 // Reading the buttons status
 value1= digitalRead(line1);
 value2= digitalRead(line2);
 value3= digitalRead(line3);
//based on status of button performs operation 
 if (value1 == LOW) {
  delay(350);//response delay of transmission
   Serial.write('a'); //when line1 is active then UNO transmits character 'a' through HC-05 module
 }
 if (value2==LOW){
  delay(350);//response delay of transmission
   Serial.write('c'); //when line2 is active then UNO transmits character 'a' through HC-05 module
 }  
 if (value3==LOW){
  delay(350);//response delay of transmission
   Serial.write('e');//when line3 is active then UNO transmits character 'a' through HC-05 module
 } 
}


