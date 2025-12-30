#include <Arduino.h>
// Temporarily disable BLE for testing
// #include "ble_advertising.h"

// Shared manufacturer data - Company ID 0xFFFF + Custom data
const uint8_t MANUFACTURER_DATA[6] = {0xFF, 0xFF, 0x01, 0x02, 0x03, 0x04};

void setup()
{
  // Initialize all LEDs for XIAO nRF52840
  #ifdef PLATFORM_NRF52
    pinMode(LED_RED, OUTPUT);
    pinMode(LED_GREEN, OUTPUT);
    pinMode(LED_BLUE, OUTPUT);
    digitalWrite(LED_RED, HIGH);    // LEDs off initially
    digitalWrite(LED_GREEN, HIGH);
    digitalWrite(LED_BLUE, HIGH);
  #else
    pinMode(LED_BUILTIN, OUTPUT);
    digitalWrite(LED_BUILTIN, LOW);
  #endif
  
  // Start Serial and wait for connection
  Serial.begin(115200);
  
  // Wait up to 5 seconds for Serial connection
  unsigned long start = millis();
  while (!Serial && (millis() - start) < 5000) {
    // Blink blue LED while waiting for Serial
    digitalWrite(LED_BLUE, LOW);
    delay(100);
    digitalWrite(LED_BLUE, HIGH);
    delay(100);
  }
  
  delay(500);
  
  Serial.println();
  Serial.println("=================================");
  Serial.println("XIAO nRF52840 Minimal Test");
  Serial.println("=================================");
  Serial.print("Serial connected after ");
  Serial.print(millis() - start);
  Serial.println(" ms");
  
  // Initialize BLE advertising (platform-specific implementation)
  // setupBLE();
  
  // Print status information
  // printBLEStatus();
  
  Serial.println("Setup complete - LEDs will blink");
  Serial.flush();
}

void loop() {
  static unsigned long counter = 0;
  
  counter++;
  
  // Check if Serial is still connected
  if (Serial) {
    Serial.print("Loop #");
    Serial.print(counter);
    Serial.print(" - millis: ");
    Serial.println(millis());
    Serial.flush();
  }
  
  // Blink all LEDs to show the board is running
  #ifdef PLATFORM_NRF52
    // Blink red LED
    digitalWrite(LED_RED, LOW);
    delay(100);
    digitalWrite(LED_RED, HIGH);
    delay(100);
    
    // Blink green LED
    digitalWrite(LED_GREEN, LOW);
    delay(100);
    digitalWrite(LED_GREEN, HIGH);
    delay(100);
    
    // Blink blue LED
    digitalWrite(LED_BLUE, LOW);
    delay(100);
    digitalWrite(LED_BLUE, HIGH);
  #else
    digitalWrite(LED_BUILTIN, LOW);
    delay(100);
    digitalWrite(LED_BUILTIN, HIGH);
  #endif
  
  delay(1400); // Total ~2 seconds with LED blinks
}
