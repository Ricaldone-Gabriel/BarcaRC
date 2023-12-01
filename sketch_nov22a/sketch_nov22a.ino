#include <Ps3Controller.h>
//a0:5a:5a:a0:09:67
//DualShock 3 CECHZC2UA1
void setup()
{
    Serial.begin(115200);
    Ps3.begin("a0:5a:5a:a0:09:67");
    Serial.println("Ready.");
}

void loop() {
  // put your main code here, to run repeatedly:
  if (Ps3.isConnected()){
    Serial.println("Connected!");
  }

  delay(3000);
}
