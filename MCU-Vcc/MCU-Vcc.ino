#include <ESP8266WiFi.h>

#define DEBUG false

#define ANALOGPIN 2 // D4
#define resistor 6.9
#define BATTERY_VOLTS 5.0

float capacity = 0, value, voltage = 0.0, current, dischargingTime = 0;

// replace with your channel’s thingspeak API key,
String apiKey = "3XAOJRRPZIY94JPW";
const char* ssid = "NET VIRTUA 336";
const char* password = "am140600";

const char* server = "api.thingspeak.com";
#define DHTPIN 2 // what pin we’re connected to

WiFiClient client;

void measure (void) {

  value = analogRead(ANALOGPIN);

  voltage = value * (1023.0 * BATTERY_VOLTS);

  current = (voltage / resistor);

  capacity = capacity + (current / 3600);

  dischargingTime++;

  if (DEBUG) {
    Serial.print("Voltage= ");
    Serial.print(voltage);

    Serial.print("V Current= ");
    Serial.print(current);

    Serial.print("A Capacity= ");
    Serial.print(capacity);
    Serial.print("Ah ");

    Serial.print("Discharging time= ");
    Serial.print(dischargingTime);
    Serial.print("s ");

    Serial.print("\n");
  }

}

void setup() {

  if (DEBUG) {
    Serial.begin(115200);
  }

  delay(10);

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

  measure();

  if (client.connect(server, 80)) { // "184.106.153.149" or api.thingspeak.com
    String postStr = apiKey;
    postStr += "&field1=";
    postStr += String(voltage);
    postStr += "&field2=";
    postStr += String(current);
    postStr += "&field3=";
    postStr += String(capacity);
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
      Serial.print(voltage * 11.132);
      Serial.println (" V");
      Serial.println("% send to Thingspeak");
    }
  }
  client.stop();

  if (DEBUG) {
    Serial.println("Waiting…");
  }

  // thingspeak needs minimum 15 sec delay between updates
  delay(20000);
}
