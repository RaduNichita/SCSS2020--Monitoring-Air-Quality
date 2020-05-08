#include <SoftwareSerial.h>
#include <ArduinoJson.h>

int pinMQ135 = A0;
int pinMQ7 = A5;
int pinMQ5 = A4;
int pinMZ = 7;
int pinBuzz = 6;

int val135 = 0;
int val7 = 0;
int val5 = 0;
int valZ = 0;

long laag = 0;
long hoog = 0;
long laagTijd = 0;
long hoogTijd = 0;

void setup() {
  Serial.begin(9600);
  //ArduinoUno.begin(4800);
  pinMode(pinMQ135, INPUT);
  pinMode(pinMQ7, INPUT);
  pinMode(pinMQ5, INPUT);
  pinMode(pinMZ, INPUT);
  pinMode(pinBuzz, OUTPUT);
  digitalWrite(pinBuzz, LOW);
  while (digitalRead(pinMZ) == LOW) {
    ;
  }
  hoog = millis();
}

void loop() {

 while (digitalRead(pinMZ) == HIGH) {
    ;
  }
  laag = millis();
  hoogTijd = laag - hoog;
  while (digitalRead(pinMZ) == LOW) {
    ;
  }
  hoog = millis();
  laagTijd = hoog - laag;
  float CO2 = 2 * laagTijd;
  StaticJsonBuffer<5000> jsonBuffer;
  JsonObject& root = jsonBuffer.createObject();

  val135 = analogRead(pinMQ135);
  val7 = analogRead(pinMQ7);
  val5 = analogRead(pinMQ5);

  if (val135 > 1000 || val7 > 1800 || val5 > 500 || CO2 > 2000) {
    digitalWrite(pinBuzz, HIGH);
    }
 
  root["val 135"] = val135;
  root["val 7"] = val7;
  root["val 5"] = val5;
  root["MH-Z14A"] = CO2;

  if (Serial.available() > 0) {
    root.printTo(Serial);
  }
  delay(3000);
  digitalWrite(pinBuzz, LOW);
}
