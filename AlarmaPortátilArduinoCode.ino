#include <LiquidCrystal.h>

// Definir pines
const int buttonPin = 9;     // Pin del botón
const int buzzerPin = 8;     // Pin del buzzer
const int EchoPin = 10;      // Pin del sensor de ultrasonido (Echo)
const int TriggerPin = 11;   // Pin del sensor de ultrasonido (Trigger)

// Crear objeto LCD
LiquidCrystal lcd(2, 3, 4, 5, 6, 7);

// Variables de funcionamiento
bool alarmaActiva = false;
int distanciaTomada = 0;
const float MargenError = 30;

void setup() {
  Serial.begin(9600);

  // Configurar pines
  pinMode(buttonPin, INPUT);
  pinMode(buzzerPin, OUTPUT);
  pinMode(TriggerPin, OUTPUT);
  pinMode(EchoPin, INPUT);

  // Inicializar LCD
  lcd.begin(16, 2);
}

void loop() {
  // Medir la distancia con el sensor de ultrasonido y mostrarla en el LCD
  int cm = ping(TriggerPin, EchoPin);
  
  // Si se activa la alarma (botón presionado), hacer sonar el buzzer
  if (digitalRead(buttonPin) == HIGH) {
    alarmaActiva = !alarmaActiva;
    distanciaTomada = cm;
    noTone(buzzerPin);
  }
  if(alarmaActiva && (cm < (distanciaTomada-MargenError) || cm > (distanciaTomada+MargenError))){
    tone(buzzerPin, 262, 5000); // Hacer sonar el buzzer
  }
  
  mostrarDistancia(cm);
  delay(250);
}

// Función para medir la distancia con el sensor de ultrasonido
int ping(int TriggerPin, int EchoPin) {
  long duration, distanceCm;

  digitalWrite(TriggerPin, LOW);
  delayMicroseconds(4);
  digitalWrite(TriggerPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(TriggerPin, LOW);

  duration = pulseIn(EchoPin, HIGH);
  distanceCm = duration * 10 / 292 / 2;

  return distanceCm;
}

// Función para mostrar la distancia en el LCD
void mostrarDistancia(int cm) {
  lcd.clear();
  lcd.print(cm);
  lcd.println(" cm , By PetaZ");
  lcd.setCursor(0, 1);
  lcd.print("A: ");
  lcd.print(alarmaActiva);
  lcd.print(" --> ");
  lcd.print(distanciaTomada);
  
}
