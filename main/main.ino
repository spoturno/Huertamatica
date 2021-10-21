const int ENC_COUNT_REV = 600;
const int ENC_IN = 2;
const int radious = 15; // radio de anemometro en centimetros

volatile long pulse;
int interval = 1000; //intervalo de 1s para medidas
int iterval_velocity = 10000; // itervalo para medicion de velocidad si supera cota

//counters for milliseconds during interval
long previousMillis = 0;
long currentMillis = 0;

long previousMillisVelocity = 0;
//long currentMillisVelocity = 0;


int rpm; // rev per min
int kph; // kilom per h

unsigned long vtime;

int velocidad_actual;
int velocidad_anterior;

int velocidad_maxima = 30; //cambiar rango
int velocidad_minima = 20; //cambiar rango

bool estado_cupula; //indicador para cerrar o no la cupula

void setup() {
  Serial.begin(9600);
  pinMode(ENC_IN, INPUT_PULLUP);
  //pinMode(encoderPinB, INPUT);
  attachInterrupt(digitalPinToInterrupt(ENC_IN), updateEncoder, RISING);
  previousMillis = millis();
  previousMillisVelocity = millis();
}

void updateEncoder(){
  pulse++;
}

void loop() {
  currentMillisVelocity = millis(); 
  currentMillis = millis();
  if(currentMillisVelocity - previousMillisVelocity > iterval_velocity){
      previousMillisVelocity = currentMillisVelocity;

      if(currentMillis - previousMillis > interval){ 
        detachInterrupt(digitalPinToInterrupt(ENC_IN));
        previousMillis = currentMillis;
        rpm = pulse * 60 / ENC_COUNT_REV; 
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
  
  

  
  velocidad_anterior = velocidad_actual;
  vtime = milis();
  if((milis() - vtime) >= 5000 && (velocidad_anterior >= velocidad_actual)){
    estado_cupula = true;   
  }else estado_cupula = false;
  
  if(velocidad_actual => velocidad_maxima && !estado_cupula){
      digitalWrite(pin_led, HIGH);
      delay(3000); // no se si es necesario debido a la espera del viento
      
      //cierra la cupula (TODO)
      
      digitalWrite(pin_led, LOW);

  }else if(velocidad_actual <= velocidad_minima && estado_cupula){
      digitalWrite(pin_led, HIGH);
      delay(3000);
      
      //abre la cupula (TODO)
      
      
      digitalWrite(pin_led, LOW);
  }

}
}
  
