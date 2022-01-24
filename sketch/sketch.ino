#define qtdLED 6  //Declaração da quantidade de LEDs da aplicação
int LEDs[qtdLED]; //Vetor que guardará em cada posição o pino de saída para cada LED 
int sensorPin=0; //Variável para guardar o valor lido pelo sensor
int tempo; //Variável para o tempo de leitura do sensor
int lidomaximo; //Variável para armazenar o maior valor lido durante a leitura
int i; //Variável de contagem
int j; //Variável de contagem

void setup()
{
  Serial.begin(9600);
  i=0;
  j=2;

  while(i < qtdLED) //Enquanto i for menor que a quantidade de LEDs que foi definida...
  {                 //...guarda no vetor um valor(começando de 2 e incrementando) equivalente a um pino digital
    LEDs[i] = j;
    i++;
    j++;
  }

for(i=0;i<qtdLED;i++) //Define os pinos dos LEDs(nesse exemplo de 2 ao 7) como saída
  {
    pinMode(LEDs[i], OUTPUT);
  }
  pinMode(13, OUTPUT); //Define o pino 13 como saída para nos indicar quando pode fazer-se o teste (LED Piscando)...
                       //...e quando o circuito estiver fazendo a leitura do sensor (LED Aceso)
}

void loop()
{
  PORTB = PORTB ^ 100000;  //Inverte o estado do pino digital 13 para dar o efeito de Blink(Piscagem)
  delay(100); //Delay para efeito de blink do LED, indicado que o teste pode ser feito pelo usuário
  int sensor = analogRead(sensorPin); //Lê o sensor e guarda na variável


  
  if(sensor >= 40) //Se a leitura for maior que 40 (valor escolhido para a demonstração utilizando-se um...
  {                //...antisséptico bucal)
    digitalWrite(13, HIGH); //Acende o LED Azul(Indicando que o sensor detectou um mínimo de álcool (sensor >= 40)
    lidomaximo = 0;         //Iniciar o valor máximo lido pelo sensor como 0
    for(tempo=0;tempo<=5000;tempo++) //Faz a leitura do sensor por 5 segundos... 
    {                                //...a cada 1 milissegundo atualiza o maior valor lido pelo sensor.
      int sensor = analogRead(sensorPin);
      delay(1);
      if(sensor > lidomaximo)
      {
        lidomaximo = sensor;
      }
    }
    digitalWrite(13, LOW); //Após o termino da leitura, apaga o LED Azul
    int nivel = map(lidomaximo, 0, 1023, 0, qtdLED); //Converte a escala de 0 a 200 do sensor em...
                                                    //...0 a 6(LEDs) e armazena na variável nível.
                                                    //OBS: Lembrando o que o sensor lê de 0 a 1023, pelo antisséptico...
                                                    //...ter um teor de álcool relativamente baixo, foi utilizado...
                                                    //...a escala de 0 a 200
    for(i=0;i<qtdLED;i++) //Compara todos os pinos dos LEDs com o valor convertido da escala...
    {                     //...Ex: Se meu nível convertido foi 5, então o os leds dos pinos 2 ao 6 irão acender
      if (i < nivel) //Compara o pino atual da contagem, e se for menor que o nível máximo convertido...
      {
        digitalWrite(LEDs[i], HIGH); //...Acende o LED
      }
      else //Compara o pino atual da contagem, e se for maior que o nível máximo convertido ...
      {
        digitalWrite(LEDs[i], LOW); //...Apaga o LED
      }
 
      
    }
   if (5>nivel){
      Serial.print("passou");
      Serial.println();
    }
    else{
      Serial.print("não passou!");
      Serial.println();
    }
    
    delay(10000); //Aguarda 10 segundos para o usuário conseguir fazer a leitura do bargraph
    for(i=0;i<qtdLED;i++) //Apaga todos os LEDs
    {
      digitalWrite(LEDs[i],LOW);
    }
  }
}
