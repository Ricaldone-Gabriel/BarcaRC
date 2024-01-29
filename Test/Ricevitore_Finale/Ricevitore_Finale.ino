#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#define CSN 13 
#define CE 12   
RF24 radio(CE,CSN); // CE, CSN

const byte address[6] = "C4J5D";

void setup() {
  Serial.begin(115200);
  Serial.println("acceso");
  
  radio.begin();
  radio.openReadingPipe(0, address);
  //radio.powerDown();
  //radio.powerUp();
  radio.setPALevel(RF24_PA_MIN);
  radio.startListening();
}

void loop() {
  String test;
  if (radio.available()) {
    radio.read(&test, sizeof(String));
    Serial.println(test);
  }
}
