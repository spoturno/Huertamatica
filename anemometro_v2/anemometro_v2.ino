volatile long pulse1 = 0;
volatile long pulse2 = 0;
volatile byte speedCount = 0;
int rpm; int mph; int kph;
const long radious = 0.000932057; // radio 15cm en millas

//canales-inputs encoder
const byte encoderPinA = 2;
const byte encoderPinB = 3;

long pulse = 0;
volatile long pulseTime = 0; 
volatile bool pinB, pinA;

void pulse_detect(){ // agregar la logica para otra sentido
  pulse2 = pulse1;
  pulse1 = millis();
  speedCount++;
  if(speedCount == 2){
    detachInterrupt(0);
  }  
}


void setup() {
  Serial.begin(9600);
  pinMode(encoderPinA, INPUT);
  pinMode(encoderPinB, INPUT);
  attachInterrupt(0, pulse_detect, FALLING);
  
}

void readEncoder(){
  pinA = bitRead(PIND,encoderPinA);
  pinB = bitRead(PIND,encoderPinB);
  pulse += (pinA == pinB) ? +1 : -1;
}


void loop() {
  //Serial.println(pulse);
  if(speedCount == 2){
    pulseTime = pulse1 - pulse2;
    rpm = 60000 / pulseTime;
    mph = rpm * 60 * radious * PI;
    kph = mph / 0.62137; // convert to kph  
    attachInterrupt(0, pulse_detect, FALLING); //re-attach the interrput
  }

  if(millis() - pulse1 >= 2000){ //if a pulse is not registered for 2 seconds
    mph = 0;
    kph = 0;
    speedCount = 0;  
  }

  
  Serial.println(kph);
}
