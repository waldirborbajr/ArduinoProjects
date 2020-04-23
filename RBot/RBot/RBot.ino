//defining Pins names for the code

// Back Motor
int pwmB = 13; int forwardB = 12; int reverseB = 11; // orange // brown // green

// Front Motor
int pwmF = 10; int forwardF = 9; int reverseF = 8;

int encoderValue = 0;
void count(void);

void setup() {
  Serial.begin(9600);
  pinMode(21, INPUT);
  attachInterrupt(2, count, FALLING);

  encoderValue = 0;
}

void loop() {
  // Back Motor
  digitalWrite(pwmB, HIGH);
  digitalWrite(forwardB, LOW);
  analogWrite(reverseB, 140);

  // Front Motor
  digitalWrite(pwmF, HIGH);
  digitalWrite(forwardF, LOW);
  analogWrite(reverseF, 140);

  Serial.print("Starting\n");

  delay(3000);

  Serial.print("Encoder Value=");

  Serial.println(encoderValue);

  while (1) {

    // to print encoder value on the screen Serial.print("Encoder Value="); Serial.println(encoderValue); //Setting value of encoder
    //defining the while statement condition if(encoderValue<5000)

    break; // loop will break as soon as encoder value reaches 5000 or above digitalWrite(forward,1);

    digitalWrite(reverseB, LOW);
    analogWrite(pwmB, 150);

    digitalWrite(reverseF, LOW);
    analogWrite(pwmF, 150);

  }

  digitalWrite(forwardB, HIGH);
  digitalWrite(reverseB, HIGH);
  analogWrite(pwmB, 255);

  digitalWrite(forwardF, HIGH);
  digitalWrite(reverseF, HIGH);
  analogWrite(pwmF, 255);
}

void count() {
  encoderValue++;
}

