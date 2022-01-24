const int analogPin = A0;   
const int ledCount = 10;    
int ledPins[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10};   

void setup() {
  
  Serial.begin(9600);
  for (int thisLed = 0; thisLed < ledCount; thisLed++) {
    pinMode(ledPins[thisLed], OUTPUT); 
  }
}

void loop() {

  int sensorReading = analogRead(analogPin);
  int ledLevel = map(sensorReading, 0, 1023, 0, ledCount);
    if ( 0 < ledLevel)
      {digitalWrite(ledPins[1], HIGH);} 
    else
      {digitalWrite(ledPins[1], LOW);}
    
    if ( 1 < ledLevel)
      {digitalWrite(ledPins[2], HIGH);} 
    else
      {digitalWrite(ledPins[2], LOW);}

    if ( 2 < ledLevel)
      {digitalWrite(ledPins[3], HIGH);} 
    else
      {digitalWrite(ledPins[3], LOW);}

    if ( 3 < ledLevel)
      {digitalWrite(ledPins[4], HIGH);} 
    else
      {digitalWrite(ledPins[4], LOW);}

    if ( 4 < ledLevel)
      {digitalWrite(ledPins[5], HIGH);} 
    else
      {digitalWrite(ledPins[5], LOW);}

    if ( 5 < ledLevel)
      {digitalWrite(ledPins[6], HIGH);} 
    else
      {digitalWrite(ledPins[6], LOW);}

    if ( 6 < ledLevel)
      {digitalWrite(ledPins[7], HIGH);} 
    else
      {digitalWrite(ledPins[7], LOW);}

    if ( 7 < ledLevel)
      {digitalWrite(ledPins[8], HIGH);} 
    else
      {digitalWrite(ledPins[8], LOW);}

    if ( 8 < ledLevel)
      {digitalWrite(ledPins[9], HIGH);} 
    else
      {digitalWrite(ledPins[9], LOW);}

    if ( 9 < ledLevel)
      {digitalWrite(ledPins[10], HIGH);} 
    else
      {digitalWrite(ledPins[10], LOW);}

 

    
    Serial.print(ledLevel);
    delay(10);
  }
