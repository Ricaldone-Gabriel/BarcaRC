#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
RF24 radio(7,8); // CE, CSN

const byte address[6] = "C4J5D";
struct dati {
    short int angoliServo[2] = {0,0};
    short int motore = 0;
};

dati datiTrasmessi;
int valY, valX;
int valPotenziometro1,  valPotenziometro2;
int mediaPotenziometro;

void setup() {
  Serial.begin(9600);
  Serial.println("acceso");
  radio.begin();
  radio.powerUp();
  radio.openWritingPipe(address);
  radio.setPALevel(RF24_PA_MIN);
  radio.stopListening();
}

void loop() {
  valX = analogRead(A0);
  valY = analogRead(A1);
  
  datiTrasmessi.angoliServo[0] = map(valX,0,1023,70,110);
  if (datiTrasmessi.angoliServo[0] > 110) {
    datiTrasmessi.angoliServo[0] = 110;
  } else if (datiTrasmessi.angoliServo[0] < 70) {
    datiTrasmessi.angoliServo[0] = 70;
  }
  
  datiTrasmessi.angoliServo[1] = map(valY,0,1023,70,110);
  if (datiTrasmessi.angoliServo[1] > 110) {
    datiTrasmessi.angoliServo[1] = 110;
  } else if (datiTrasmessi.angoliServo[1] < 70) {
    datiTrasmessi.angoliServo[1] = 70;
  }
  
  Serial.println(datiTrasmessi.angoliServo[0]);
  Serial.println(datiTrasmessi.angoliServo[1]);
  
  valPotenziometro1 = analogRead(A2);
  valPotenziometro2 = analogRead(A3);
  mediaPotenziometro = (valPotenziometro1 + valPotenziometro2) / 2;
  
  datiTrasmessi.motore = map(mediaPotenziometro,0,1023,0,180);
  if (datiTrasmessi.motore > 180) {
    datiTrasmessi.motore = 180;
  } else if (datiTrasmessi.motore < 0){
    datiTrasmessi.motore = 0;
  }
  radio.write(&datiTrasmessi, sizeof(datiTrasmessi));
}
