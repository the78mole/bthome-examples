# BLE Advertisement Example

Dies ist ein einfaches Beispiel für BLE (Bluetooth Low Energy) Advertisement mit ESP32-C3 und nRF52840 Mikrocontrollern.

## Hardware-Anforderungen

Eines der folgenden Boards:
- **ESP32-C3**: ESP32-C3 Development Board (z.B. ESP32-C3-DevKitM-1)
- **nRF52840**: nRF52840 Development Board (z.B. Adafruit Feather nRF52840 Express)
- USB Kabel für Programmierung und Stromversorgung

## Funktionalität

Dieses Beispiel demonstriert:
- Initialisierung des BLE-Stacks auf beiden Plattformen
- Erstellen und Senden von BLE Advertisement Packets
- Setzen von Device Name und Manufacturer Data
- Kontinuierliches Broadcasting von BLE Advertisements
- Plattform-spezifischer Code mit Preprocessor-Direktiven

## Multi-Platform Architektur

Dieses Beispiel verwendet ein **Single-Source-Design** mit plattformspezifischem Code:
- Eine `main.cpp` Datei für beide Plattformen
- Verwendung von `#ifdef PLATFORM_ESP32` und `#ifdef PLATFORM_NRF52` für plattformspezifischen Code
- Gemeinsame `platformio.ini` mit mehreren Umgebungen

## BLE Advertisement Details

### ESP32-C3 (env:esp32-c3-devkitm-1)
- **Device Name**: ESP32-C3-BLE
- **Library**: Arduino BLE (ESP32 native)
- **Manufacturer Data**: 0xFFFF (Company ID) + 0x01020304 (Custom Data)
- **Advertising Interval**: 1000ms
- **Flags**: BR_EDR_NOT_SUPPORTED | LE General Discoverable Mode

### nRF52840 (env:adafruit_feather_nrf52840)
- **Device Name**: nRF52840-BLE
- **Library**: Adafruit Bluefruit
- **Manufacturer Data**: 0xFFFF (Company ID) + 0x01020304 (Custom Data)
- **Advertising Interval**: 1000ms (1600 * 0.625ms)
- **TX Power**: +4 dBm
- **Flags**: LE General Discoverable Mode

## Kompilieren und Hochladen

### Standard-Plattform (ESP32-C3):

```bash
cd examples/01-ble-advertisement
pio run -t upload
pio device monitor
```

### Spezifische Plattform auswählen:

```bash
# Für ESP32-C3
pio run -e esp32-c3-devkitm-1 -t upload

# Für nRF52840
pio run -e adafruit_feather_nrf52840 -t upload
```

### Beide Plattformen bauen:

```bash
# Beide Umgebungen kompilieren
pio run

# Beide Umgebungen hochladen (Board muss jeweils angeschlossen sein)
pio run -t upload
```

### Mit VSCode:

1. Öffne den Workspace in VSCode mit DevContainer
2. Öffne das Projekt-Verzeichnis
3. Wähle die gewünschte Umgebung in der PlatformIO-Toolbar
4. Verwende die PlatformIO-Buttons zum Kompilieren und Hochladen

**Für nRF52840**: Möglicherweise musst du das Board in den Bootloader-Modus versetzen (Doppelklick auf Reset-Button).

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

### ESP32-C3:
```
Starting BLE Advertisement Example for ESP32-C3
BLE Advertising started!
Device Name: ESP32-C3-BLE
Manufacturer Data: FF FF 01 02 03 04
Still advertising...
```

### nRF52840:
```
Starting BLE Advertisement Example for nRF52840
BLE Advertising started!
Device Name: nRF52840-BLE
Manufacturer Data: FF FF 01 02 03 04
Still advertising...
```

## Code-Struktur

```cpp
// Plattform-spezifische Includes
#ifdef PLATFORM_ESP32
  #include <BLEDevice.h>
  // ESP32-spezifischer Code
#endif

#ifdef PLATFORM_NRF52
  #include <bluefruit.h>
  // nRF52-spezifischer Code
#endif

void setup() {
  // Gemeinsamer Initialisierungscode
  
  #ifdef PLATFORM_ESP32
    // ESP32-spezifische Initialisierung
  #endif
  
  #ifdef PLATFORM_NRF52
    // nRF52-spezifische Initialisierung
  #endif
}
```

## Nächste Schritte

Dieses Beispiel dient als Grundlage für komplexere BLE-Anwendungen:
- Hinzufügen von BThome-Format zu den Advertisement Data
- Senden von Sensor-Daten
- Implementierung von Power Management
- Verwendung von erweiterten BLE Features
