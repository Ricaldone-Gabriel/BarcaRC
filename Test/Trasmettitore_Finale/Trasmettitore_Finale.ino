#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>  
#define CSN 13 
#define CE 12   
/*
Commento qui perchè è più figo,
Gabi devi riuscire a gestire la trasmisisone dei dati dal UMV al tostapane e dal tostapane al UMV in half-duplex
*/

RF24 radio(CE,CSN); // CE, CSN

const byte address[6] = "C4J5D";

void setup() {
  Serial.begin(115200);
  Serial.println("acceso");
  radio.begin();
  //radio.powerUp();
  radio.openWritingPipe(address);
  radio.setPALevel(RF24_PA_MIN);
  radio.stopListening();
}

void loop() {
  const String test = "Test";
  radio.write(&test, sizeof(String));
}
