#include <DHT.h>
#include <ESP8266WiFi.h>

#define DEBUG true

// replace with your channel’s thingspeak API key,
String apiKey = "55XY3P4MCXA4XXND";
const char* ssid = "NET VIRTUA 336";
const char* password = "am140600";

const char* server = "api.thingspeak.com";
#define DHTPIN 0 // what pin we’re connected to

DHT dht(DHTPIN, DHT11, 15);
WiFiClient client;

void setup() {

  if (DEBUG) {
    
    while (!Serial) { }
    
    Serial.begin(115200);
  }

  delay(10);
  dht.begin();

  WiFi.begin(ssid, password);

  if (DEBUG) {
    Serial.println();
    Serial.println();
    Serial.print("Connecting to ");
    Serial.println(ssid);
  }

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);

    if (DEBUG) {
      Serial.print(".");
    }

  }

  if (DEBUG) {
    Serial.println("");
    Serial.println("WiFi connected");
  }

}

void loop() {

  float h = dht.readHumidity();
  float t = dht.readTemperature();

  if (isnan(h) || isnan(t)) {

    if (DEBUG) {
      Serial.println("Failed to read from DHT sensor!");
    }

    return;
  }

  if (client.connect(server, 80)) { // "184.106.153.149" or api.thingspeak.com
    String postStr = apiKey;
    postStr += "&field1=";
    postStr += String(t);
    postStr += "&field2=";
    postStr += String(h);
    postStr += "\r\n\r\n";

    client.print("POST /update HTTP/1.1\n");
    client.print("Host: api.thingspeak.com\n");
    client.print("Connection: close\n");
    client.print("X-THINGSPEAKAPIKEY: " + apiKey + "\n");
    client.print("Content-Type: application/x-www-form-urlencoded\n");
    client.print("Content-Length: ");
    client.print(postStr.length());
    client.print("\n\n");
    client.print(postStr);

    if (DEBUG) {
      Serial.print("Temperature: ");
      Serial.print(t);
      Serial.print(" degrees Celcius Humidity: ");
      Serial.print(h);
      Serial.println("% send to Thingspeak");
    }
  }
  client.stop();

  if (DEBUG) {
    Serial.println("Waiting…");
  }

  // thingspeak needs minimum 30 sec delay between updates
  delay(40000);
}
