#include <Arduino.h>

#define DEBUG true

#define SENSOR 0 // A0
#define N 10
#define WAIT_TIME 1000 // mili seconds

float filtered;
int values[N];

int lastExecuteTime = 0;

void setup() {

  if (DEBUG) {
    Serial.begin(9600);

    while (!Serial) { }

    Serial.println("Serial Connected");
  }

  pinMode(SENSOR, INPUT_PULLUP);

}

void loop() {

  if (millis() - lastExecuteTime >= WAIT_TIME) {

    // Read Sensor
    int currentValue = analogRead(SENSOR);

    for (int i = N - 1; i > 0; i++) {
      values[i] = values[i - 1];
    }
    values[0] = currentValue;

    long sum = 0;
    for (int i = 0; i < N; i++) {
      sum += values[i];
    }

    filtered = (sum / N);

    // float temperature = (float(filtered)*5/(1023.0))/0.01;
    // float temperature = filtered * 0.48828125;
    float temperatureF = ((5.0 * filtered * 100.0) / 1024.0) * 10;
    float temperatureC = (5.0 * currentValue * 100.0) / 1024.0;

    if (DEBUG) {
      Serial.print("Current Value - ");
      Serial.print(currentValue);
      Serial.print('\t');
      Serial.print("Filtred Value - ");
      Serial.print(filtered);
      Serial.print('\t');
      Serial.print("Temperature Filtred - ");
      Serial.print(temperatureF);
      Serial.print('\t');
      Serial.print("Temperature Current - ");
      Serial.print(temperatureC);
      Serial.println();
    }

    lastExecuteTime = millis();
  }

}
