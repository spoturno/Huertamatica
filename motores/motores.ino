const int en1 = 9;
const int in1 = 8;
const int in2 = 7;
const int in3 = 5;
const int in4 = 4;
const int en2  = 3;
int cont = 0;

void setup() {
  pinMode(en1,OUTPUT);
  pinMode(in1,OUTPUT);
  pinMode(in2,OUTPUT);
  pinMode(in3,OUTPUT);
  pinMode(in4,OUTPUT);
  pinMode(en2, OUTPUT);

  attachInterrupt(digitalPinToInterrupt(2),motor, RISING);
}

void motor(){
  cont++;
   
}

void cerrar_move(){
    

  analogWrite(en1,140);
  analogWrite(en2,140);
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);  

  delay(5000);

  //parar ambos
  analogWrite(en1,0);
  analogWrite(en2,0);
 
    
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

  delay(5000);

  //parar ambos
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in4, LOW);
  
}

void loop(){
 //cerrar_move();
 //abrir_move();
   
  if(cont == 300){
       cerrar_move();   
    } 
}
