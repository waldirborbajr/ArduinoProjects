#include "saida.h"

// Instancia um objeto chamado LED no pino 13
Saida LED(13);

void setup(){
}

void loop()
{
 LED.liga();       // liga o led
 delay(1000);      // aguarda 1 segundo
 LED.desliga();    // desliga o Led
 delay(1000);      // aguarda 1 segundo
}
