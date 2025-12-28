# Quick Start Guide

Schnellstart-Anleitung für die Arbeit mit den BThome-Beispielen.

## Voraussetzungen

1. [Docker Desktop](https://www.docker.com/products/docker-desktop) installiert und gestartet
2. [Visual Studio Code](https://code.visualstudio.com/) installiert
3. [Dev Containers Extension](https://marketplace.visualstudio.com/items?itemName=ms-vscode-remote.remote-containers) in VSCode installiert

## Schritt 1: Repository klonen

```bash
git clone https://github.com/the78mole/bthome-examples.git
cd bthome-examples
```

## Schritt 2: In VSCode öffnen

```bash
code .
```

Oder öffne VSCode und wähle **File → Open Folder** und navigiere zum Repository-Ordner.

## Schritt 3: Im DevContainer öffnen

Wenn VSCode das Projekt öffnet, sollte eine Benachrichtigung erscheinen:

**"Folder contains a Dev Container configuration file. Reopen folder to develop in a container"**

Klicke auf **"Reopen in Container"**.

Alternativ:
1. Drücke `F1` oder `Ctrl+Shift+P` (Windows/Linux) / `Cmd+Shift+P` (Mac)
2. Suche nach **"Dev Containers: Reopen in Container"**
3. Wähle den Befehl aus

**Beim ersten Mal** kann das Erstellen des Containers 5-10 Minuten dauern, da Docker das Image erstellt und PlatformIO installiert wird. Bei späteren Starts geht es deutlich schneller.

## Schritt 4: Warten auf Container-Initialisierung

VSCode zeigt den Fortschritt in der unteren rechten Ecke an:
- "Starting Dev Container..."
- "Building image..."
- "Running postCreateCommand..."

Wenn der Prozess abgeschlossen ist, siehst du **"Dev Container: BThome Examples - PlatformIO"** in der unteren linken Ecke.

## Schritt 5: Ein Beispiel kompilieren

### Mit der PlatformIO-Toolbar:

1. Öffne eines der Beispiel-Verzeichnisse in der Seitenleiste
2. Am unteren Rand von VSCode siehst du die PlatformIO-Toolbar
3. Klicke auf das **✓ (Häkchen-Symbol)** um zu kompilieren

### Mit dem Terminal:

1. Öffne ein Terminal in VSCode (`Ctrl+`` oder Terminal → New Terminal`)
2. Navigiere zum Beispiel:
   ```bash
   cd examples/01-ble-advertisement-esp32c3
   ```
3. Kompiliere das Projekt:
   ```bash
   pio run
   ```

## Schritt 6: Auf Hardware hochladen

1. Verbinde dein ESP32-C3 oder nRF52840 Board per USB
2. In VSCode:
   - Klicke auf **→ (Pfeil-Symbol)** in der PlatformIO-Toolbar
   - Oder im Terminal: `pio run -t upload`

**Für nRF52840**: Möglicherweise musst du das Board in den Bootloader-Modus versetzen (Doppelklick auf Reset-Button).

## Schritt 7: Serielle Ausgabe anzeigen

- Klicke auf **🔌 (Stecker-Symbol)** in der PlatformIO-Toolbar
- Oder im Terminal: `pio device monitor`

Du solltest die Debug-Ausgabe sehen:
```
Starting BLE Advertisement Example...
BLE Advertising started!
...
```

## Testen der BLE-Advertisement

Installiere eine BLE-Scanner-App auf deinem Smartphone:
- **Android**: [nRF Connect](https://play.google.com/store/apps/details?id=no.nordicsemi.android.mcp)
- **iOS**: [nRF Connect](https://apps.apple.com/app/nrf-connect/id1054362403) oder [LightBlue](https://apps.apple.com/app/lightblue/id557428110)

Öffne die App und scanne nach BLE-Geräten. Du solltest dein Gerät sehen:
- **ESP32-C3**: "ESP32-C3-BLE"
- **nRF52840**: "nRF52840-BLE"

## Problemlösung

### Container startet nicht

- Stelle sicher, dass Docker Desktop läuft
- Prüfe die Docker-Logs in VSCode (unten rechts auf "Show Log" klicken)
- Versuche den Container neu zu erstellen: `F1` → "Dev Containers: Rebuild Container"

### PlatformIO findet Board nicht

- **Windows**: Installiere den [USB-Treiber](https://www.silabs.com/developers/usb-to-uart-bridge-vcp-drivers) für CP210x oder CH340
- **Linux**: Füge deinen Benutzer zur Gruppe `dialout` hinzu: `sudo usermod -a -G dialout $USER` (dann neu anmelden)
- **Mac**: Normalerweise keine zusätzlichen Treiber nötig

### Build-Fehler

- Prüfe, ob die richtigen Plattformen installiert sind:
  ```bash
  pio platform list
  ```
- Installiere fehlende Plattformen:
  ```bash
  pio platform install espressif32
  pio platform install nordicnrf52
  ```

## Nächste Schritte

- Lies die [README.md](README.md) für weitere Informationen
- Schaue dir die Beispiel-READMEs in den jeweiligen Verzeichnissen an
- Experimentiere mit den Beispielen und passe sie an deine Bedürfnisse an
- Lerne mehr über [BThome](https://bthome.io/) und erstelle deine eigenen Sensor-Projekte

## Weitere Ressourcen

- [PlatformIO Dokumentation](https://docs.platformio.org/)
- [BThome Spezifikation](https://bthome.io/format/)
- [ESP32-C3 Arduino Dokumentation](https://docs.espressif.com/projects/arduino-esp32/)
- [Adafruit nRF52 Arduino Dokumentation](https://learn.adafruit.com/bluefruit-nrf52-feather-learning-guide)
