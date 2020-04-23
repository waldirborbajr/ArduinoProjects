const int sensor1 = 6;
const int ledPin = 13;

int sensor1Status;

// Maquina de Status
// -----------------
// LOW  - HIGH -- 0,1 - Fechado
// HIGH - LOW  -- 1,0 - Aberto
// LOW  - LOW  -- 0,0 - *Erro*

void setup() {

  pinMode(sensor1, INPUT);
  pinMode(ledPin, OUTPUT);

  // Read initial sensor status
  sensor1Status = digitalRead(sensor1);

  digitalWrite(sensor1, HIGH);

  Serial.begin(115200);

  Serial.print("Initial Status: ");
  Serial.println(sensor1Status);

}

void loop() {

  if (digitalRead(sensor1) == LOW) {
    digitalWrite(ledPin, LOW);
    Serial.println(digitalRead(sensor1));
    Serial.println("Your Door is Closed");
  } else {
    digitalWrite(ledPin, HIGH);
    Serial.println(digitalRead(sensor1));
    Serial.println("Your Door is Open");
  }

  delay(2000);

}
