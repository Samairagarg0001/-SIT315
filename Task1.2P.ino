const int motionSensorPin = 2;  // HC-SR505 digital output pin (Interrupt Pin)
const int ledPin = LED_BUILTIN; // Built-in LED pin
volatile bool motionDetected = false; // Flag for motion detection

// Function prototype (Declare before usage)
void detectMotion();

void setup() {
  pinMode(motionSensorPin, INPUT); // Set motion sensor as input
  pinMode(ledPin, OUTPUT);         // Set LED as output
  Serial.begin(9600);              // Initialize serial monitor

  // Attach interrupt to motion sensor pin (RISING for motion detected)
  attachInterrupt(digitalPinToInterrupt(motionSensorPin), detectMotion, RISING);
}

// Interrupt Service Routine (ISR) function
void detectMotion() {
  motionDetected = true;  // Set flag when motion is detected
}

void loop() {
  if (motionDetected) {
    digitalWrite(ledPin, HIGH); // Turn on LED
    Serial.println("Motion detected! LED ON");
    
    delay(2000);  // Keep LED ON for 2 seconds
    digitalWrite(ledPin, LOW); // Turn OFF LED after delay
    Serial.println("No motion. LED OFF");
    
    motionDetected = false; // Reset flag
  }
}
