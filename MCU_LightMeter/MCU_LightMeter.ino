#define DEBUG true

#define SENSOR 2 // D4
#define N 10
#define WAIT_TIME 1000 // 1000ms

int filtered;
int values[N];

int lastExecuteTime = 0;

void setup() {

  if (DEBUG) {
    Serial.begin(115200);

    while (!Serial) { }

    Serial.println("Serial Connected");
  }

  pinMode(SENSOR, INPUT);

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

    filtered = sum / N;

    if (DEBUG) {
      Serial.print(currentValue);
      Serial .print('\t');
      Serial.println(filtered);
    }

    lastExecuteTime = millis();
  }

}
