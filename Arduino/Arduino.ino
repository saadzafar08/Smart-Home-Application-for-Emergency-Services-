#include <ArduinoJson.h>


#define FLAME 2
int buzzerPin = 12;
int redled = 5;
int greenled = 6;
int smokeA0 = A5;
int sensorThres = 300; //threshold for gas sensor
int pirSensor = 1;
int fireSensor = 0;
int gasSensor = 1;


void setup() {
  Serial.begin(57600);

  pinMode(redled, OUTPUT);
  pinMode(greenled, OUTPUT);
  pinMode(FLAME, INPUT);
 pinMode(buzzerPin, OUTPUT);
  pinMode(smokeA0, INPUT);
  pinMode(13, OUTPUT);
  pinMode(9, INPUT);

}

void loop() {
  //SEND DATA TO THE ESP8266

    delay(1000); // wait 1 sec between each send to the ESP  - when changed to 5 seconds did not work properly
  DynamicJsonBuffer jbuffer;
  JsonObject& root = jbuffer.createObject();

  //read sensor 
  pirSensor = digitalRead(9);
  fireSensor = digitalRead(FLAME);
 gasSensor = analogRead(smokeA0);


  root["flame"] = fireSensor;
  root["gas"] = gasSensor;
  root["motion"] = pirSensor;
    root.printTo(Serial); // sending to the ESP
  Serial.println();
 
  
  //trigger led and buzzer
  if (pirSensor == HIGH)
  {
    tone(buzzerPin, 1000);
    digitalWrite(redled, HIGH);
    digitalWrite(greenled, LOW);
  }
  else
  {
    noTone(buzzerPin);
    digitalWrite(redled, LOW);
    digitalWrite(greenled, HIGH);
  }

delay(1000);

}
