const int ENC_COUNT_REV = 600;
const int ENC_IN = 2;
const int radious = 15; // radio de anemometro en centimetros

volatile long pulse; // pulsos del encoder

//counters for milliseconds during interval
long currentMillis = 0;
long previousMillis = 0; // time for messure 1s intervals
long previousMillisVelocity = 0; // time for messure 10s intervals

int rpm; // rev per min
int kph; // kilom per h

int velocidadInicial = 0;
int velocidadFinal = 0;
int velocidadMedia = 0;

bool estadoCupula = true; // abierta o cerrada

void setup(){
    Serial.begin(9600);
    pinMode(ENC_IN, INPUT_PULLUP); // solo 1 channel del encoder
    attachInterrupt(digitalPinToInterrupt(ENC_IN), updateEncoder, RISING);   
}

void updateEncoder(){
  pulse++;
}

void loop(){
    currentMillis = millis();  
    if(currentMillis - previousMillis >= 1000){
        previousMillis = currentMillis;
        detachInterrupt(digitalPinToInterrupt(ENC_IN));
        
        previousMillis = currentMillis;
        rpm = pulse * 60 / ENC_COUNT_REV; 
        kph = (0.1885 * rpm * 2 * radious) / 100; 

        // la otra forma es ir calculando el promedio iterativamente.
        
        if(currentMillis % 1000 == 0){
            velocidadInicial = kph;
            Serial.print("velocidadInicial:");
            Serial.println(velocidadInicial);
        }
        if(currentMillis % 10000 == 0){
            velocidadFinal = kph;
            Serial.print("velocidadFinal:");
            Serial.println(velocidadFinal);
        }

        if(rpm > 0){
            printStatus();
        }
        pulse = 0;
        attachInterrupt(digitalPinToInterrupt(ENC_IN), updateEncoder, RISING);
    }
    
    if(currentMillis - previousMillisVelocity >= 10000){
        previousMillisVelocity = currentMillis;
        velocidadMedia = (velocidadInicial + velocidadFinal) / 2;
        if(velocidadMedia >= 15 && estadoCupula){
            //cerrar cupula con motores
            Serial.print("CERRANDO...");
            estadoCupula = false;
        }else if(velocidadMedia <= 5 && !estadoCupula){
            //abrir cupula
            Serial.print("ABRIENDO...");
            estadoCupula = true;
        }
    }
    
}

void printStatus(){
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
