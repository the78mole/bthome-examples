#include <Arduino.h>
#include <BLEDevice.h>
#include <BLEUtils.h>
#include <BLEServer.h>
#include <BLEAdvertising.h>
#include <Adafruit_NeoPixel.h>

// BLE configuration
#define BLE_DEVICE_NAME "MAKE-ESP32-S3"
#define BLE_ADVERTISING_INTERVAL_MS 1000

// RGB LED configuration
#define RGB_LED_PIN 48        // GPIO48 für ESP32-S3 DevKitC-1
#define RGB_LED_COUNT 1       // Nur eine LED
#define RGB_LED_BRIGHTNESS 50 // 0-255, niedrig für Augenschonung

// Manufacturer data - Company ID 0xFFFF + Custom data
const uint8_t MANUFACTURER_DATA[6] = {0xFF, 0xFF, 0x01, 0x02, 0x03, 0x04};

// Global BLE objects
BLEAdvertising *pAdvertising = nullptr;

// RGB LED object
Adafruit_NeoPixel rgbLed(RGB_LED_COUNT, RGB_LED_PIN, NEO_GRB + NEO_KHZ800);

void setupBLE()
{
  Serial.println("Initializing BLE...");
  
  // Initialize BLE
  BLEDevice::init(BLE_DEVICE_NAME);
  
  // Create BLE Server (needed for advertising)
  BLEServer *pServer = BLEDevice::createServer();
  
  // Get advertising object
  pAdvertising = BLEDevice::getAdvertising();
  
  // Set advertising data
  BLEAdvertisementData advertisementData;
  advertisementData.setFlags(0x06); // BR_EDR_NOT_SUPPORTED | LE General Discoverable Mode
  advertisementData.setName(BLE_DEVICE_NAME);
  
  // Set manufacturer data
  advertisementData.setManufacturerData(
    std::string(reinterpret_cast<const char*>(MANUFACTURER_DATA), sizeof(MANUFACTURER_DATA))
  );
  
  pAdvertising->setAdvertisementData(advertisementData);
  
  // Set scan response data (optional)
  BLEAdvertisementData scanResponseData;
  scanResponseData.setCompleteServices(BLEUUID((uint16_t)0x180A)); // Device Information Service
  pAdvertising->setScanResponseData(scanResponseData);
  
  // Set advertising interval
  pAdvertising->setMinInterval(BLE_ADVERTISING_INTERVAL_MS);
  pAdvertising->setMaxInterval(BLE_ADVERTISING_INTERVAL_MS);
  
  // Start advertising
  pAdvertising->start();
  
  Serial.println("BLE Advertising started!");
  Serial.print("Device Name: ");
  Serial.println(BLE_DEVICE_NAME);
  Serial.print("Manufacturer Data: ");
  for (int i = 0; i < sizeof(MANUFACTURER_DATA); i++) {
    if (MANUFACTURER_DATA[i] < 0x10) Serial.print("0");
    Serial.print(MANUFACTURER_DATA[i], HEX);
    if (i < sizeof(MANUFACTURER_DATA) - 1) Serial.print(" ");
  }
  Serial.println();
}

void setup()
{
  // Initialize RGB LED
  rgbLed.begin();
  rgbLed.setBrightness(RGB_LED_BRIGHTNESS);
  rgbLed.clear();
  rgbLed.show();
  
  // Initialize built-in LED
  #ifdef LED_BUILTIN
    pinMode(LED_BUILTIN, OUTPUT);
    digitalWrite(LED_BUILTIN, LOW);
  #endif
  
  // Start Serial - Hardware UART doesn't need delays
  Serial.begin(115200);
  delay(100);
  
  Serial.println();
  Serial.println("=================================");
  Serial.println("BLE Advertisement Example");
  Serial.println("ESP32-S3 DevKitC-1");
  Serial.println("=================================");
  Serial.println();
  
  // Initialize BLE advertising
  Serial.println("Initializing BLE...");
  setupBLE();
  
  Serial.println();
  Serial.println("Setup complete!");
  Serial.println("Advertising continuously...");
}

void loop()
{
  // Blinke blau bei jedem Advertisement
  rgbLed.setPixelColor(0, rgbLed.Color(0, 0, 255)); // Blau
  rgbLed.show();
  delay(50); // Kurz anzeigen
  
  rgbLed.clear(); // Ausschalten
  rgbLed.show();
  
  // Warte bis zum nächsten Advertisement (1000ms Intervall - 50ms bereits abgelaufen)
  delay(BLE_ADVERTISING_INTERVAL_MS - 50);
}
