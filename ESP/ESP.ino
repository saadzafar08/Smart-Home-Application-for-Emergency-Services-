#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <FirebaseArduino.h>
#include <ArduinoJson.h>
// Set these to run example.
#define FIREBASE_HOST "smart-home-application-6e576-default-rtdb.asia-southeast1.firebasedatabase.app"
#define FIREBASE_AUTH "mBeNjHb0L1CETOuSr6MoxeQ0MKyeUovFRD1mtIOM"
#define WIFI_SSID "TELENOR 4G 8841"
#define WIFI_PASSWORD "90316157" 

/*#define EAP_ANONYMOUS_IDENTITY "" //anonymous@example.com, or you can use also nickname@example.com
#define EAP_IDENTITY "01-134182-015@student.bahria.edu.pk" //nickname@example.com, at some organizations should work nickname only without realm, but it is not recommended
#define EAP_PASSWORD "fsk1199" //password for eduroam account*/


void setup() {
  Serial.begin(57600);

  // connect to wifi.
 WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
  Serial.println("");
  Serial.print("connected: ");
  Serial.println(WiFi.localIP());


  Firebase.begin(FIREBASE_HOST);
}

int n = 0;
void loop() {
  bool StringReady;
  String json;

  //ACCEPT DATA FROM THE ARDUINO
  while (Serial.available()) { // listen for serial data from the Arduino Atmega328
    json = Serial.readString();
    StringReady = true;
  }

  if (StringReady) {
    StaticJsonBuffer<256> jsonBuffer;  // preallocated memory to store the JsonObject max 200 bytes
    JsonObject& root = jsonBuffer.parseObject(json); // turning the string into JSON data

    if (!root.success()) {
      //Serial.println("parseObject() failed");
      return ;
    }
//data received from arduino
    String motionData = root["motion"]; 
    String flameData = root["flame"]; 
    String gasData = root["gas"];
    //Serial.println();
    //Serial.println(temperatureMessage);
    // Serial.println();
    root.remove("motion");// remove the temp field from the JSON root object so I can reuse the root object to send back data
    // if the serial console is open it will print: 22:40:32.989 -> 21oC : temperature recieved from Arduino at ESP
  
 
 // set value

  Firebase.setString("motionval", motionData);
  // handle error
  if (Firebase.failed()) {
      Serial.print("setting /motion failed:");
      Serial.println(Firebase.error());  
      return;
  }
  delay(10); 
   Firebase.setString("flame", flameData);
  // handle error
  if (Firebase.failed()) {
      Serial.print("setting /flame failed:");
      Serial.println(Firebase.error());  
      return;
  }
  delay(10); 
   Firebase.setString("gas", gasData);
  // handle error
  if (Firebase.failed()) {
      Serial.print("setting /gas failed:");
      Serial.println(Firebase.error());  
      return;
  }
  delay(10);
  
// get value 
  Serial.print("motionval: ");
  Serial.println(Firebase.getString("motionval"));

delay(10); 
  

  }
}
