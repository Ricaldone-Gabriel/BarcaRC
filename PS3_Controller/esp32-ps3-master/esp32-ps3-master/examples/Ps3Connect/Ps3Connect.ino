#include <Ps3Controller.h>

void setup()
{
    Serial.begin(115200);
    Ps3.begin("a0:5a:5a:a0:09:67");
    Serial.println("Ready.");
}

void loop()
{
  if (Ps3.isConnected()){
    Serial.println("Connected!");
  }

  delay(3000);
}
