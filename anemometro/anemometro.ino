//int counter = 0;  //This variable will increase or decrease depending on the rotation of encoder


//canales-inputs encoder
const byte encoderPinA = 2;
const byte encoderPinB = 3;

volatile long pulse;

volatile bool pinB, pinA, dir;



void setup() {
  Serial.begin(9600);
  pinMode(encoderPinA, INPUT);
  pinMode(encoderPinB, INPUT);
  attachInterrupt(0, readEncoder, CHANGE);
  
  //pulso A rising de encoder
  //attachInterrupt(digitalPinToInterrupt(encoderPinA), ai0, RISING);
  //pulso B rising de encoder
  //attachInterrupt(digitalPinToInterrupt(encoderPinB), ai1, RISING);
}

void readEncoder(){
  pinA = bitRead(PIND,encoderPinA);
  pinB = bitRead(PIND,encoderPinB);
  pulse += (pinA == pinB) ? +1 : -1;
}
/*
void ai0(){
  //ai0 se activa si digitalpin #2 va de LOW a HIGH
  //chequamos pin 5 para ver dirección
  if(digitalRead(3) == LOW){
    counter++;
  }else{
    counter--;  
  }
}

void ai1(){
    if(digitalRead(2) == LOW){
      counter--;
    }else{
      counter++;
    }
}
*/

void loop() {
  Serial.println(pulse);
  //convertir counter to rpm
  
  /*current_state_clk = digitalRead(input_clk);

  //si son diferentes los estados del input_clk entonces un pulso ha ocurrido
  if(current_state_clk != previous_state_clk){
    if(digitalRead(input_dt) != current_state_clk){//encoder rotando a contra-reloj
     counter--;
     if(counter < 0){
      counter = 0; 
     } 
    }else{//encoder rotando normal
      counter++;
      if(counter > 180){
        counter = 180;
      }
    }
    Serial.print("Posicion: ");
    Serial.Println(counter);

    //actualizar previos_state_clk con el estado actual
    previous_state_clk = current_state_clk;
  }
  if(velocidad > velocidad_maxima){
      digitalWrite(pin_led, HIGH);
      delay(3000);
      //cierra la cupula (TODO)
      digitalWrite(pin_led, LOW);
      
  }else if(velocidad < velocidad_minima){
      digitalWrite(pin_led, HIGH);
      delay(3000);
      // abre la cupula (TODO)
      digitalWrite(pin_led, LOW);
  }
  */
}
