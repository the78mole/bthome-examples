# 02 - BThome Temperatursensor

## Kurzbeschreibung

Dieses Beispiel demonstriert die Verwendung des internen Temperatursensors des ESP32-S3 in Kombination mit dem BThome v2 Protokoll. Die gemessene Temperatur wird über BLE Advertisements im BThome-Format gesendet und kann von Home Assistant automatisch erkannt werden.

## Hardware-Anforderungen

### Unterstützte Boards

- **ESP32-S3 DevKitC-1** (primäres Ziel)
  - Interner Temperatursensor
  - WS2812 RGB LED an GPIO48
  - USB-UART Converter für serielle Kommunikation

## Funktionalität

### BThome Temperatursensor

Das Beispiel implementiert einen vollständigen BThome v2 Temperatursensor:

1. **Temperatursensor**: Nutzt den internen Temperatursensor des ESP32-S3
2. **BThome v2 Protokoll**: Sendet Temperaturdaten im offiziellen BThome v2 Format
3. **BLE Advertisement**: Kontinuierliche Advertisements alle 5 Sekunden (batterieeffizient)
4. **Home Assistant Ready**: Automatische Integration in Home Assistant möglich
5. **RGB LED Feedback**: Visuelles Feedback bei Temperaturmessungen

### BThome Paket-Format

Das Advertisement enthält folgende Daten:

```
Manufacturer Data:
0xD2 0xFC          // Company ID: 0xFCD2 (BTHome, Little Endian)
0x40               // Device Info: BThome v2, unverschlüsselt
0x02               // Object ID: Temperature (signed int16, 0.01°C)
0xXX 0xXX          // Temperaturwert (Little Endian, z.B. 0xCA 0x09 = 2506 = 25.06°C)
```

### BLE Details

- **Device Name**: `ESP32-TempSensor`
- **Advertising Interval**: 5000ms (5 Sekunden)
- **Company ID**: 0xFCD2 (BTHome)
- **Temperatur-Auflösung**: 0.01°C
- **Format**: BThome v2, unverschlüsselt

### RGB LED Status

- **Grün**: System bereit, sendet Advertisements
- **Blau (kurz)**: Temperaturmessung durchgeführt
- **Regenbogen**: Langsamer Farbverlauf im Hintergrund

### Temperatursensor

Der ESP32-S3 hat einen internen Temperatursensor, der die Chip-Temperatur misst:

- **Messbereich**: Ca. -40°C bis +125°C
- **Genauigkeit**: ±2-3°C (ungekalibriert)
- **Hinweis**: Misst die interne Chip-Temperatur, nicht die Umgebungstemperatur
- **Verwendung**: Ideal für Demonstrations- und Test-Zwecke

## Kompilierung & Upload

### Mit PlatformIO (empfohlen)

```bash
# In das Projekt-Verzeichnis wechseln
cd examples/02-bthome-tempsensor

# Kompilieren
pio run

# Kompilieren und hochladen
pio run -t upload

# Serial Monitor starten
pio device monitor

# Oder kombiniert
pio run -t upload && pio device monitor
```

### Für ESP32-S3 DevKitC-1

```bash
# Explizit für ESP32-S3 kompilieren
pio run -e esp32-s3-devkitc-1

# Upload
pio run -e esp32-s3-devkitc-1 -t upload
```

## Test-Anleitung

### 1. Serielle Ausgabe überprüfen

Nach dem Upload solltest du folgende Ausgabe sehen:

```
=================================
BThome Temperatursensor Example
ESP32-S3 DevKitC-1
=================================

Initializing BLE...
BLE erfolgreich initialisiert!
Device Name: ESP32-TempSensor
Advertising Interval: 5000 ms
Initiale Temperatur: 42.78°C

System bereit! Sende BThome Temperature Advertisements...

BLE Advertisement aktualisiert - Temperatur: 42.78°C | BThome Payload: d2 fc 40 02 b6 10
BLE Advertisement aktualisiert - Temperatur: 42.89°C | BThome Payload: d2 fc 40 02 c1 10
...
```

### 2. BLE Scanner verwenden

**Android/iOS: nRF Connect App**

