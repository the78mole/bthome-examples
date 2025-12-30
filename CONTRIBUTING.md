# Beiträge zum Projekt

Vielen Dank für dein Interesse, zu diesem Projekt beizutragen! Hier findest du Richtlinien, wie du effektiv beitragen kannst.

## Wie kann ich beitragen?

Es gibt mehrere Möglichkeiten, zum Projekt beizutragen:

1. **Neue Beispiele erstellen**: Füge neue BThome-Beispiele hinzu
2. **Bestehende Beispiele verbessern**: Optimiere Code, füge Features hinzu oder verbessere Dokumentation
3. **Bugs melden**: Erstelle Issues für gefundene Probleme
4. **Dokumentation verbessern**: Hilf, die Dokumentation klarer und hilfreicher zu machen

## Entwicklungsumgebung einrichten

1. Forke das Repository
2. Clone dein Fork:
   ```bash
   git clone https://github.com/DEIN-USERNAME/bthome-examples.git
   cd bthome-examples
   ```
3. Öffne das Projekt in VSCode mit DevContainer (siehe [QUICKSTART.md](QUICKSTART.md))

## Neues Beispiel erstellen

### 1. Verzeichnisstruktur

Erstelle ein neues Verzeichnis unter `examples/` mit folgendem Muster:

```
examples/XX-description/
├── src/
│   └── main.cpp
├── platformio.ini
└── README.md
```

**Namenskonvention**: `XX-description`
- `XX`: Fortlaufende Nummer (01, 02, 03, ...)
- `description`: Kurze Beschreibung des Beispiels (z.B. `ble-advertisement`, `bthome-temperature`)

**Multi-Platform Projekte**: Die Beispiele sollen wenn möglich beide Plattformen (ESP32-C3 und nRF52840) in einem Projekt unterstützen:
- Verwende `#ifdef PLATFORM_ESP32` und `#ifdef PLATFORM_NRF52` für plattformspezifischen Code
- Definiere beide Umgebungen in der `platformio.ini`

### 2. platformio.ini erstellen

Verwende die vorhandenen Beispiele als Vorlage. Für Multi-Platform Projekte:

```ini
[platformio]
default_envs = esp32-c3-devkitm-1

[env:esp32-c3-devkitm-1]
platform = espressif32
board = esp32-c3-devkitm-1
framework = arduino
monitor_speed = 115200
upload_speed = 460800
build_flags = 
    -DCORE_DEBUG_LEVEL=3
    -DARDUINO_USB_CDC_ON_BOOT=1
    -DPLATFORM_ESP32
lib_deps = 
    ; Füge benötigte Libraries hier hinzu

[env:adafruit_feather_nrf52840]
platform = nordicnrf52
board = adafruit_feather_nrf52840
framework = arduino
monitor_speed = 115200
upload_protocol = nrfutil
build_flags = 
    -DCFG_DEBUG=2
    -DNRF52840_XXAA
    -DPLATFORM_NRF52
lib_deps = 
    adafruit/Adafruit TinyUSB Library @ ^1.7.0
    ; Füge benötigte Libraries hier hinzu
```

**Wichtig**: Definiere `PLATFORM_ESP32` und `PLATFORM_NRF52` in den build_flags für plattformspezifischen Code.

### 3. main.cpp schreiben

- **Sprache**: Code in Englisch, Kommentare in Deutsch (für Klarheit)
- **Formatierung**: 2 Leerzeichen Einrückung, Allman-Stil für Klammern
- **Serielle Ausgabe**: Füge Debug-Ausgaben hinzu, um den Status zu zeigen
- **Dokumentation**: Kommentiere wichtige Code-Abschnitte
- **Multi-Platform**: Verwende Preprocessor-Direktiven für plattformspezifischen Code

Beispiel-Struktur für Multi-Platform Code:

```cpp
#include <Arduino.h>

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
  Serial.begin(115200);
  delay(1000);
  
  #ifdef PLATFORM_ESP32
  Serial.println("ESP32 Initialisierung...");
  // ESP32-spezifische Initialisierung
  #endif
  
  #ifdef PLATFORM_NRF52
  Serial.println("nRF52 Initialisierung...");
  // nRF52-spezifische Initialisierung
  #endif
}

void loop() {
  // Gemeinsamer Code für beide Plattformen
  delay(1000);
}
```

### 4. README.md erstellen

Jedes Beispiel benötigt eine detaillierte README.md mit:

```markdown
# Titel des Beispiels

Kurzbeschreibung des Beispiels.

## Hardware-Anforderungen

- Liste der benötigten Hardware für beide Plattformen
- ESP32-C3 Boards
- nRF52840 Boards
- Sensoren, etc.

## Funktionalität

Detaillierte Beschreibung:
- Was das Beispiel tut
- Welche Features implementiert sind
- Technische Details (BLE-Parameter, etc.)

## Kompilieren und Hochladen

### Mit PlatformIO CLI:
```bash
# Standard-Plattform kompilieren
pio run

