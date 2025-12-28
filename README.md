# BThome Examples

Beispiel-Projekte für BThome (Bluetooth Low Energy Home) auf Basis von PlatformIO.

> **🚀 Neu hier?** Siehe [Quick Start Guide](QUICKSTART.md) für eine Schritt-für-Schritt-Anleitung!

## Überblick

Dieses Repository enthält mehrere Beispielprojekte, die zeigen, wie man BLE-Geräte mit verschiedenen Mikrocontrollern implementiert. Die Beispiele beginnen mit grundlegenden BLE Advertisement Funktionen und führen schrittweise zu vollständigen BThome-Implementierungen.

## Unterstützte Hardware

- **ESP32-C3**: Espressif ESP32-C3 Development Boards
- **nRF52840**: Nordic nRF52840 Development Boards (z.B. Adafruit Feather nRF52840)

## Entwicklungsumgebung

Dieses Projekt verwendet VSCode mit einem DevContainer, der alle notwendigen Tools für die Entwicklung mit PlatformIO enthält.

### Voraussetzungen

- [Docker](https://www.docker.com/products/docker-desktop)
- [Visual Studio Code](https://code.visualstudio.com/)
- [Dev Containers Extension](https://marketplace.visualstudio.com/items?itemName=ms-vscode-remote.remote-containers)

### Erste Schritte

1. Repository klonen:
   ```bash
   git clone https://github.com/the78mole/bthome-examples.git
   cd bthome-examples
   ```

2. In VSCode öffnen:
   ```bash
   code .
   ```

3. Wenn VSCode startet, erscheint eine Benachrichtigung "Reopen in Container" - klicken Sie darauf
   - Alternativ: `Ctrl+Shift+P` → "Dev Containers: Reopen in Container"

4. Warten Sie, bis der Container erstellt und gestartet ist (beim ersten Mal kann dies einige Minuten dauern)

5. Navigieren Sie zu einem Beispiel-Projekt und kompilieren Sie es

## Beispiel-Projekte

### 01 - BLE Advertisement

Grundlegende BLE Advertisement Implementierung ohne BThome-Protokoll.

- **[ESP32-C3 Version](examples/01-ble-advertisement-esp32c3/README.md)**: Verwendet die ESP32 Arduino BLE Library
- **[nRF52840 Version](examples/01-ble-advertisement-nrf52840/README.md)**: Verwendet die Adafruit Bluefruit Library

**Features:**
- BLE Device Name setzen
- Manufacturer Data senden
- Kontinuierliches Advertising
- Serielle Debug-Ausgabe

### Weitere Beispiele (geplant)

- 02 - BThome v2 Basic (Temperatur und Luftfeuchtigkeit)
- 03 - BThome v2 mit verschlüsseltem Payload
- 04 - BThome v2 mit Battery Service
- 05 - BThome v2 Multi-Sensor (Temperatur, Luftfeuchtigkeit, Luftdruck)

## Entwicklung

### Ein Projekt kompilieren

Mit PlatformIO CLI:
```bash
cd examples/01-ble-advertisement-esp32c3
pio run
```

### Ein Projekt hochladen

```bash
cd examples/01-ble-advertisement-esp32c3
pio run -t upload
```

### Serielle Ausgabe überwachen

```bash
pio device monitor
```

### Mit VSCode

Verwenden Sie die PlatformIO-Toolbar am unteren Bildschirmrand:
- ✓ (Häkchen): Kompilieren
- → (Pfeil): Hochladen
- 🔌 (Stecker): Seriellen Monitor öffnen

## Struktur

```
bthome-examples/
├── .devcontainer/          # DevContainer Konfiguration
│   ├── devcontainer.json   # VSCode DevContainer Setup
│   └── Dockerfile          # Container mit PlatformIO
├── examples/               # Beispiel-Projekte
│   ├── 01-ble-advertisement-esp32c3/
│   │   ├── src/
│   │   │   └── main.cpp
│   │   ├── platformio.ini
│   │   └── README.md
│   └── 01-ble-advertisement-nrf52840/
│       ├── src/
│       │   └── main.cpp
│       ├── platformio.ini
│       └── README.md
├── .gitignore
├── LICENSE
└── README.md
```

## BThome Protokoll

BThome ist ein energieeffizientes Bluetooth Low Energy Datenformat für Sensordaten, das für Home Assistant optimiert ist. Weitere Informationen:

- [BThome Website](https://bthome.io/)
- [BThome Format Spezifikation](https://bthome.io/format/)
- [Home Assistant BThome Integration](https://www.home-assistant.io/integrations/bthome/)

## Lizenz

Dieses Projekt ist unter der MIT-Lizenz lizenziert - siehe [LICENSE](LICENSE) Datei für Details.

## Autor

Daniel Glaser

## Beiträge

Beiträge sind willkommen! Bitte öffnen Sie ein Issue oder einen Pull Request.
