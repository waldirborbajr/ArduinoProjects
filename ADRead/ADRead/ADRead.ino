// Variáveis para armazenar os resultados
unsigned long tempo_inicio;
unsigned long tempo_fim;
unsigned long valor;

void setup() {
  Serial.begin(19200);    //inicia a comunicação serial
}

void loop() {
  // leitura
  tempo_inicio = micros(); //marca tempo de inicio de leitura
  valor = analogRead(0);  //le valor convertido
  tempo_fim = micros();   //le tempo no fim da conversão

  //exibe valor lido e tempo de conversão
  Serial.print("Valor = ");
  Serial.print(valor);
  Serial.print(" -- Tempo leitura = ");
  Serial.print(tempo_fim - tempo_inicio);
  Serial.println(" us");
  delay(500);
}
