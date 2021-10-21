const int  higometroPin = A0;
const int bomba = 13;
int valor;

void setup(){
  Serial.begin(9600);
  pinMode(bomba,OUTPUT);  
  pinMode(higometroPin, INPUT);
  
}

void loop(){
  valor = analogRead(higometroPin);

  if (valor >= 800){ 
    digitalWrite(bomba, HIGH);
    delay(5000);
    digitalWrite(bomba, LOW);
  }
}
