#include <IRremote.h>
const int RECV_PIN = 17;

IRrecv irrecv(RECV_PIN);
decode_results results;

void setup() {
  Serial.begin(9600);
  irrecv.enableIRIn();
  
}

void loop() {
  if (irrecv.decode(&results)) {
    Serial.println(results.value, HEX);
     irrecv.resume();
  }

  if (results.value == 0x00fd20df) { //VolumeHigh
   Serial.println("line1");
   Serial.println("turn left");
   Serial.println("follow line");
   delay(5000);
    results.value = 0x00000000;
   
  }

  if (results.value == 0x00fda05f) { //VolumeDown
      Serial.println("line2");
       Serial.println("forward");
   Serial.println("follow line");
    results.value = 0x00000000;
   
  }

  if (results.value == 0x00fd609f) { //Select
     Serial.println("line3");
      Serial.println("turn right");
   Serial.println("follow line");
    results.value = 0x00000000;
   
  }

}

