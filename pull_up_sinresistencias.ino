#define pinBoton 6
#define pinLed 7
int lecturaBoton;

void setup() {
  Serial.begin(9600);
  pinMode(pinBoton, INPUT_PULLUP);
  pinMode(pinLed, OUTPUT);
  // put your setup code here, to run once:

}

void loop() {
  // put your main code here, to run repeatedly:
  lecturaBoton = digitalRead(pinBoton);
  if(lecturaBoton == 0){
    digitalWrite(pinLed, 1);
  }else{
    digitalWrite(pinLed, 0);
  }

  Serial.println(lecturaBoton);

}