# Spezifische Plattform kompilieren
pio run -e esp32-c3-devkitm-1
pio run -e adafruit_feather_nrf52840

# Hochladen
pio run -t upload
pio run -e esp32-c3-devkitm-1 -t upload
```

### Mit VSCode:
Wähle die Umgebung in der PlatformIO-Toolbar und verwende die Buttons.

## Testen

Anleitung, wie das Beispiel auf beiden Plattformen getestet werden kann.

## Serielle Ausgabe

Beispiel der erwarteten Konsolen-Ausgabe für beide Plattformen:

### ESP32-C3:
```
Erwartete Ausgabe für ESP32-C3...
```

### nRF52840:
```
Erwartete Ausgabe für nRF52840...
```

## Nächste Schritte

Mögliche Erweiterungen oder verwandte Themen.
```

### 5. Testen

Vor dem Erstellen eines Pull Requests:

1. **Kompiliere das Projekt für beide Plattformen**:
   ```bash
   cd examples/XX-dein-beispiel
   pio run -e esp32-c3-devkitm-1
   pio run -e adafruit_feather_nrf52840
   ```

2. **Teste auf Hardware** (wenn möglich, beide Plattformen):
   ```bash
   pio run -e esp32-c3-devkitm-1 -t upload
   pio device monitor
   
   pio run -e adafruit_feather_nrf52840 -t upload
   pio device monitor
   ```

3. **Prüfe die Dokumentation**:
   - Ist die README vollständig?
   - Sind alle Schritte klar beschrieben?
   - Funktionieren alle Code-Beispiele?

## Code-Stil

Siehe [.github/copilot-instructions.md](.github/copilot-instructions.md) für detaillierte Code-Stil-Richtlinien.

### Wichtigste Punkte:

- **Einrückung**: 2 Leerzeichen (keine Tabs)
- **Klammern**: Allman-Stil (öffnende Klammer auf neuer Zeile)
- **Namenskonventionen**:
  - Variablen: `camelCase`
  - Konstanten: `UPPER_SNAKE_CASE`
  - Funktionen: `camelCase`
- **Kommentare**: Deutsch für Erklärungen, Englisch für Code-Dokumentation
- **Maximale Zeilenlänge**: 100 Zeichen

## Pull Request erstellen

1. **Erstelle einen Branch**:
   ```bash
   git checkout -b feature/mein-neues-beispiel
   ```

2. **Committe deine Änderungen**:
   ```bash
   git add .
   git commit -m "Füge Beispiel für XYZ hinzu"
   ```

3. **Push zum Fork**:
   ```bash
   git push origin feature/mein-neues-beispiel
   ```

4. **Erstelle Pull Request** auf GitHub:
   - Beschreibe, was dein Beispiel tut
   - Füge Screenshots oder Beispiel-Ausgaben hinzu
   - Verweise auf relevante Issues (falls vorhanden)

## Pull Request Checkliste

Bevor du einen Pull Request einreichst, stelle sicher:

- [ ] Code kompiliert ohne Fehler
- [ ] Code wurde (wenn möglich) auf Hardware getestet
- [ ] Alle neuen Dateien sind enthalten
- [ ] README.md ist vollständig und korrekt
- [ ] Code folgt den Stil-Richtlinien
- [ ] Keine unnötigen Dateien (Build-Artefakte, etc.) enthalten
- [ ] Commit-Messages sind aussagekräftig
- [ ] Changes sind in `examples/` oder Dokumentation (keine Core-Änderungen ohne Diskussion)

## Issues melden

Wenn du einen Bug findest oder eine Verbesserung vorschlagen möchtest:

1. **Prüfe**, ob ein ähnliches Issue bereits existiert
2. **Erstelle ein neues Issue** mit:
   - Klare Beschreibung des Problems/Vorschlags
   - Schritte zur Reproduktion (bei Bugs)
   - Erwartetes vs. tatsächliches Verhalten
   - Hardware/Software-Versionen
   - Serielle Ausgabe oder Fehler-Logs (falls relevant)

## Fragen?

Bei Fragen oder Unklarheiten:
- Öffne ein Issue mit dem Label `question`
- Schaue dir existierende Beispiele als Referenz an
- Konsultiere die [Copilot Instructions](.github/copilot-instructions.md)

## Code of Conduct

Sei respektvoll und konstruktiv in allen Interaktionen. Dieses Projekt soll eine freundliche und einladende Umgebung für alle sein.

## Lizenz

Mit dem Beitragen zum Projekt stimmst du zu, dass deine Beiträge unter der [MIT-Lizenz](LICENSE) lizenziert werden.
