#include <Adafruit_NeoPixel.h>
#include <Arduino.h>
#include <BLEAdvertising.h>
#include <BLEDevice.h>
#include <BLEServer.h>
#include <BLEUtils.h>

// ESP32-S3 Temperature Sensor API
#include "driver/temp_sensor.h"

// BLE configuration
#define BLE_DEVICE_NAME "MAKE-ESP32-S3-TS"
#define BLE_ADVERTISING_INTERVAL_MS \
  5000                            // Alle 5 Sekunden für Batterieeffizienz
#define BTHOME_COMPANY_ID 0xFCD2  // BTHome Company ID (Little Endian)

// RGB LED configuration
#define RGB_LED_PIN 48         // GPIO48 für ESP32-S3 DevKitC-1
#define RGB_LED_COUNT 1        // Nur eine LED
#define RGB_LED_BRIGHTNESS 50  // 0-255, niedrig für Augenschonung

// Temperature measurement configuration
#define TEMP_MEASUREMENT_INTERVAL_MS 5000  // Alle 5 Sekunden messen
#define TEMP_CONVERSION_FACTOR 0.01        // BThome verwendet 0.01°C Auflösung

// Global BLE objects
BLEAdvertising* pAdvertising = nullptr;

// RGB LED object
Adafruit_NeoPixel rgbLed(RGB_LED_COUNT, RGB_LED_PIN, NEO_GRB + NEO_KHZ800);

// Timing variables
unsigned long lastTempMeasurement = 0;

/**
 * Liest die interne Temperatur des ESP32-S3 aus
 * @return Temperatur in °C (float)
 */
float readInternalTemperature() {
  // ESP32-S3 interner Temperatursensor
  static bool tempSensorInitialized = false;

  // Initialisiere Temperatursensor beim ersten Aufruf
  if (!tempSensorInitialized) {
    temp_sensor_config_t temp_sensor_config = TSENS_CONFIG_DEFAULT();
    temp_sensor_set_config(temp_sensor_config);
    temp_sensor_start();
    tempSensorInitialized = true;
  }

  // Temperatur auslesen
  float tempC = 0.0;
  temp_sensor_read_celsius(&tempC);

  return tempC;
}

/**
 * Erstellt ein BThome v2 Advertisement-Paket mit Temperaturdaten
 * @param tempC Temperatur in °C
 * @param data Buffer für die Manufacturer Data
 * @return Länge der Manufacturer Data
 */
size_t createBThomePacket(float tempC, uint8_t* data) {
  size_t index = 0;

  // Company ID (Little Endian): 0xFCD2
  data[index++] = 0xD2;
  data[index++] = 0xFC;

  // BThome Device Information Byte
  // Bit 0: Encryption (0 = unverschlüsselt)
  // Bit 1-5: Reserved (0)
  // Bit 6: Trigger (0 = normale Messung)
  // Bit 7: Reserved (0)
  data[index++] = 0x40;  // 0b01000000 = BThome v2, unverschlüsselt

  // Temperature Object ID: 0x02
  data[index++] = 0x02;

  // Temperatur als signed int16 in 0.01°C Auflösung (Little Endian)
  int16_t tempValue = (int16_t)(tempC * 100);  // z.B. 25.06°C -> 2506
  data[index++] = tempValue & 0xFF;            // Low Byte
  data[index++] = (tempValue >> 8) & 0xFF;     // High Byte

  return index;
}

/**
 * Aktualisiert das BLE Advertisement mit neuen Temperaturdaten
 */
