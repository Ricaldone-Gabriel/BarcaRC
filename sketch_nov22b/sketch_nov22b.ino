#include <Ps3Controller.h>
#include <ESP32Servo.h>
#include <SPI.h>
#include "RF24.h"

#define CE_PIN 5
#define CSN_PIN 13
// instantiate an object for the nRF24L01 transceiver
Servo Servo1, Servo2, ESC;
RF24 radio(CE_PIN, CSN_PIN);

//a0:5a:5a:a0:09:67
//DualShock 3 CECHZC2UA1
//Baud a 115200

// Let these addresses be used for the pair
uint8_t address[][6] = { "1Node", "2Node" };
// It is very helpful to think of an address as a path instead of as
// an identifying device destination
bool radioNumber = 1;  // 0 uses address[0] to transmit, 1 uses address[1] to transmit

short int payload[2] = {0,90}; //0 = Potenza motore, 1 angolo servo

void setup()
{
    Serial.begin(115200);
    Ps3.begin("a0:5a:5a:a0:09:67");

    Servo1.attach(2);
    Servo2.attach(3);
    ESC.attach(6,1000,2000);
    
    if (!radio.begin()) {
      Serial.println(F("radio hardware is not responding!!"));
      while (1) {}  // hold in infinite loop
    }
    Serial.println("Ready.");
    radio.setPALevel(RF24_PA_LOW);  // RF24_PA_MAX is default.
    radio.setPayloadSize(sizeof(payload));
     
    radio.openWritingPipe(address[radioNumber]); 
    // set the RX address of the TX node into a RX pipe
    radio.openReadingPipe(1, address[!radioNumber]); 
    radio.startListening();

    
}

void loop() {
  if(radio.available()) {
    Serial.println(payload[0]);
    Serial.println(payload[1]);
    radio.read(&payload,sizeof(payload));
    Servo1.write(payload[1]);
    Servo2.write(payload[1]);
    ESC.write(payload[0]);
  }
}
