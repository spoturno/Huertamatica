
//canales-inputs encoder
const byte encoderPinA = 2;
const byte encoderPinB = 3;

volatile long pulse;

volatile bool pinB, pinA;

int rpm = 0;


void setup() {
  Serial.begin(9600);
  pinMode(encoderPinA, INPUT);
  pinMode(encoderPinB, INPUT);
  attachInterrupt(0, readEncoder, CHANGE);
  
}

void readEncoder(){
  pinA = bitRead(PIND,encoderPinA);
  pinB = bitRead(PIND,encoderPinB);
  pulse += (pinA == pinB) ? +1 : -1;
}


void loop() {
  Serial.println(pulse);

  
  //convertir counter to rpm
  
}
