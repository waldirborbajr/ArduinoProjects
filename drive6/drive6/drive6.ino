//defining Pins names for the code

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

    digitalWrite(reverseF, LOW);
    analogWrite(pwmF, 150);

  }

  digitalWrite(forwardF, HIGH);
  digitalWrite(reverseF, HIGH);
  analogWrite(pwmF, 255);
}

void count() {
  encoderValue++;
}

