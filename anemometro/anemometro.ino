const int ENC_COUNT_REV = 600;
const int ENC_IN = 2;
const int radious = 15; // radio de anemometro en centimetros

volatile long pulse;
int interval = 1000; //intervalo de 1s para medidas

//counters for milliseconds during interval
long previousMillis = 0;
long currentMillis = 0;

int rpm; // rev per min
int kph; // kilom per h

void setup() {
  Serial.begin(9600);
  pinMode(ENC_IN, INPUT_PULLUP);
  //pinMode(encoderPinB, INPUT);
  attachInterrupt(digitalPinToInterrupt(ENC_IN), updateEncoder, RISING);
  previousMillis = millis();
  
}

void updateEncoder(){
  pulse++;
}


void loop() {
  
  //update rpm value every second
  currentMillis = millis();
  if(currentMillis - previousMillis > interval){ // cuantos pulsos ocurren en intervalo de 1s
    detachInterrupt(digitalPinToInterrupt(ENC_IN));
    previousMillis = currentMillis;
    //multiplicando por 60 obtenemos la cantidad en 1 minuto
    //dividimos por el total de pulsos x rev del encoder 
    rpm = pulse * 60 / ENC_COUNT_REV; 
    // v = 2 * pi * frec * radio
    // convertimos a kph multiplicando por 3.6 (3600 / 1000)
    kph = (0.1885 * rpm * 2 * radious) / 100; 

    if(rpm > 0){
      Serial.print("PULSES:");
      Serial.print(pulse);
      Serial.print('\n');
      
      Serial.print("SPEED:");
      Serial.print(rpm);
      Serial.print("RPM");
      Serial.print('\t');
      Serial.print("KPH:");
      Serial.print(kph);
      Serial.print('\t');
    }
    pulse = 0;
    attachInterrupt(digitalPinToInterrupt(ENC_IN), updateEncoder, RISING);
  
  }
  
}
