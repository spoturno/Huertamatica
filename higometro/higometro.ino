const int  sensorPin= A0;
const int led = 4;
const int bomba = 8;

void setup (){
Serial.begin(9600);
}

void loop () 
{
int humedad = analogRead(sensorPin);
if (humedad < 30) 
digitalWrite( led, HIGH) ;
delay(3000);
digitalWrite(bomba, HIGH);
delay(5000);
digitalWrite(bomba, LOW);
delay(1000);
digitalWrite(led,LOW);
}
