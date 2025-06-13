// Basic LED Blinking
int ledPin = 8;     

void setup() {
  pinMode(ledPin, OUTPUT);    // Set LED pin as OUTPUT
}

void loop() {
  digitalWrite(ledPin, HIGH);  // Turn LED ON
  delay(500);                  // Wait 500 milliseconds
  
  digitalWrite(ledPin, LOW);   // Turn LED OFF
  delay(500);                  // Wait 500 milliseconds
}
