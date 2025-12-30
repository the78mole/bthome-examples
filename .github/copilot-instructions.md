# GitHub Copilot Instructions für BThome Examples

## Projekt-Kontext

Dieses Repository enthält Beispielprojekte für BThome (Bluetooth Low Energy Home) Geräte, entwickelt mit PlatformIO. Die Zielplattform ist ESP32-S3.

## Entwicklungsumgebung

- **IDE**: Visual Studio Code mit DevContainer
- **Container Image**: `ghcr.io/the78mole/platformio:latest`
- **Build-System**: PlatformIO
- **Sprachen**: C++, Arduino Framework
- **Primäre Plattform**: ESP32-S3 (Espressif32)
- **Hardware**: ESP32-S3 DevKitC-1 mit USB-UART Converter
- **Serielle Kommunikation**: Hardware UART über USB-UART Converter (115200 Baud)
- **RGB LED**: WS2812 an GPIO48 (Standard für ESP32-S3 DevKitC-1)

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

#### ESP32-S3 DevKitC-1
- Verwende die Arduino BLE Library (`BLEDevice.h`, `BLEServer.h`, etc.)
- Verwende die BThomev2-Arduino-Bibliothek für BThome-spezifische Funktionen
- **Serielle Kommunikation**: Hardware UART, keine USB CDC Flags benötigt
- Standard-Baudrate: 115200
- Upload-Geschwindigkeit: 921600
- Debug-Level über `CORE_DEBUG_LEVEL` setzen (0-5, Standard: 3)
- **RGB LED**: Adafruit NeoPixel Library für WS2812 an GPIO48
  - Helligkeit: 50 (0-255) für Augenschonung
  - Farbformat: NEO_GRB + NEO_KHZ800
- **Wichtig**: Keine PSRAM-Flags für Boards ohne PSRAM
- **Wichtig**: Keine USB CDC Flags bei Verwendung von USB-UART Converter

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
examples/XX-description/
├── src/
│   └── main.cpp           # Multi-Platform Hauptprogramm
├── platformio.ini         # PlatformIO Konfiguration (beide Plattformen)
└── README.md              # Beispiel-Dokumentation (Deutsch)
```

**Namenskonvention**: `XX-description` (ohne Plattform-Suffix, da Multi-Platform)

### PlatformIO Konfiguration

Standard `platformio.ini` für ESP32-S3 Projekte:
```ini
[platformio]
default_envs = esp32-s3-devkitc-1

[env:esp32-s3-devkitc-1]
platform = espressif32
board = esp32-s3-devkitc-1
framework = arduino

monitor_speed = 115200
upload_speed = 921600

build_flags = 
    -DCORE_DEBUG_LEVEL=3

lib_deps = 
    adafruit/Adafruit NeoPixel @ ^1.12.0
```

**Wichtig**: 
- **Keine USB CDC Flags** bei Verwendung von USB-UART Converter
- **Keine PSRAM Flags** für Boards ohne PSRAM (ESP32-S3-DevKitC-1-N8)
- Upload-Geschwindigkeit: 921600 Baud (schneller als Standard 460800)
- Debug-Level: 0 (keine Logs) bis 5 (sehr verbose), Standard: 3
- Library-Versionen mit `^` für Kompatibilität (z.B. `^1.12.0` = 1.12.0 bis <2.0.0)

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
cd examples/XX-example-name
pio run
```

### Upload und Test

```bash
# Kompilieren und hochladen
pio run -t upload

# Serial Monitor starten
pio device monitor

# Oder kombiniert
pio run -t upload && pio device monitor
```

### Code-Checks

- Stelle sicher, dass der Code ohne Warnungen kompiliert
- Teste auf Hardware (ESP32-S3 DevKitC-1)
- Überprüfe serielle Ausgabe im Monitor
- Bei BLE: Teste mit nRF Connect App (Android/iOS)

## Abhängigkeiten

### Minimale externe Abhängigkeiten

- Bevorzuge eingebaute Libraries
- Für ESP32-S3: Arduino BLE Library (Teil des Frameworks, keine Installation nötig)
- Für RGB LED (WS2812): Adafruit NeoPixel Library (stabil, gut dokumentiert)
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
- [ESP32-S3 Arduino BLE Library](https://github.com/espressif/arduino-esp32/tree/master/libraries/BLE)
- [Adafruit NeoPixel Library](https://github.com/adafruit/Adafruit_NeoPixel)
- [ESP32-S3 DevKitC-1 Dokumentation](https://docs.espressif.com/projects/esp-idf/en/latest/esp32s3/hw-reference/esp32s3/user-guide-devkitc-1.html)
- [Home Assistant BThome Integration](https://www.home-assistant.io/integrations/bthome/)

## Fragen und Unterstützung

Bei Fragen zum Code-Stil oder zur Implementierung:
1. Prüfe existierende Beispiele im Repository
2. Konsultiere die BThome-Spezifikation
3. Siehe PlatformIO und Library-Dokumentationen
