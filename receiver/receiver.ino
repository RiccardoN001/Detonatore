#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

RF24 radio(7,8);
const byte address1[6] = "00001";
const byte address2[6] = "00011";

const int rele1 = 2; //Associazione ai pin arduino
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
  digitalWrite(9,HIGH);
  pinMode(9,OUTPUT);
  int countWhile = 0;
  boolean confirm = false;
  pinMode(rele1, OUTPUT);
  pinMode(rele2, OUTPUT);
  pinMode(rele3, OUTPUT);
  pinMode(rele4, OUTPUT);
  pinMode(rele5, OUTPUT);
  Serial.begin(9600);
  radio.begin();
  radio.openWritingPipe(address2);
  radio.openReadingPipe(1,address1);
  radio.setPALevel(RF24_PA_MAX);
  radio.setDataRate(RF24_250KBPS);
  radio.startListening();
  
  char activation[32] = "";
 while(!confirm){
  if(radio.available()){
      radio.read(&activation, sizeof(activation));
      //Serial.println(activation);
      String transData = String(activation);
      if (transData == "ping") {
        Serial.println("Ping arrivato");
        confirm = true;
        delay(200);
      }
   }
  }
  radio.stopListening();
  const char pong[] = "pong"; //Invia un segnale di pong
  radio.write(&pong, sizeof(pong));
  Serial.println("Pong inviato");
  delay(500);
 radio.startListening();      
  }
  
 

void loop() {

  char text[32] = "";

   
  if (radio.available()) {
      radio.read(&text, sizeof(text));
    String transData = String(text);
    if (transData == "trigger1" && count1 <3) {
        digitalWrite(9,LOW);
        digitalWrite(rele1, HIGH);
        Serial.print("Arrivato 1, ");
        Serial.println(count1);
        delay(3000);
        digitalWrite(rele1, LOW);
        count1++;
        }
     if (transData == "trigger2" && count2<3) {
        digitalWrite(rele2, HIGH);
        Serial.print("Arrivato 2, ");
        Serial.println(count2);
        delay(3000);
        digitalWrite(rele2, LOW);
        count2++;
      if (transData == "trigger3" && count3 <3) {
        digitalWrite(rele3, HIGH);
        delay(3000);
        digitalWrite(rele3, LOW);
        count3++;
      }
      if (transData == "trigger4" && count4 <3) {
        digitalWrite(rele4, HIGH);
        delay(3000);
        digitalWrite(rele4, LOW);
        count4++;
      }
      if (transData == "trigger5" && count5 <3) {
        digitalWrite(rele5, HIGH);
        delay(3000);
        digitalWrite(rele5, LOW);
        count5++;
      }
      if (transData == "reset") {
        count1 = 0;
        count2 = 0;
      }
  }
 }
}
