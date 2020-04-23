
// Motor A
const int enA = 9; // PWM
const int in1 = 8;
const int in2 = 7;

// Motor B
const int enB = 3; // PWM
const int in3 = 5;
const int in4 = 4;

void setup() {

  // Motor A
  pinMode(enA,  OUTPUT);
  pinMode (in1, OUTPUT);
  pinMode (in2, OUTPUT);

  // Motor B
  pinMode(enB,  OUTPUT);
  pinMode (in3, OUTPUT);
  pinMode (in4, OUTPUT);

}

void demoMode() {

  // Turn on motor A

  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);

  analogWrite(enA, 100);

  // Turn on motor B

  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);

  analogWrite(enB, 100);

  delay(2000);

  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);

  delay(2000);

  // Turn off motors

  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in4, LOW);

}

void loop() {

  demoMode();

}
