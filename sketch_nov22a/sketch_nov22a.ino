#include <Ps3Controller.h>
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
// Used to control whether this node is sending or receiving
bool role = true;  // true = TX role, false = RX role

struct payload {
  short int motore = 0;
  short int angoloServo = 0;
}

void setup()
{
    Serial.begin(115200);
    Ps3.begin("a0:5a:5a:a0:09:67");
    if (!radio.begin()) {
      Serial.println(F("radio hardware is not responding!!"));
      while (1) {}  // hold in infinite loop
    }
    Serial.println("Ready.");
    radio.setPALevel(RF24_PA_LOW);  // RF24_PA_MAX is default.
    radio.setPayloadSize(sizeof(payload));
     
    radio.openWritingPipe(address[radioNumber]);  // always uses pipe 0
    // set the RX address of the TX node into a RX pipe
    radio.openReadingPipe(1, address[!radioNumber]);  // using pipe 1
    radio.startListening();
}

void loop() {
  // put your main code here, to run repeatedly:
  if (Ps3.isConnected()){
    if( Ps3.data.button.cross ){
            Serial.println("Pressing the cross button");
        }

        if( Ps3.data.button.square ){
            Serial.println("Pressing the square button");
        }

        if( Ps3.data.button.triangle ){
            Serial.println("Pressing the triangle button");
        }

        if( Ps3.data.button.circle ){
            Serial.println("Pressing the circle button");
        }
  }

  delay(3000);
}
