//const int pinLed = 13;
const int pinEncoder = 2;

const int pinHigrometro = A0;
const int bomba = 13;

const int ENC_COUNT_REV = 600;
const int radious = 15;

//pines de motores-puente
const int enA = 9;
const int in1 = 8;
const int in2 = 7;
const int in3 = 5;
const int in4 = 4;
const int enB  = 3;


volatile long count; //pulsos de encoder

int valorHigrometro;

int rpm; // rev per min
int kph; // kilom per h

int velocidadInicial = 0;
int velocidadFinal = 0;
int velocidadMedia = 0;

unsigned long currentTime = 0;
unsigned long previousTime1 = 0;
unsigned long previousTime2 = 0;
unsigned long previousTimeLed = 0;
unsigned long previousTimeRegar = 0;
int tiempoRegado = 240000; // 4 minutos

//variables estado
bool primerValor = true;
bool estadoCupula = true;
bool estadoMotores = false;

void setup(){
    Serial.begin(9600);
    pinMode(pinEncoder, INPUT_PULLUP);
    attachInterrupt(digitalPinToInterrupt(pinEncoder), updateEncoder, RISING);    
    pinMode(13, OUTPUT);
    pinMode(bomba,OUTPUT);  
    pinMode(pinHigrometro, INPUT);

    pinMode(enA,OUTPUT);
    pinMode(in1,OUTPUT);
    pinMode(in2,OUTPUT);
    pinMode(in3,OUTPUT);
    pinMode(in4,OUTPUT);
    pinMode(enB,OUTPUT);  
}

void loop(){
        currentTime = millis();
        
        if(currentTime - previousTime1 >= 1000){
            previousTime1 = currentTime;
            detachInterrupt(digitalPinToInterrupt(pinEncoder));
            rpm = count * 60 / ENC_COUNT_REV; 
            kph = (0.1885 * rpm * 2 * radious) / 100;

            if(primerValor){
                velocidadInicial = kph;
                primerValor = false;  
            }
            
            if(rpm > 0){
                printStatus();
            }
            count = 0;
            attachInterrupt(digitalPinToInterrupt(pinEncoder), updateEncoder, RISING); 

                
        }else if(currentTime - previousTime2 >= 10000){
            previousTime2 = currentTime;
            velocidadFinal = kph;
            velocidadMedia = (velocidadInicial + velocidadFinal) / 2;
            primerValor = true;
            if((velocidadMedia >= 20) && estadoCupula && !estadoMotores){
                Serial.println("CERRANDO...");
                cerrarCupula(); // prender los motores
                estadoMotores = true;
                estadoCupula = false;    
            }else if(velocidadMedia <= 8 && !estadoCupula && !estadoMotores){
                Serial.println("ABRIENDO...");
                abrirCupula();
                estadoMotores = true;
                estadoCupula = true;    
            }
       }else if(currentTime - previousTimeLed >= 20000){
         previousTimeLed = currentTime;
         if(estadoMotores){
            Serial.println("Motores apagados");
            apagarMotores(); // apagar los motores
            estadoMotores = false;   
         }
       }else if(currentTime - previousTimeRegar >= tiempoRegado){
         valorHigrometro = analogRead(pinHigrometro);
         if(valorHigrometro >= 800){
            Serial.println("REGANDO...");
            digitalWrite(bomba, HIGH);
            delay(5000); // ver o cambiar
            digitalWrite(bomba, LOW);
         }
       }
       
}


void updateEncoder(){
    count++;
}

void printStatus(){
    Serial.print("PULSOS:");
    Serial.print(count);
    Serial.print('\n');
    Serial.print("VELOCIDAD:");
    Serial.print(rpm);
    Serial.print("RPM");
    Serial.print('\t');
    Serial.print(kph);
    Serial.print("KPH");
    Serial.print('\t');
}

void cerrarCupula(){
    analogWrite(enA,140);
    analogWrite(enB,120);
  
    digitalWrite(in1, HIGH);
    digitalWrite(in2, LOW);
    digitalWrite(in3, HIGH);
    digitalWrite(in4, LOW);
}

void abrirCupula(){
    analogWrite(enA,110);
    analogWrite(enB,140);
  
    digitalWrite(in1, LOW);
    digitalWrite(in2, HIGH);
    digitalWrite(in3, LOW);
    digitalWrite(in4, HIGH);
}

void apagarMotores(){
    analogWrite(enA,0);
    analogWrite(enB,0);
}
