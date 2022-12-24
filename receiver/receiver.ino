#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

RF24 radio(7,8);
const byte address[6] = "00001";
const byte connection[6] = "00010";

const int led = 2; //Associazione ai pin arduino
const int rele2 = 3;
const int rele3 = 4;
const int rele4 = 5;
const int rele5 = 6;

int count1 = 0; //Contatore per innescare una sola volta
int count2 = 0;
int count3 = 0;
int count4 = 0;
int count5 = 0;

void setup() {

  boolean confirm = false;
  pinMode(led, OUTPUT);
  pinMode(rele2, OUTPUT);
  pinMode(rele3, OUTPUT);
  pinMode(rele4, OUTPUT);
  pinMode(rele5, OUTPUT);
  Serial.begin(9600);
  radio.begin();
  radio.openReadingPipe(0,address);
  radio.openWritingPipe(connection);
  radio.setPALevel(RF24_PA_MAX);
  radio.setDataRate(RF24_250KBPS);
  radio.stopListening();
  const char pong[] = "pong"; //Invia un segnale di pong
  radio.write(&pong, sizeof(pong));
  Serial.println("Pong inviato");
  delay(4000);
  radio.startListening();
  
  char activation[32] = "";
  while(!confirm){
      radio.read(&activation, sizeof(activation));
      //Serial.println(activation);
      String transData = String(activation);
      if (transData == "ping") {
        Serial.println("Ping arrivato");
        confirm = true;
        delay(200);
    }
  }
  /*Serial.println("Esco dal while");
  radio.stopListening();
  delay(200);
  const char pong[] = "pong"; //Invia un segnale di pong
  radio.write(&pong, sizeof(pong));
  Serial.println("Pong inviato");
  delay(500);      
  radio.startListening();*/
}
  

void loop() {

  char text[32] = "";

   
  if (radio.available()) {
      radio.read(&text, sizeof(text));
    String transData = String(text);
    if (transData == "trigger1" && count1 <2) {
        digitalWrite(led, HIGH);
        delay(3000);
        digitalWrite(led, LOW);
        count1++;
      }
     if (transData == "trigger2" && count2<2) {
        digitalWrite(rele2, HIGH);
        delay(3000);
        digitalWrite(rele2, LOW);
        count2++;
      }
      if (transData == "trigger3" && count3 <2) {
        digitalWrite(rele3, HIGH);
        delay(3000);
        digitalWrite(rele3, LOW);
        count3++;
      }
      if (transData == "trigger4" && count4 <2) {
        digitalWrite(rele4, HIGH);
        delay(3000);
        digitalWrite(rele4, LOW);
        count4++;
      }
      if (transData == "trigger5" && count5 <2) {
        digitalWrite(rele5, HIGH);
        delay(3000);
        digitalWrite(rele5, LOW);
        count5++;
      }
  }
}
