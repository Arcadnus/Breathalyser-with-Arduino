
//SERVO MOTOR
#include <Servo.h>
#define SERVO 11 // Porta Digital 6 PWM
 Servo s; // Variável Servo
int pos; // Posição Servo
//SERVO MOTOR
#define PORTB _SFR_IO8(0x05)



#define qtdLED 6  //Declaração da quantidade de LEDs da aplicação

int LEDs[qtdLED]; //Variável que guardará em cada posição o pino de saída para cada LED 
int sensorPin=0; //Variável para guardar o valor lido pelo sensor
int tempo; //Variável para o tempo de leitura do sensor
int lidomaximo; //Variável para armazenar o maior valor lido durante a leitura
int i; //Variável de contagem
int j; //Variável de contagem


// TESTE COM BOTÃO
//const int não mudam
const int buttonPin = 12;     // Pin onde o botão está inserido
const int ledPin =  11;      // Pin do led acendido pelo botão
int btnStatus = 0;         // ler o Variável para guardar o estado do botao, pressionado ou não
//  TESTE COM BOTÃO


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

  // TESTE COM BOTÃO
  pinMode(ledPin, OUTPUT);    //Led recebe energia
  pinMode(buttonPin, INPUT);  //Botão envia dados
  // TESTE COM BOTÃO

  // DEFINIR SERVO MOTOR
    s.attach(SERVO);
    pos=0;
    s.write(pos);
  // DEFINIR SERVO MOTOR

}

void loop()
{
  PORTB = PORTB ^ 100000;  //Inverte o estado do pino digital 13 para dar o efeito de Blink(Piscagem)
  delay(100); //Delay para efeito de blink do LED, indicado que o teste pode ser feito pelo usuário
  int sensor = analogRead(sensorPin); //Lê o sensor e guarda na variável

  btnStatus = digitalRead(buttonPin); //Lê o status do botão

  // COMEÇO DA CONTAGEM


  if(btnStatus == LOW) //Se a leitura for maior que 40 (valor escolhido para a demonstração utilizando-se um...
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


    // FIM DA CONTAGEM

      // LIBERA OU NÃO A TRAVA DO CARRO

     if(nivel<1){

        Serial.print(nivel);
        
        for(pos = 0; pos < 90; pos++)
        {
          s.write(pos);
          delay(5);
        }
        
     }
     else{
       
        Serial.print(nivel);
        
        for(pos = 90; pos >= 0; pos--)
        {
          s.write(pos);
          delay(5);
        }

     }

      
     if (nivel<5){  // 15 minutos de espera
        Serial.print("15 minutos");
        Serial.print("(");
        Serial.print(lidomaximo);
        Serial.print(")");
        Serial.println();
        
      }
      else{         // 30 minutos de espera
        Serial.print("30 minutos");
        Serial.print("(");
        Serial.print(lidomaximo);
        Serial.print(")");
        Serial.println();
        
      }



    
    delay(10000); //Aguarda 10 segundos para o usuário conseguir fazer a leitura do bargraph
    for(i=0;i<qtdLED;i++) //Apaga todos os LEDs
    {
      digitalWrite(LEDs[i],LOW);
    }

  }



}
