#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#include <Servo.h>
Servo ServoL1, ServoL2, ServoR1, ServoR2,ESC;
RF24 radio(7,8); // CE, CSN
int r;

void rollio(int x);
void beccheggio(int x);
void motore(int x);

const byte address[6] = "C4J5D";
struct dati {
    short int angoliServo[2] = {0,0};
    short int motore = 0;
};

dati datiRicevuti;

void setup() {
  Serial.begin(9600);
  Serial.println("acceso");
  
  ServoL1.attach(2);
  ServoL2.attach(3);
  ServoR1.attach(4);
  ServoR2.attach(5);
  ESC.attach(6,1000,2000);
  
  radio.begin();
  radio.openReadingPipe(0, address);
  radio.powerDown();
  radio.powerUp();
  radio.setPALevel(RF24_PA_MIN);
  delay(10);
  radio.startListening();
}

void loop() {
  Serial.println(datiRicevuti.angoliServo[0]);
  Serial.println(datiRicevuti.angoliServo[1]);
  
  if (radio.available()) {
    radio.read(&datiRicevuti, sizeof(dati));
    rollio(datiRicevuti.angoliServo[0]);
    beccheggio(datiRicevuti.angoliServo[1]);
    motore(datiRicevuti.motore);
  }
}

void rollio(int x) {
  r = 180-x;  
  ServoL2.write(x);
  ServoR2.write(r);
}

void beccheggio(int x) {
  ServoL1.write(x);
  ServoR1.write(x);
}

void motore(int x) {
  ESC.write(x);
}
