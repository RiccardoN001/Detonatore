#include <LiquidCrystal_I2C.h>
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

RF24 radio(7,8);

LiquidCrystal_I2C lcd (0x00,16,2);

const byte address1[6] = "00001";
const byte address2[6] = "00011";

const int genSwitch = A5;
const int checkLed = 4;
const int led = 2; //Associazione ai pin arduino
const int rele2 = 3;
const int rele3 = A0;
const int rele4 = A1;
const int rele5 = 6;

void setup() {
  boolean confirm = false;
  int countWhile = 0;
  pinMode(checkLed, OUTPUT);
  pinMode(led, INPUT);//PinMode
  pinMode(rele2, INPUT);
  pinMode(rele3, INPUT);
  pinMode(rele4, INPUT);
  pinMode(rele5, INPUT);
  pinMode(genSwitch,INPUT);
  Serial.begin(9600);
  
  radio.begin();
  radio.openWritingPipe(address1);
  radio.openReadingPipe(1,address2);
  radio.setPALevel(RF24_PA_MAX);
  radio.setDataRate(RF24_250KBPS);
  radio.stopListening();
  
  digitalWrite(checkLed,HIGH);// Conferma messaggio mandato
  delay(100);
  digitalWrite(checkLed,LOW);
  
  radio.write("ping", sizeof("ping"));
  Serial.println("Ping inviato");
  delay(100);
  radio.startListening();
  
char pong[32] = "";  
while(!confirm){
  radio.read(&pong, sizeof(pong));
  String transData = String(pong);
  countWhile++;
    if (transData == "pong") {
      Serial.println("Pong arrivato");
      digitalWrite(checkLed,HIGH);
      radio.stopListening();
      confirm = true;
    }
    else if(countWhile > 10000){
      digitalWrite(checkLed,HIGH);
      break;
    }
 }
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

 if(digitalRead(genSwitch)==HIGH){ //DA SISTEMARE
  if(digitalRead(led)==HIGH){
   radio.write("trigger1", sizeof("trigger1"));
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
   radio.write("trigger2", sizeof("trigger2"));
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
   radio.write("trigger3", sizeof("trigger3"));
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
   radio.write("trigger4", sizeof("trigger4"));
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
   radio.write("trigger5", sizeof("trigger5"));
   delay(200);
   Serial.println("Inviato 5");
   lcd.clear();
   lcd.setCursor(4,0);
   lcd.print("MICCIA 5");
   lcd.setCursor(3,1);
   lcd.print("INNESCATA.");
   delay(3000);
  }
  if(digitalRead(led)==HIGH && digitalRead(rele2)==HIGH){
   radio.write("reset", sizeof("reset"));
   delay(200);
   Serial.println("Inviato reset");
   lcd.clear();
   lcd.setCursor(4,0);
   lcd.print("MICCIA 5");
   lcd.setCursor(3,1);
   lcd.print("INNESCATA.");
   delay(3000);
  }
 }
}
