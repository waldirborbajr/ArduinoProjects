#include "LM35.h"

void setup() {
  Serial.begin(9600);
  Serial.println("Serial Connected");

}

void loop() {
  LM35 sensor1(A0); // Sensor connected to pin A0
  double temp = sensor1.read(5); //Returns temperature based on 5 readings (more accurate but slower)

  Serial.print("Temperature Current - ");
  Serial.print(temp);
  Serial.println();

  delay(5000);
}
