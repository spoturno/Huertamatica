int counter = 0;  //This variable will increase or decrease depending on the rotation of encoder


//canales-inputs encoder
const int input_clk = 2;
const int input_dt = 3;


int velocidad;
int velocidad_maxima = 30; //cambiar rango
int velocidad_minima = 20; //cambiar rango

int counter = 0; //valor cambiante encoder

//podremos determinar si realmente se movió el encoder
int current_state_clk;
int previous_state_clk;


void setup() {

  //encoder pins como input
  pinMode(input_clk, INPUT);
  pinMode(input_dt, INPUT);
  
  Serial.begin(9600);


  //leer y asignar estado inicial a ...
  previous_state_clk = digitalRead(input_clk);

  //pulso A rising de encoder
  attachInterrupt(digitalPinToInterrupt(2), ai0, RISING);

  //pulso B rising de encoder
  attachInterrupt(digitalPinToInterrupt(3), ai1, RISING);
}

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


void loop() {

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
