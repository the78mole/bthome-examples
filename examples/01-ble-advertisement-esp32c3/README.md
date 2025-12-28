# BLE Advertisement Example - ESP32-C3

Dies ist ein einfaches Beispiel für BLE (Bluetooth Low Energy) Advertisement mit einem ESP32-C3 Mikrocontroller.

## Hardware-Anforderungen

- ESP32-C3 Development Board (z.B. ESP32-C3-DevKitM-1)
- USB-C Kabel für Programmierung und Stromversorgung

## Funktionalität

Dieses Beispiel demonstriert:
- Initialisierung des BLE-Stacks auf dem ESP32-C3
- Erstellen und Senden von BLE Advertisement Packets
- Setzen von Device Name und Manufacturer Data
- Kontinuierliches Broadcasting von BLE Advertisements

## BLE Advertisement Details

- **Device Name**: ESP32-C3-BLE
- **Manufacturer Data**: 0xFFFF (Company ID) + 0x01020304 (Custom Data)
- **Advertising Interval**: 1000ms
- **Flags**: BR_EDR_NOT_SUPPORTED | LE General Discoverable Mode

## Kompilieren und Hochladen

### Mit PlatformIO CLI:

```bash
cd examples/01-ble-advertisement-esp32c3
pio run -t upload
pio device monitor
```

### Mit VSCode:

1. Öffne den Workspace in VSCode mit DevContainer
2. Öffne das Projekt-Verzeichnis
3. Verwende die PlatformIO-Buttons zum Kompilieren und Hochladen

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

Der ESP32-C3 gibt folgende Informationen über die serielle Schnittstelle aus:

```
Starting BLE Advertisement Example for ESP32-C3
BLE Advertising started!
Device Name: ESP32-C3-BLE
Manufacturer Data: FF FF 01 02 03 04
Still advertising...
```

## Nächste Schritte

Dieses Beispiel dient als Grundlage für komplexere BLE-Anwendungen:
- Hinzufügen von BThome-Format zu den Advertisement Data
- Senden von Sensor-Daten
- Implementierung von BLE Scan Response
- Power Management für batteriebetriebene Anwendungen
