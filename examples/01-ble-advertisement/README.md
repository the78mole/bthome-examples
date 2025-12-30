# BLE Advertisement Example

Dies ist ein einfaches Beispiel für BLE (Bluetooth Low Energy) Advertisement mit ESP32-S3 Mikrocontroller.

## Hardware-Anforderungen

- **ESP32-S3 DevKitC-1**: Espressif ESP32-S3 Development Board
- USB-UART Converter (z.B. CP2102, CH340) für serielle Kommunikation
- USB Kabel für Programmierung und Stromversorgung

**RGB LED**: Das Board verfügt über eine serielle RGB LED (WS2812) am GPIO48, die bei jedem Advertisement blau blinkt.

## Funktionalität

Dieses Beispiel demonstriert:
- Initialisierung des BLE-Stacks auf ESP32-S3
- Erstellen und Senden von BLE Advertisement Packets
- Setzen von Device Name und Manufacturer Data
- Kontinuierliches Broadcasting von BLE Advertisements
- Visuelle Anzeige durch RGB-LED (blinkt blau bei jedem Advertisement)
- Serielle Kommunikation über Hardware UART

## BLE Advertisement Details

### ESP32-S3 DevKitC-1 (env:esp32-s3-devkitc-1)
- **Device Name**: MAKE-ESP32-S3
- **Library**: ESP32 BLE Arduino v2.0.0 (framework-integriert)
- **Manufacturer Data**: 0xFFFF (Company ID) + 0x01020304 (Custom Data)
- **Advertising Interval**: 1000ms
- **Flags**: BR_EDR_NOT_SUPPORTED | LE General Discoverable Mode
- **RGB LED**: GPIO48, WS2812, blinkt 50ms blau bei jedem Advertisement

### Verwendete Libraries
- **ESP32 BLE Arduino**: BLE Stack für ESP32 (Teil des Arduino Frameworks)
- **Adafruit NeoPixel**: v1.15.2 für RGB LED Steuerung

## Kompilieren und Hochladen

### Mit PlatformIO CLI:

```bash
cd examples/01-ble-advertisement
pio run -t upload
pio device monitor
```

### Mit VSCode:

1. Öffne den Workspace in VSCode mit DevContainer
2. Öffne das Projekt-Verzeichnis
3. Verwende die PlatformIO-Buttons zum Kompilieren und Hochladen
4. Öffne den Serial Monitor (115200 Baud)

### Hinweise:
- Upload-Geschwindigkeit: 921600 Baud
- Monitor-Geschwindigkeit: 115200 Baud
- Der ESP32-S3 wird automatisch erkannt und über esptool programmiert

## Testen

Nach dem Hochladen können Sie die BLE Advertisements mit verschiedenen Tools überprüfen:

### Smartphone Apps:
- **nRF Connect** (Android/iOS) - empfohlen
- **BLE Scanner** (Android)
- **LightBlue** (iOS)

### Computer Tools:
- **hcitool** (Linux): `sudo hcitool lescan`
- **BluetoothLE Explorer** (Windows 10+)

## Serielle Ausgabe

```
=================================
BLE Advertisement Example
ESP32-S3 DevKitC-1
=================================

Initializing BLE...
[   562][I][BLEDevice.cpp:577] getAdvertising(): create advertising
BLE Advertising started!
Device Name: MAKE-ESP32-S3
Manufacturer Data: FF FF 01 02 03 04

Setup complete!
Advertising continuously...
```

**Hinweis**: Die Debug-Ausgaben von BLEDevice.cpp sind durch `-DCORE_DEBUG_LEVEL=3` aktiviert.

## Code-Struktur

```cpp
#include <Arduino.h>
#include <BLEDevice.h>
#include <BLEAdvertising.h>
#include <Adafruit_NeoPixel.h>

// BLE Konfiguration
#define BLE_DEVICE_NAME "MAKE-ESP32-S3"
#define BLE_ADVERTISING_INTERVAL_MS 1000

// RGB LED Konfiguration
#define RGB_LED_PIN 48
#define RGB_LED_COUNT 1
#define RGB_LED_BRIGHTNESS 50

Adafruit_NeoPixel rgbLed(RGB_LED_COUNT, RGB_LED_PIN, NEO_GRB + NEO_KHZ800);

void setupBLE() {
  // BLE Initialisierung
  BLEDevice::init(BLE_DEVICE_NAME);
  BLEServer *pServer = BLEDevice::createServer();
  BLEAdvertising *pAdvertising = BLEDevice::getAdvertising();
  // ... Advertisement Konfiguration
  pAdvertising->start();
}

void setup() {
  // RGB LED initialisieren
  rgbLed.begin();
  rgbLed.setBrightness(RGB_LED_BRIGHTNESS);
  
  // Serielle Kommunikation
  Serial.begin(115200);
  
  // BLE starten
  setupBLE();
}

void loop() {
  // Blau blinken bei Advertisement
  rgbLed.setPixelColor(0, rgbLed.Color(0, 0, 255));
  rgbLed.show();
  delay(50);
  rgbLed.clear();
  rgbLed.show();
  delay(950);
}
```

## Nächste Schritte

Dieses Beispiel dient als Grundlage für komplexere BLE-Anwendungen:
- Hinzufügen von BThome-Format zu den Advertisement Data
- Senden von Sensor-Daten
- Implementierung von Power Management
- Verwendung von erweiterten BLE Features
