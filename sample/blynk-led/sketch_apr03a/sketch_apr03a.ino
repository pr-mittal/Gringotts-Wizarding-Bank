#include <BlynkSimpleStream.h>
 
 // You should get Auth Token in the Blynk App.
 // Go to the Project Settings (nut icon).
 char auth[] = "KmppDTbndQVHXkDaGh1uh5oiBCNQcGZu";
 
 void setup()
 {
   Serial.begin(9600);
   Blynk.begin(auth, Serial);
   pinMode(10, OUTPUT);
   pinMode(11, OUTPUT);
   pinMode(12, OUTPUT);
   pinMode(13, OUTPUT);
 }
 void loop()
 {
   Blynk.run();
 }
