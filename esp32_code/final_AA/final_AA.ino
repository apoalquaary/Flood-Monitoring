/*
* Ultrasonic Sensor HC-SR04 and Arduino Tutorial
*
* by ApoAlquaary,
*
*
*/




#include <WiFi.h>
#include "ThingSpeak.h"
const char* ssid     = "SSID";
const char* password = "Password";
const char* host = "192.168.1.54";


// thingspeak

unsigned long ch_no = 000;//Replace with Thingspeak Channel number
const char * write_api = "000"; //Replace with Thingspeak write API
char auth[] = "auth";//Replace with Thingspeak auth

// leds


#define redled 2
#define grnled 4


// buzzer

#define buzzer 15

// time


unsigned long startMillis;
unsigned long currentMillis;
const unsigned long period = 10000;
WiFiClient  client;

// defines pins numbers
const int trigPin = 23;
const int echoPin = 22;
// defines variables
long duration;
int distance;
void setup() {
    pinMode(grnled, OUTPUT);
    pinMode(redled, OUTPUT);
    pinMode(buzzer, OUTPUT);
  Serial.begin(115200);

    // We start by connecting to a WiFi network

    Serial.println();
    Serial.println();
    Serial.print("Connecting to ");
    Serial.println(ssid);

    WiFi.begin(ssid, password);

    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }


    Serial.println("");
    Serial.println("WiFi connected");
    Serial.println("IP address: ");
    Serial.println(WiFi.localIP());

  pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
  pinMode(echoPin, INPUT); // Sets the echoPin as an Input


  ThingSpeak.begin(client);
  startMillis = millis();  //initial start time

}
void loop() {

  // Clears the trigPin
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  // Sets the trigPin on HIGH state for 10 micro seconds
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration = pulseIn(echoPin, HIGH);
  // Calculating the distance
  distance= duration*0.034/2;
  // Prints the distance on the Serial Monitor
  Serial.print("Distance: ");
  Serial.println(distance);


  if(isnan(distance)){
    Serial.println("Failed to read HC");
  }else{
    Serial.print("value: ");
    Serial.print(distance);
    Serial.println("");
    delay(200);
  }

   if (distance <= 9)
  {
    digitalWrite(redled, HIGH);
    digitalWrite(buzzer,HIGH);
    digitalWrite(grnled, LOW);
    delay(200);
  }
  else
  {
    digitalWrite(grnled, HIGH);
    digitalWrite(buzzer,LOW);
    digitalWrite(redled, LOW);
  }
  currentMillis = millis();
  if (currentMillis - startMillis >= period)
  {
    ThingSpeak.setField(1, distance);
    ThingSpeak.writeFields(ch_no, write_api);
    startMillis = currentMillis;
  }

    Serial.print("connecting to ");
    Serial.println(host);


    // Use WiFiClient class to create TCP connections
    WiFiClient client;
    const int httpPort = 80;
    if (!client.connect(host, httpPort)) {
        Serial.println(client.connect(host, httpPort));
        Serial.println("connection failed");
        return;
    }
  Serial.println("well done");


    // This will send the request to the server
 client.print(String("GET http://192.168.1.52/iot/connect.php?") +
                          ("&value=") + distance +
                          " HTTP/1.1\r\n" +
                 "Host: " + host + "\r\n" +
                 "Connection: close\r\n\r\n");
    unsigned long timeout = millis();
    while (client.available() == 0) {
        if (millis() - timeout > 1000) {
            Serial.println(">>> Client Timeout !");
            client.stop();
            return;
        }
    }



    Serial.println();
    Serial.println("closing connection");



}
