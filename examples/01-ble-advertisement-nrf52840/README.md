# BLE Advertisement Example - nRF52840

Dies ist ein einfaches Beispiel für BLE (Bluetooth Low Energy) Advertisement mit einem nRF52840 Mikrocontroller.

## Hardware-Anforderungen

- nRF52840 Development Board (z.B. Adafruit Feather nRF52840 Express)
- USB Kabel für Programmierung und Stromversorgung

## Funktionalität

Dieses Beispiel demonstriert:
- Initialisierung des BLE-Stacks auf dem nRF52840 mit Adafruit Bluefruit Library
- Erstellen und Senden von BLE Advertisement Packets
- Setzen von Device Name und Manufacturer Data
- Kontinuierliches Broadcasting von BLE Advertisements

## BLE Advertisement Details

- **Device Name**: nRF52840-BLE
- **Manufacturer Data**: 0xFFFF (Company ID) + 0x01020304 (Custom Data)
- **Advertising Interval**: 1000ms
- **TX Power**: +4 dBm (Maximum)
- **Flags**: LE General Discoverable Mode

## Kompilieren und Hochladen

### Mit PlatformIO CLI:

```bash
cd examples/01-ble-advertisement-nrf52840
pio run -t upload
pio device monitor
```

### Mit VSCode:

1. Öffne den Workspace in VSCode mit DevContainer
2. Öffne das Projekt-Verzeichnis
3. Verwende die PlatformIO-Buttons zum Kompilieren und Hochladen

**Hinweis**: Für das nRF52840 kann es notwendig sein, das Board in den Bootloader-Modus zu versetzen:
- Doppelklick auf den Reset-Button
- Die LED sollte rot/grün blinken
- Das Board erscheint als USB-Laufwerk

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

Der nRF52840 gibt folgende Informationen über die serielle Schnittstelle aus:

```
Starting BLE Advertisement Example for nRF52840
BLE Advertising started!
Device Name: nRF52840-BLE
Manufacturer Data: FF FF 01 02 03 04
Still advertising...
```

## Besonderheiten nRF52840

Der nRF52840 bietet:
- Hervorragende BLE-Performance mit niedrigem Stromverbrauch
- Native USB-Unterstützung
- Integrierte Bluetooth 5.0 Features
- TX Power bis zu +8 dBm (in diesem Beispiel +4 dBm)

## Nächste Schritte

Dieses Beispiel dient als Grundlage für komplexere BLE-Anwendungen:
- Hinzufügen von BThome-Format zu den Advertisement Data
- Senden von Sensor-Daten
- Implementierung von Power Management
- Verwendung der erweiterten Bluetooth 5.0 Features
