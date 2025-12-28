# GitHub Copilot Instructions für BThome Examples

## Projekt-Kontext

Dieses Repository enthält Beispielprojekte für BThome (Bluetooth Low Energy Home) Geräte, entwickelt mit PlatformIO. Die Zielplattformen sind ESP32-C3 und nRF52840 Mikrocontroller.

## Entwicklungsumgebung

- **IDE**: Visual Studio Code mit DevContainer
- **Build-System**: PlatformIO
- **Sprachen**: C++, Arduino Framework
- **Plattformen**: ESP32-C3 (Espressif32), nRF52840 (Nordic nRF52)

## Code-Richtlinien

### Allgemein

1. **Sprache**: Kommentare und Dokumentation in Deutsch, Code in Englisch
2. **Formatierung**: 
   - Einrückung: 2 Leerzeichen
   - Klammern: Allman-Stil (Klammern auf neuer Zeile)
   - Maximale Zeilenlänge: 100 Zeichen

3. **Namenskonventionen**:
   - Variablen: camelCase (z.B. `deviceName`, `advertisingInterval`)
   - Konstanten: UPPER_SNAKE_CASE (z.B. `BLE_ADVERTISING_INTERVAL`)
   - Funktionen: camelCase (z.B. `setupBLE()`, `sendAdvertisement()`)
   - Klassen: PascalCase (z.B. `BThomeDevice`, `SensorData`)

### Plattform-spezifische Anforderungen

#### ESP32-C3
- Verwende die Arduino BLE Library (`BLEDevice.h`, `BLEServer.h`, etc.)
- Standard-Baudrate: 115200
- USB CDC aktivieren: `ARDUINO_USB_CDC_ON_BOOT=1`
- Debug-Level über `CORE_DEBUG_LEVEL` setzen

#### nRF52840
- Verwende die Adafruit Bluefruit Library (`bluefruit.h`)
- Include TinyUSB Library für USB-Unterstützung
- Standard-Upload-Protokoll: `nrfutil`
- TX Power: Typisch +4 dBm, maximal +8 dBm

### BLE Advertisement Best Practices

1. **Advertising Interval**: 
   - Standard: 1000ms für kontinuierliches Advertising
   - Batteriebetrieb: 2000-5000ms für längere Batterielebensdauer

2. **Manufacturer Data Format**:
   - Erste 2 Bytes: Company Identifier (Little Endian)
   - Für BThome: Company ID `0xFCD2` (BTHome)
   - Folgende Bytes: BThome-Payload gemäß Spezifikation

3. **Device Name**:
   - Beschreibend und eindeutig
   - Format: `<Plattform>-<Funktion>` (z.B. `ESP32-Temp-Sensor`)

### BThome-Protokoll

Beim Implementieren von BThome-Features:

1. **BThome Version**: Verwende BThome v2 (aktueller Standard)
2. **Object IDs**: Verwende die offiziellen Object IDs aus der BThome-Spezifikation
3. **Datenformat**: Little Endian für alle numerischen Werte
4. **Verschlüsselung**: Optional, aber empfohlen für sensible Daten

Beispiel BThome v2 Payload (unverschlüsselt):
```
0x40              // Device Information (bit 0=Encryption, bit 1-5=Reserved, bit 6=Trigger, bit 7=Reserved)
0x02 0xCA 0x09    // Temperature: 25.06°C (0x09CA = 2506, Factor 0.01)
0x03 0xBF 0x13    // Humidity: 50.55% (0x13BF = 5055, Factor 0.01)
```

### Projekt-Struktur

Neue Beispiele sollten folgende Struktur haben:

```
examples/XX-description-platform/
├── src/
│   └── main.cpp           # Hauptprogramm
├── platformio.ini         # PlatformIO Konfiguration
└── README.md              # Beispiel-Dokumentation (Deutsch)
```

### PlatformIO Konfiguration

