//Programa : Modulo Bluetooth HC-06 - Leds
//Autor : Adilson Thomsen

//Armazena o caracter recebido
char buf;

void setup()
{
  //Define os pinos dos leds como saida
  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);
  Serial.begin(9600);
}

void loop()
{
  while (Serial.available() > 0)
  {
    buf = Serial.read();
    //Caso seja recebido R, acende o led vermelho
    if (buf == 'R')
    {
      digitalWrite(3, HIGH);
      Serial.println("LED Vermelho ligado !");
    }
    //Caso seja recebido G, acende o led verde
    if (buf == 'G')
    {
      digitalWrite(4, HIGH);
      Serial.println("LED Verde ligado !");
    }
    //Caso seja recebido B, acende o led azul
    if (buf == 'B')
    {
      digitalWrite(5, HIGH);
      Serial.println("LED Azul ligado !");
    }

  }
}
