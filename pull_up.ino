#define pinBoton 5
#define pinLed 6
int lectBoton;

void setup()
{
  Serial.begin(9600);
  pinMode(pinBoton, INPUT);
  pinMode(pinLed, OUTPUT);
}

void loop()
{
  lectBoton = digitalRead(pinBoton);
  if(lectBoton == 0){
    digitalWrite(pinLed, HIGH);
  }else{
    digitalWrite(pinLed, LOW);
  }
  Serial.println(lectBoton);
 
}

