/*This is bluetooth receiver on top of AGV uses Arduino UNO
 * this receives the bluetooth data from Cental_Master
 * It Translates bluetooth data to IR signal and transmits to AGV
 * Arduino IRremote library is used to transmit IR data
 * NEC protocal is used here as AGV can able to receive NEC protocal data

*/


//include IRremote library for IR communication
#include <IRremote.h>
#include <IRremoteInt.h>
IRsend irsend;
//defining Line staus LEDs for indicating which line the AGV follows
int line1_status=8;
int line2_status=9;
int line3_status=10;

void setup() {
Serial.begin(9600);// Default communication rate of the Bluetooth module
//declaring Line status LEDs as output
pinMode(line1_status, OUTPUT); 
pinMode(line2_status,OUTPUT);
pinMode(line3_status,OUTPUT);
}
 
void loop() {

  //checking for serial data availability
if(Serial.available()>0)
   {    
      char data= Serial.read(); // reading the data from the bluetooth module
      switch(data)
      {
        //when character 'a' recevied then it translates the character into IR packet based on NEC protocol
        case 'a': 
               digitalWrite(line1_status, HIGH);
               Serial.println("line1 is active");
               delay(50);
               irsend.sendNEC(0x00fd20df, 32);// sends IR packet '0x00fd20df'
               delay(500);
               digitalWrite(line1_status,LOW);
               break;       
      //when character 'a' recevied then it translates the character into IR packet based on NEC protocol
       case 'c': 
               digitalWrite(line2_status, HIGH);
               Serial.println("line2 is active");
               delay(50);
               irsend.sendNEC(0x00fda05f, 32);//sends IR packet '0x00fda05f'
               delay(500); 
               digitalWrite(line2_status,LOW);
               break; 
       //when character 'a' recevied then it translates the character into IR packet based on NEC protocol
       case 'e':
               digitalWrite(line3_status, HIGH);
               Serial.println("line3 is active");
               delay(50);
               irsend.sendNEC(0x00fd609f, 32);//sends IR packet '0x00fd609f'
               delay(500); 
               digitalWrite(line3_status,LOW);
               break; 
       default : 
               //
                break;
      }
      Serial.println(data);
   }
   delay(50);
}