void updateBLEAdvertisement(float tempC) {
  if (pAdvertising == nullptr) {
    Serial.println("FEHLER: BLE Advertising nicht initialisiert!");
    return;
  }

  // BThome Paket erstellen
  uint8_t manufacturerData[10];
  size_t dataLen = createBThomePacket(tempC, manufacturerData);

  // Advertisement stoppen
  pAdvertising->stop();

  // Neues Advertisement erstellen
  BLEAdvertisementData advertisementData;
  advertisementData.setFlags(
      0x06);  // BR_EDR_NOT_SUPPORTED | LE General Discoverable Mode
  advertisementData.setName(BLE_DEVICE_NAME);

  // BThome Manufacturer Data setzen
  advertisementData.setManufacturerData(
      std::string(reinterpret_cast<const char*>(manufacturerData), dataLen));

  pAdvertising->setAdvertisementData(advertisementData);

  // Advertisement neu starten
  pAdvertising->start();

  // Debug-Ausgabe
  Serial.print("BLE Advertisement aktualisiert - Temperatur: ");
  Serial.print(tempC, 2);
  Serial.print("°C | BThome Payload: ");
  for (size_t i = 0; i < dataLen; i++) {
    if (manufacturerData[i] < 0x10) Serial.print("0");
    Serial.print(manufacturerData[i], HEX);
    if (i < dataLen - 1) Serial.print(" ");
  }
  Serial.println();
}

/**
 * Initialisiert BLE mit BThome Advertisement
 */
void setupBLE() {
  Serial.println("Initializing BLE...");

  // Initialize BLE
  BLEDevice::init(BLE_DEVICE_NAME);

  // Create BLE Server (needed for advertising)
  BLEServer* pServer = BLEDevice::createServer();

  // Get advertising object
  pAdvertising = BLEDevice::getAdvertising();

  // Set advertising interval
  pAdvertising->setMinInterval(BLE_ADVERTISING_INTERVAL_MS);
  pAdvertising->setMaxInterval(BLE_ADVERTISING_INTERVAL_MS);

  Serial.println("BLE erfolgreich initialisiert!");
  Serial.print("Device Name: ");
  Serial.println(BLE_DEVICE_NAME);
  Serial.print("Advertising Interval: ");
  Serial.print(BLE_ADVERTISING_INTERVAL_MS);
  Serial.println(" ms");
}

/**
 * Zeigt einen Farbverlauf auf der RGB LED
 * @param hue Farbton (0-65535)
 */
void showRainbow(uint16_t hue) {
  uint32_t color = rgbLed.ColorHSV(hue, 255, 255);
  rgbLed.setPixelColor(0, color);
  rgbLed.show();
}

void setup() {
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
  Serial.println("BThome Temperatursensor Example");
  Serial.println("ESP32-S3 DevKitC-1");
  Serial.println("=================================");
  Serial.println();

  // Initialize BLE advertising
  setupBLE();

  // Erste Temperaturmessung und Advertisement
  float tempC = readInternalTemperature();
  Serial.print("Initiale Temperatur: ");
  Serial.print(tempC, 2);
  Serial.println("°C");

  updateBLEAdvertisement(tempC);

  // RGB LED: Grün für bereit
  rgbLed.setPixelColor(0, rgbLed.Color(0, 255, 0));
  rgbLed.show();

  Serial.println();
  Serial.println("System bereit! Sende BThome Temperature Advertisements...");
  Serial.println();
}

void loop() {
  unsigned long currentMillis = millis();

  // Temperatur messen und Advertisement aktualisieren
  if (currentMillis - lastTempMeasurement >= TEMP_MEASUREMENT_INTERVAL_MS) {
    lastTempMeasurement = currentMillis;

    // Temperatur messen
    float tempC = readInternalTemperature();

    // Advertisement aktualisieren
    updateBLEAdvertisement(tempC);

    // RGB LED: Kurzes Aufblitzen in Blau
    rgbLed.setPixelColor(0, rgbLed.Color(0, 0, 255));
    rgbLed.show();
    delay(50);
    rgbLed.setPixelColor(0, rgbLed.Color(0, 255, 0));
    rgbLed.show();
  }

  // LED-Animation: Langsamer Regenbogen-Effekt
  static uint16_t hue = 0;
  hue += 50;
  if (hue >= 65536) hue = 0;

  delay(50);
}
