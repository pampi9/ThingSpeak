#include <WiFi101.h>
#include "DHT.h"
#include "ThingSpeak.h"

#define DHTPIN 12
#define DHTTYPE DHT11

DHT myDht(DHTPIN, DHTTYPE);
WiFiClient client;

char ssid[] = "UPC0134688";
char pass[] = "FIPZXSDU";
int status = WL_IDLE_STATUS;

unsigned long myChannelNr = 580191;
const char * myWriteAPIKey = "UO0VSORXEPKNO56Q";

void setup() {
  Serial.begin(9600);
  WiFi.setPins(8, 7, 4, 2);
  WiFi.begin(ssid, pass);
  ThingSpeak.begin(client);
  myDht.begin();
}

void loop() {
  delay(2000);
  
  float h = myDht.readHumidity();
  float t = myDht.readTemperature(true);

  ThingSpeak.setField(1, t);
  ThingSpeak.setField(2, h);
  ThingSpeak.writeFields(myChannelNr, myWriteAPIKey);

  delay(2000);
}
