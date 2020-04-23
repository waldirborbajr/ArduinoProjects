#include <ESP8266WiFi.h>

#define DEBUG false

// number of analog samples to take per reading
#define NUM_SAMPLES 10
#define ANALOGPIN 2 // D4

int sum = 0;                    // sum of samples taken
unsigned char sample_count = 0; // current sample number
float voltage = 0.0;            // calculated voltage

// replace with your channel’s thingspeak API key,
String apiKey = "3XAOJRRPZIY94JPW";
const char* ssid = "NET VIRTUA 336";
const char* password = "am140600";

const char* server = "api.thingspeak.com";
#define DHTPIN 2 // what pin we’re connected to

WiFiClient client;

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

  // take a number of analog samples and add them up
  while (sample_count < NUM_SAMPLES) {
    sum += analogRead(ANALOGPIN);
    sample_count++;
    delay(10);
  }

  // calculate the voltage
  // use 5.0 for a 5.0V ADC reference voltage
  // 5.015V is the calibrated reference voltage
  voltage = ((float)sum / (float)NUM_SAMPLES * 5.015) / 1024.0;

  if (client.connect(server, 80)) { // "184.106.153.149" or api.thingspeak.com
    String postStr = apiKey;
    postStr += "&field1=";
    postStr += String(voltage);
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

  sample_count = 0;
  sum = 0;

  // thingspeak needs minimum 15 sec delay between updates
  delay(20000);
}