1. Öffne nRF Connect
2. Scanne nach BLE-Geräten
3. Suche nach `ESP32-TempSensor`
4. Überprüfe die Manufacturer Data:
   - Company ID: `0xFCD2` (BTHome)
   - Device Info: `0x40` (BThome v2)
   - Object ID: `0x02` (Temperature)
   - Wert: z.B. `0xB6 0x10` = 4278 = 42.78°C

### 3. Home Assistant Integration

**Automatische Erkennung:**

1. Stelle sicher, dass die BThome Integration installiert ist
2. Das Gerät sollte automatisch als neuer Sensor erscheinen
3. Überprüfe unter **Einstellungen → Geräte & Dienste → BTHome**
4. Der Sensor sollte als `ESP32-TempSensor` angezeigt werden

**Manuelle Konfiguration (falls nötig):**

```yaml
# configuration.yaml
sensor:
  - platform: bthome
    mac: "XX:XX:XX:XX:XX:XX"  # MAC-Adresse des ESP32
```

### 4. RGB LED beobachten

- Die LED sollte grün leuchten nach dem Start
- Alle 5 Sekunden ein kurzes blaues Aufblitzen bei Messung
- Langsamer Regenbogen-Effekt im Hintergrund

## BThome Spezifikation

### Object ID: Temperature (0x02)

- **Datentyp**: Signed int16
- **Faktor**: 0.01°C
- **Beispiel**: 2506 (0x09CA) = 25.06°C
- **Byte-Reihenfolge**: Little Endian

### Berechnung

```cpp
// Celsius zu BThome
int16_t value = (int16_t)(temperatureC * 100);

// BThome zu Celsius
float temperatureC = value / 100.0;
```

## Serielle Ausgabe

Beispiel einer vollständigen Session:

```
=================================
BThome Temperatursensor Example
ESP32-S3 DevKitC-1
=================================

Initializing BLE...
BLE erfolgreich initialisiert!
Device Name: ESP32-TempSensor
Advertising Interval: 5000 ms
Initiale Temperatur: 42.78°C
BLE Advertisement aktualisiert - Temperatur: 42.78°C | BThome Payload: d2 fc 40 02 b6 10

System bereit! Sende BThome Temperature Advertisements...

BLE Advertisement aktualisiert - Temperatur: 42.89°C | BThome Payload: d2 fc 40 02 c1 10
BLE Advertisement aktualisiert - Temperatur: 43.00°C | BThome Payload: d2 fc 40 02 cc 10
BLE Advertisement aktualisiert - Temperatur: 42.67°C | BThome Payload: d2 fc 40 02 ab 10
```

## Nächste Schritte

Mögliche Erweiterungen für dieses Beispiel:

1. **Externe Temperatursensoren**: 
   - BME280/BME680 für präzise Umgebungstemperatur
   - DS18B20 für wasserdichte Messungen
   - DHT22 für Temperatur + Luftfeuchtigkeit

2. **Mehrere Sensoren kombinieren**:
   - Temperatur + Luftfeuchtigkeit (Object ID 0x03)
   - Temperatur + Luftdruck (Object ID 0x04)
   - Temperatur + Batteriespannung (Object ID 0x01)

3. **Batterieeffizienz**:
   - Longer Advertising-Intervalle (z.B. 60 Sekunden)
   - Deep Sleep zwischen Messungen
   - Dynamisches Intervall basierend auf Änderungen

4. **Verschlüsselung**:
   - BThome v2 Encryption implementieren
   - AES-CCM für sichere Datenübertragung

5. **Home Assistant Automatisierungen**:
   - Benachrichtigungen bei hohen Temperaturen
   - Historische Daten visualisieren
   - Multi-Room Temperaturüberwachung

## Ressourcen

- [BThome Spezifikation](https://bthome.io/format/)
- [BThome Object IDs](https://bthome.io/format/#object-ids)
- [ESP32-S3 Temperature Sensor](https://docs.espressif.com/projects/esp-idf/en/latest/esp32s3/api-reference/peripherals/temp_sensor.html)
- [Home Assistant BThome Integration](https://www.home-assistant.io/integrations/bthome/)

## Bekannte Einschränkungen

- Der interne Temperatursensor misst die **Chip-Temperatur**, nicht die Umgebungstemperatur
- Die Temperatur liegt typischerweise 5-10°C über der Raumtemperatur
- Für genaue Umgebungstemperatur-Messungen einen externen Sensor verwenden
- Der Sensor ist nicht kalibriert (±2-3°C Abweichung möglich)
