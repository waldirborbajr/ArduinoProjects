#ifndef SAIDA_H
#define SAIDA_H

#include "Arduino.h"

class Saida
{
public:
   Saida(int pin);
   void  liga();
   void  desliga();
   void  inverte();
 
private:
   int pino;
};

#endif
