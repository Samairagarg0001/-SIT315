// Define pin connections
const int motionSensorPin = 2;  // HC-SR505 digital output pin
const int tempSensorPin = A0;   // TMP36 analog output pin
const int builtInLedPin = LED_BUILTIN; // Built-in LED pin
const int externalLedPin = 3;   // External LED pin

volatile bool motionDetected = false;
float temperature = 0.0;

void motionISR() {
  motionDetected = true;
}
void setup() {
  pinMode(motionSensorPin, INPUT); // Set motion sensor as input
  pinMode(builtInLedPin, OUTPUT);  // Set built-in LED as output
  pinMode(externalLedPin, OUTPUT); // Set external LED as output
  Serial.begin(9600);              // Initialize serial monitor

  attachInterrupt(digitalPinToInterrupt(motionSensorPin), motionISR, RISING);
}
void loop() {
  // Read temperature sensor value
  int sensorValue = analogRead(tempSensorPin);
  temperature = (sensorValue * 5.0 / 1024.0 - 0.5) * 100.0; // Convert to Celsius
  Serial.print("Temperature: ");
  Serial.print(temperature);
  Serial.println(" °C");
  
  if (motionDetected) {
    digitalWrite(builtInLedPin, HIGH); // Turn on built-in LED if motion is detected
    digitalWrite(externalLedPin, HIGH); // Turn on external LED if motion is detected
    Serial.println("Motion detected! LEDs ON");
    motionDetected = false;
  }
  
  delay(500); // Small delay to avoid rapid state changes
  digitalWrite(builtInLedPin, LOW); // Turn off built-in LED after delay
  digitalWrite(externalLedPin, LOW); // Turn off external LED after delay
}
