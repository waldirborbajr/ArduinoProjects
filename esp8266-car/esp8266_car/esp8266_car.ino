//Incluindo biblioteca Ultrasonic.h
#include "Ultrasonic.h"
#include <ESP8266WiFi.h>
#include <Servo.h>

// ESP8266 - NodeMCU - Pins Mapping
#define D0    16
#define D1    5
#define D2    4
#define D3    0
#define D4    2
#define D5    14
#define D6    12
#define D7    13
#define D8    15
#define D9    3  // RX
#define D10   1  // TX
#define SD3   10
#define SD2   9

// H-bridge - L298N

int enA =  5; /* D1 -> Motor-A Enable */
int in1 =  4; /* D2 -> IN1  */
int in2 =  0; /* D3 -> IN2  */

int enB = 12; /* D6 -> Motor-B Enable */
int in3 = 15; /* D8 -> IN3   */
int in4 = 13; /* D7 -> IN4   */

/* motor speed */
int speedMotor_A = 200;
int speedMotor_B = 200;


// WiFi
const char* ssid = "OIVO-0DEC-ANONYMOUS";
const char* password = "C6622E0DEC!HACKER#WORLD";


// HSR-04

// Trigger , Echo
Ultrasonic SensorUltrassonico1(2, 14); /* D4 , D5 */

long Microsegundos = 0;// Variável para armazenar o valor do tempo da reflexão do som refletido pelo objeto fornecido pela biblioteca do sensor
float DistanciaemCM = 0;// Variável para armazenar o valor da distância a ser convertido por uma função da própria bilbioteca do sensor


long previousMillis = 0;        // Variável de controle do tempo
long interval = 7000;     // Tempo em ms do intervalo a ser executado


Servo servoMotor;

const int pinServo = 16;
const int pulsoMax = 550;
const int pulsoMin = 2450;

int pos = 0;


void setup() {

  Serial.begin(115200);// Inicia a comunicação seria com velocidade de 115200 bits por segundo

  delay(10);

  // Connect to WiFi network
  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");

  Serial.println(WiFi.localIP());

  /* initialize motor enable pins as output */
  pinMode(enA, OUTPUT);
  //  pinMode(enB, OUTPUT);

  /* initialize motor control pins as output */
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);

  delay(3000);// Tempo de espera para inicialização (para dar tempo de por o robô no chão)


  Serial.println("Initializing Servo");
  servoMotor.attach(pinServo);

  Serial.print("Starting engines...");
}


/********************************************* FORWARD *****************************************************/
void MotorForward(void) {

  analogWrite( enA, speedMotor_A);
  analogWrite( enB, speedMotor_B);

  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
}

/********************************************* BACKWARD *****************************************************/
void MotorBackward(void) {
  digitalWrite(enA, HIGH);
  digitalWrite(enB, HIGH);

  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);

  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);
}

/********************************************* TURN LEFT *****************************************************/
void TurnLeft(void)
{
  analogWrite( enA, speedMotor_A);

  digitalWrite(enB, HIGH);
  digitalWrite(enA, HIGH);

  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in4, LOW);
}

/********************************************* TURN RIGHT *****************************************************/
void TurnRight(void)
{
  analogWrite( enB, speedMotor_B);

  digitalWrite(enA, HIGH);
  digitalWrite(enB, HIGH);

  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
}

/********************************************* STOP *****************************************************/
void MotorStop(void)
{
  digitalWrite(enB, LOW);
  digitalWrite(enA, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in4, LOW);
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
}

void Motor_Test(void) {
  Serial.println("MotorForward()");
  MotorForward();

  delay(5000);

  Serial.println("MotorStop()");
  MotorStop();

  delay(10000);

  Serial.println("MotorBackward()");
  MotorBackward();

  delay(5000);

  Serial.println("MotorStop()");
  MotorStop();

  delay(10000);

  Serial.println("TurnLeft()");
  TurnLeft();

  delay(5000);

  Serial.println("MotorStop()");
  MotorStop();

  delay(10000);

  Serial.println("TurnRight()");
  TurnRight();

  delay(5000);

  Serial.println("MotorStop()");
  MotorStop();

  delay(10000);

}

void HSR04_Test(void) {
  //Convertendo a distância em CM e lendo o sensor
  DistanciaemCM = SensorUltrassonico1.convert(SensorUltrassonico1.timing(), Ultrasonic::CM);

  Serial.print(DistanciaemCM);
  Serial.println(" cm");
}

void Servo_Test(void) {
  servoMotor.attach(pinServo);
  Serial.println("0");
  servoMotor.write(0);
  servoMotor.detach();
  delay(5000);

  servoMotor.attach(pinServo);
  Serial.println("45");
  servoMotor.write(45);
  servoMotor.detach();
  delay(5000);

  servoMotor.attach(pinServo);
  Serial.println("90");
  servoMotor.write(90);
  servoMotor.detach();
  delay(5000);

  servoMotor.attach(pinServo);
  Serial.println("135");
  servoMotor.write(135);
  servoMotor.detach();
  delay(5000);

  servoMotor.attach(pinServo);
  Serial.println("180");
  servoMotor.write(180);
  servoMotor.detach();
  delay(5000);
}

void loop() {

  unsigned long currentMillis = millis();

  if (currentMillis - previousMillis > interval) {
    previousMillis = currentMillis;

    Motor_Test();
  }

}

