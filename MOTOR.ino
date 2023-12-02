int motorPin = 9;          // Pin del motor del ventilador
int waterMotorPin = 10;    // Pin del motor de agua
int ledPin = 11;           // Pin de las luces LED

void setup() {
  pinMode(motorPin, OUTPUT);
  pinMode(waterMotorPin, OUTPUT);
  pinMode(ledPin, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  if (Serial.available() > 0) {
    String command = Serial.readStringUntil('\n'); // Lee el comando enviado por el cliente Python

    if (command.equals("FAN_TOGGLE")) {
      toggleFanMotor();
    } else if (command.equals("WATER_TOGGLE")) {
      toggleWaterPump();
    } else if (command.startsWith("LED")) {
      controlLedIntensity(command);
    } else if (command.startsWith("FAN_SPEED")) {
      controlFanSpeed(command);
    } else {
      Serial.println("Comando desconocido");
    }
  }
}

void toggleFanMotor() {
  digitalWrite(motorPin, !digitalRead(motorPin));
  Serial.println("Motor del Ventilador Toggled");
}

void toggleWaterPump() {
  digitalWrite(waterMotorPin, !digitalRead(waterMotorPin));
  Serial.println("Motor de Agua Toggled");
}

void controlLedIntensity(String command) {
  int intensity = command.substring(3).toInt(); // Ignora los primeros 3 caracteres (comando "LED ")
  analogWrite(ledPin, map(intensity, 0, 100, 0, 255)); // Mapea la intensidad a un valor PWM (0 - 255)
  Serial.println("Intensidad de LED ajustada");
}

void controlFanSpeed(String command) {
  int speed = command.substring(9).toInt(); // Ignora los primeros 9 caracteres (comando "FAN_SPEED ")
  analogWrite(motorPin, map(speed, 0, 100, 0, 255)); // Mapea la velocidad a un valor PWM (0 - 255)
  Serial.println("Velocidad del Motor del Ventilador ajustada");
}