Standard `platformio.ini` für ESP32-C3:
```ini
[env:esp32-c3-devkitm-1]
platform = espressif32
board = esp32-c3-devkitm-1
framework = arduino
monitor_speed = 115200
upload_speed = 460800
build_flags = 
    -DCORE_DEBUG_LEVEL=3
    -DARDUINO_USB_CDC_ON_BOOT=1
```

Standard `platformio.ini` für nRF52840:
```ini
[env:adafruit_feather_nrf52840]
platform = nordicnrf52
board = adafruit_feather_nrf52840
framework = arduino
monitor_speed = 115200
upload_protocol = nrfutil
build_flags = 
    -DCFG_DEBUG=2
    -DNRF52840_XXAA
lib_deps = 
    adafruit/Adafruit TinyUSB Library @ ^1.7.0
```

### Dokumentation

Jedes Beispiel benötigt eine README.md mit:

1. **Kurzbeschreibung**: Was das Beispiel demonstriert
2. **Hardware-Anforderungen**: Welche Boards unterstützt werden
3. **Funktionalität**: Detaillierte Beschreibung der Features
4. **BLE Details**: Advertisement-Intervall, Daten-Format, etc.
5. **Kompilierung & Upload**: Schritt-für-Schritt-Anleitung
6. **Test-Anleitung**: Tools zum Testen (nRF Connect, etc.)
7. **Serielle Ausgabe**: Beispiel der erwarteten Konsolen-Ausgabe
8. **Nächste Schritte**: Mögliche Erweiterungen

### Fehlerbehandlung

1. Immer serielle Ausgabe für Debugging verwenden
2. Aussagekräftige Fehlermeldungen in Deutsch
3. Status-Updates während der Initialisierung
4. Regelmäßige "Keep-Alive" Meldungen im Loop

### Security

1. Keine Hardcoded-Credentials oder sensible Daten
2. Bei BThome-Verschlüsselung: Keys sollten zur Build-Zeit eingebunden werden
3. Dokumentiere Sicherheitsaspekte in den README-Dateien

## Build & Test

### Kompilieren testen

Vor dem Commit sollten neue Beispiele kompiliert werden:

```bash
cd examples/XX-example-name-platform
pio run
```

### Code-Checks

- Stelle sicher, dass der Code ohne Warnungen kompiliert
- Teste auf beiden Plattformen (ESP32-C3 und nRF52840), wenn möglich

## Abhängigkeiten

### Minimale externe Abhängigkeiten

- Bevorzuge eingebaute Libraries
- Für ESP32: Arduino BLE Library (Teil des Frameworks)
- Für nRF52840: Adafruit Bluefruit Library (stabile, gut dokumentierte Library)
- Für zusätzliche Sensoren: Bevorzuge Adafruit Libraries (gute Qualität, breite Unterstützung)

### Library-Versionen

- Verwende spezifische Versionen in `lib_deps` (z.B. `@ ^1.7.0`)
- Dokumentiere verwendete Library-Versionen in der README

## Hilfreiche Befehle

```bash
# PlatformIO CLI Befehle
pio run                    # Kompilieren
pio run -t upload          # Hochladen
pio device monitor         # Serieller Monitor
pio run -t clean           # Build-Artefakte löschen

# System-Info
pio system info
pio platform list
pio boards espressif32
pio boards nordicnrf52
```

## Ressourcen

- [BThome Spezifikation](https://bthome.io/format/)
- [PlatformIO Dokumentation](https://docs.platformio.org/)
- [ESP32-C3 Arduino BLE Library](https://github.com/espressif/arduino-esp32/tree/master/libraries/BLE)
- [Adafruit Bluefruit nRF52 Library](https://github.com/adafruit/Adafruit_nRF52_Arduino)
- [Home Assistant BThome Integration](https://www.home-assistant.io/integrations/bthome/)

## Fragen und Unterstützung

Bei Fragen zum Code-Stil oder zur Implementierung:
1. Prüfe existierende Beispiele im Repository
2. Konsultiere die BThome-Spezifikation
3. Siehe PlatformIO und Library-Dokumentationen
