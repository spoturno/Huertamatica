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


const int en1 = 9;
const int in1 = 8;
const int in2 = 7;
const int in3 = 5;
const int in4 = 4;
const int en2  = 3;

void setup(){
    Serial.begin(9600);
    pinMode(ENC_IN, INPUT_PULLUP); // solo 1 channel del encoder
    attachInterrupt(digitalPinToInterrupt(ENC_IN), updateEncoder, RISING);   
    pinMode(en1,OUTPUT);
    pinMode(in1,OUTPUT);
    pinMode(in2,OUTPUT);
    pinMode(in3,OUTPUT);
    pinMode(in4,OUTPUT);
    pinMode(en2,OUTPUT);  
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
        
        if(currentMillis == 1000){ // unicamente al inicio
            velocidadInicial = kph;
            Serial.print("velocidadInicial:");
            Serial.println(velocidadInicial);
        }else if(currentMillis == 11000){
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
    
    if(currentMillis - previousMillisVelocity >= 11000){
        previousMillisVelocity = currentMillis;
        velocidadMedia = (velocidadInicial + velocidadFinal) / 2;
        if(velocidadMedia >= 15 && estadoCupula){
            //cerrar cupula con motores
            Serial.print("CERRANDO...");
            cerrar_move();
            estadoCupula = false;
            
        }else if(velocidadMedia < 15 && !estadoCupula){
            //abrir cupula
            Serial.print("ABRIENDO...");
            abrir_move();
            estadoCupula = true;
        }
        //reseteamos el tiempo para conveniencia de logica
        currentMillis = 0;
        previousMillis = 0;
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

void cerrar_move(){
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);

  //setear velocidad de motor A en rango de [0,255]
  analogWrite(en1,140);

  //encender motor B
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);

  //setear velocidad motor B
  analogWrite(en2,120);

  //delay(5000);

  //parar ambos
  //digitalWrite(in1, LOW);
  //digitalWrite(in2, LOW);
  //digitalWrite(in3, LOW);
  //digitalWrite(in4, LOW);
    
}

void abrir_move() {
  //demoMotors();

  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);

  //setear velocidad de motor A en rango de [0,255]
  analogWrite(en1,110);

  //encender motor Ba
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);

  //setear velocidad motor B
  analogWrite(en2,140);

  //delay(5000);

  //parar ambos
  //digitalWrite(in1, LOW);
  //digitalWrite(in2, LOW);
  //digitalWrite(in3, LOW);
  //digitalWrite(in4, LOW);
  
}
