void setup()
{
  Serial.begin(9600);
  Serial.println(F("Sensor de temperatura interna"));
}

void loop()
{
  // exibe a temperatura em °C
  Serial.println(GetTemp(), 1);
  delay(1000);
}

double GetTemp(void)
{
  unsigned int valorADC;
  double temperatura;

  ADMUX = (_BV(REFS1) | _BV(REFS0) | _BV(MUX3)); //seleciona tensão interna de 1,1 V e canal 8
  ADCSRA |= _BV(ADEN);  // habilita o conversor AD

  delay(20);            // aguarda estabilização da tensão

  ADCSRA |= _BV(ADSC);  // inicia a conversão

  //aguarda o fim da conversão
  while (bit_is_set(ADCSRA, ADSC));

  // le o valor da conversão
  valorADC = ADCW;

  // calcula o valor da temperatura
  temperatura = (valorADC - 324.31 ) / 1.22;

  // retorna o valor da temperatura em °C
  return (temperatura);
}
