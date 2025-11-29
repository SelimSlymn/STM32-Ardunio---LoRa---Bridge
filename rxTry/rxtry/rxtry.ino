#include <SoftwareSerial.h>

// --- PIN DEFINITIONS ---
#define JOYSTICK_PIN A0  // Joystick VRx (Throttle) pin
#define LORA_RX_PIN 2    // Arduino RX (Connects to LoRa TX)
#define LORA_TX_PIN 3    // Arduino TX (Connects to LoRa RX)
#define LED_PIN 13       // Onboard LED for status indication

// Virtual Serial Communication (for LoRa module)
SoftwareSerial loraSerial(LORA_RX_PIN, LORA_TX_PIN);

void setup() {
  // 1. Initialize PC Communication (for Serial Monitor debugging)
  Serial.begin(9600);
  
  // 2. Initialize LoRa Communication (Default baud rate for E22 is 9600)
  loraSerial.begin(9600);

  // 3. Initialize Status LED
  pinMode(LED_PIN, OUTPUT);

  Serial.println("--- SYSTEM STARTING ---");
  Serial.println("Arduino: Transmitter Mode Active");
  delay(1000); // Wait for the module to stabilize
}

void loop() {
  // STEP A: Read Joystick Data (Range: 0 - 1023)
  int rawValue = analogRead(JOYSTICK_PIN);

  // STEP B: Map to Drone Protocol Format (Range: 1000 - 2000)
  // Standard Drone Protocol: 1000 = Motor Stop, 2000 = Full Throttle
  int throttleValue = map(rawValue, 0, 1023, 1000, 2000);

  // Safety: Constrain values strictly between 1000 and 2000
  throttleValue = constrain(throttleValue, 1000, 2000);

  // STEP C: Package and Transmit Data via LoRa
  // Packet Format: Prefix "T" + Value + Newline (\n)
  // Example: T1500
  loraSerial.print("T");
  loraSerial.println(throttleValue);

  // STEP D: Debugging - Print to Serial Monitor
  // If you see this, the Joystick and Arduino logic are working.
  Serial.print("Sent Packet: T");
  Serial.println(throttleValue);

  // Visual Effect: Blink LED briefly during transmission
  digitalWrite(LED_PIN, HIGH);
  delay(50); // Keep LED on for a short duration
  digitalWrite(LED_PIN, LOW);
  
  // Delay to prevent data flooding (50-100ms is ideal for stability)
  delay(50);
}