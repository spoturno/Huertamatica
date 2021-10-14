#include <Servo.h>

Servo myservo;
unsigned long vtime;

int velocidad_actual;
int velocidad_anterior;

int velocidad_maxima = 30; //cambiar rango
int velocidad_minima = 20; //cambiar rango

bool estado_cupula; //indicador para cerrar o no la cupula

void setup() {
  pinMode(pin_led, OUTPUT);
  Serial.begin(9600);
  myservo.attach(9);

}

void loop() {
  
  //leer velocidad_actual con interrupcion
  
  velocidad_anterior = velocidad_actual;
  vtime = milis();
  if((milis() - vtime) >= 5000 && (velocidad_anterior >= velocidad_actual)){
    estado_cupula = true;   
  }else estado_cupula = false;
  
  if(velocidad_actual => velocidad_maxima && !estado_cupula){
      digitalWrite(pin_led, HIGH);
      delay(3000);
      
      //cierra la cupula (TODO)
      //ejemplo con servo
      myservo.move(0);
      
      digitalWrite(pin_led, LOW);

  }else if(velocidad_actual <= velocidad_minima && estado_cupula){
      digitalWrite(pin_led, HIGH);
      delay(3000);
      
      //abre la cupula (TODO)
      //ejemplo con servo
      myservo.move(180);
      
      digitalWrite(pin_led, LOW);
  }

}
