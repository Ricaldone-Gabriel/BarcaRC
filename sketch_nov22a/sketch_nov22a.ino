#include <Ps3Controller.h>
#include "RF24.h"

#define CE_PIN 5
#define CSN_PIN 13
// instantiate an object for the nRF24L01 transceiver
RF24 radio(CE_PIN, CSN_PIN);

//a0:5a:5a:a0:09:67
//DualShock 3 CECHZC2UA1
//Baud a 115200

// Let these addresses be used for the pair
uint8_t address[][6] = { "1Node", "2Node" };
// It is very helpful to think of an address as a path instead of as
// an identifying device destination
bool radioNumber = 0;  // 0 uses address[0] to transmit, 1 uses address[1] to transmit

short int payload[2] = {0,0}; //0 = Potenza motore, 1 angolo servo

void setup()
{
    Serial.begin(115200);
    Ps3.begin("a0:5a:5a:a0:09:67");
    /*if (!radio.begin()) {
      Serial.println(F("radio hardware is not responding!!"));
      while (1) {}  // hold in infinite loop
    }
    Serial.println("Ready.");
    radio.setPALevel(RF24_PA_LOW);  // RF24_PA_MAX is default.
    radio.setPayloadSize(sizeof(payload));
     
    radio.openWritingPipe(address[radioNumber]);  // always uses pipe 0
    // set the RX address of the TX node into a RX pipe
    radio.openReadingPipe(1, address[!radioNumber]);  // using pipe 1
    radio.startListening();*/
}

void loop() {
  // put your main code here, to run repeatedly:
  if (Ps3.isConnected()){
    if( abs(Ps3.event.analog_changed.stick.lx) + abs(Ps3.event.analog_changed.stick.ly) > 2 ){
       Serial.print("Moved the left stick:");
       Serial.print(" x="); Serial.print(Ps3.data.analog.stick.lx, DEC);
       Serial.print(" y="); Serial.print(Ps3.data.analog.stick.ly, DEC);
       Serial.println();
    }

    if( abs(Ps3.event.analog_changed.stick.rx) + abs(Ps3.event.analog_changed.stick.ry) > 2 ){
       Serial.print("Moved the right stick:");
       Serial.print(" x="); Serial.print(Ps3.data.analog.stick.rx, DEC);
       Serial.print(" y="); Serial.print(Ps3.data.analog.stick.ry, DEC);
       Serial.println();
   }
  }
}
