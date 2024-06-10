#include <SPI.h>
#include <MFRC522.h>
#include <Servo.h>

#define RST_PIN  9
#define SS_PIN   10
#define SERVO_PIN 5 // Cambia esto al pin al que esté conectado tu servomotor

MFRC522 mfrc522(SS_PIN, RST_PIN);
byte LecturaUID[4];

// Actualiza los valores de Usuario1 y Usuario2 con los UID correctos
byte Usuario1[4] = {0xA2, 0x2D, 0x7C, 0x1D};
byte Usuario2[4] = {0xA3, 0x66, 0x96, 0xA6};

int numeroUsuario = -1;

Servo miServo;

void setup() {
  Serial.begin(9600);
  SPI.begin();
  mfrc522.PCD_Init();
  miServo.attach(SERVO_PIN); // Inicializa el servomotor
  Serial.println("Listo");
}

void loop() {
  if (!mfrc522.PICC_IsNewCardPresent())
    return;

  if (!mfrc522.PICC_ReadCardSerial())
    return;

  Serial.print("UID:");

  for (byte i = 0; i < mfrc522.uid.size; i++) {
    if (mfrc522.uid.uidByte[i] < 0x10) {
      Serial.print(" 0");
    } else {
      Serial.print(" ");
    }
    Serial.print(mfrc522.uid.uidByte[i], HEX);
    LecturaUID[i] = mfrc522.uid.uidByte[i];
  }

  Serial.print("\t");

  // Comparar con usuarios y asignar el número de usuario
  if (comparaUID(LecturaUID, Usuario1)) {
    numeroUsuario = 1;
  } else if (comparaUID(LecturaUID, Usuario2)) {
    numeroUsuario = 2;
  } else {
    numeroUsuario = -1;
  }

  Serial.print("Número de Usuario: ");
  Serial.println(numeroUsuario);

  // Mostrar mensaje personalizado según el número de usuario
  if (numeroUsuario != -1) {
    Serial.print("Hola Usuario ");
    Serial.println(numeroUsuario);
    abrirPuerta(); // Llama a la función para abrir la puerta (controla el servomotor)
  } else {
    Serial.println("No te conozco");
  }

  mfrc522.PICC_HaltA();
}

boolean comparaUID(byte lectura[], byte usuario[]) {
  for (byte i = 0; i < mfrc522.uid.size; i++) {
    Serial.print("lectura[");
    Serial.print(i);
    Serial.print("]: ");
    Serial.print(lectura[i], HEX);
    Serial.print(", usuario[");
    Serial.print(i);
    Serial.print("]: ");
    Serial.println(usuario[i], HEX);

    if (lectura[i] != usuario[i]) {
      return false;
    }
  }
  return true;
}

void abrirPuerta() {
  // Controla el servomotor para abrir la puerta
  miServo.write(90); // Cambia el ángulo según tu configuración para abrir la puerta
  delay(6000); // Mantén la puerta abierta durante 2 segundos
  miServo.write(0); // Vuelve a la posición inicial (cerrada)
}

