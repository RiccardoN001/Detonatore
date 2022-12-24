#include <LiquidCrystal_I2C.h>
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

RF24 radio(7,8);

LiquidCrystal_I2C lcd (0x00,16,2);

const byte address[6] = "00001";
const byte connection[6] = "00010";

const int checkLed = 4;
const int led = 2; //Associazione ai pin arduino
const int rele2 = 3;
const int rele3 = 10;
const int rele4 = 5;
const int rele5 = 6;

void setup() {
  boolean confirm = false;
  pinMode(checkLed, OUTPUT);
  pinMode(led, INPUT);//PinMode
  pinMode(rele2, INPUT);
  pinMode(rele3, INPUT);
  pinMode(rele4, INPUT);
  pinMode(rele5, INPUT);
  Serial.begin(9600);
  
  radio.begin();
  radio.openWritingPipe(address);
  radio.openReadingPipe(1,connection);
  radio.setPALevel(RF24_PA_MAX);
  radio.setDataRate(RF24_250KBPS);
  radio.startListening();
   char pong[32] = "";
  while(!confirm){
      radio.read(&pong, sizeof(pong));
      //Serial.println(activation);
      String transData = String(pong);
      if (transData == "ping") {
        Serial.println("Ping arrivato");
        confirm = true;
        delay(200);
    }
  }
    delay(50000);
  
 radio.stopListening();
 
 
  digitalWrite(checkLed,HIGH);// Conferma messaggio mandato
  delay(100);
  digitalWrite(checkLed,LOW);
  
  const char activation[] = "ping"; //Invia un segnale di ping
  radio.write(&activation, sizeof(activation));
  Serial.println("Ping inviato");
  
  radio.startListening();
  
/*char pong[32] = "";  
while(!confirm){
  radio.read(&pong, sizeof(pong));
  //Serial.println(pong);
  String transData = String(pong);
    if (transData == "pong") {
      Serial.println("Pong arrivato");
      digitalWrite(checkLed,HIGH);
      radio.stopListening();
      confirm = true;
    }
 }*/
 radio.stopListening();
  
  
  lcd.begin();
  lcd.setCursor(1,0);
  lcd.print("--BENVENUTO!--");
  lcd.setCursor(6,1);
  lcd.print("by R&T");
  delay(2000);
  lcd.clear();
}

void loop() {
  if(digitalRead(led)==HIGH){
   const char text[] = "trigger1";
   radio.write(&text, sizeof(text));
   delay(200);
   Serial.println("Inviato 1");
   lcd.clear();
   lcd.setCursor(4,0);
   lcd.print("MICCIA 1");
   lcd.setCursor(3,1);
   lcd.print("INNESCATA.");
   delay(3000);
  }
  if(digitalRead(rele2)==HIGH){
   const char text[] = "trigger2";
   radio.write(&text, sizeof(text));
   delay(200);
   Serial.println("Inviato 2");
   lcd.clear();
   lcd.setCursor(4,0);
   lcd.print("MICCIA 2");
   lcd.setCursor(3,1);
   lcd.print("INNESCATA.");
   delay(3000);
  }
  if(digitalRead(rele3)==HIGH){
   const char text[] = "trigger3";
   radio.write(&text, sizeof(text));
   delay(200);
   Serial.println("Inviato 3");
   lcd.clear();
   lcd.setCursor(4,0);
   lcd.print("MICCIA 3");
   lcd.setCursor(3,1);
   lcd.print("INNESCATA.");
   delay(3000);
  }
  if(digitalRead(rele4)==HIGH){
   const char text[] = "trigger4";
   radio.write(&text, sizeof(text));
   delay(200);
   Serial.println("Inviato 4");
   lcd.clear();
   lcd.setCursor(4,0);
   lcd.print("MICCIA 4");
   lcd.setCursor(3,1);
   lcd.print("INNESCATA.");
   delay(3000);
  }
  if(digitalRead(rele5)==HIGH){
   const char text[] = "trigger5";
   radio.write(&text, sizeof(text));
   delay(200);
   Serial.println("Inviato 5");
   lcd.clear();
   lcd.setCursor(4,0);
   lcd.print("MICCIA 5");
   lcd.setCursor(3,1);
   lcd.print("INNESCATA.");
   delay(3000);
  }
}
