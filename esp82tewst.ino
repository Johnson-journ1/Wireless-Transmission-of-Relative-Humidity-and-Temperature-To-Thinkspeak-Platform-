#include "DHT.h"
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ThingSpeak.h>

const char* ssid = "Galaxy Tab S6 LiteC1E1";
const char* password = "aefh8397";

#define DHTPIN D1
#define DHTTYPE DHT11

WiFiClient client;

unsigned long myChannelNumber= 3210189;
const char* myWriteAPIKey = "44087C22A7VGA9XX";
/*int yellow = D1;
int blue = D2;
*/
DHT dht(DHTPIN, DHTTYPE);

void setup() {
  // put your setup code here, to run once:
/*  pinMode(yellow, OUTPUT);
  pinMode(blue, OUTPUT);*/
  Serial.begin(9600);
  Serial.println("The DHT sensor is running on the ESP.");
  dht.begin();
  delay(10);
  // to give time for the wifi to connect
  WiFi.begin(ssid, password);
  ThingSpeak.begin(client);
  
}

void loop() {
  // put your main code here, to run repeatedly:
/*  digitalWrite(D1, HIGH);
  delay(1000);
  digitalWrite(D1, LOW);
  delay(200);
  digitalWrite(D2, HIGH);
*/
  delay(1000);
  float temperature = dht.readTemperature();
  float humidity = dht.readHumidity();
  if(isnan(temperature)|| isnan(humidity)){
    Serial.println("Error.");
  }else {
    Serial.print("Temperature: ");
    Serial.print(temperature);
    Serial.print("*C| ");
    Serial.print("Humidity: ");
    Serial.print(humidity);
    Serial.println("%");
    Serial.println();
    ThingSpeak.setField(1, temperature);
    ThingSpeak.setField(2, humidity);
    delay(1000);
    ThingSpeak.writeFields(myChannelNumber, myWriteAPIKey);
    delay(100);
  }

}
