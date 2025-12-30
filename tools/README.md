# BThome Logger Tools

Dieses Verzeichnis enthält Tools zum Testen und Debuggen von BThome-Geräten.

## 🐍 Python BThome Logger

Ein zuverlässiges Python-Tool zum Scannen und Anzeigen von BThome v2 Advertisements.

### Installation

**Mit uv (empfohlen):**

```bash
# uv installieren (falls noch nicht vorhanden)
curl -LsSf https://astral.sh/uv/install.sh | sh

# Ins tools-Verzeichnis wechseln
cd tools

# Abhängigkeiten installieren und Tool ausführen
uv run bthome-logger.py
```

### Verwendung

```bash
# Mit uv (empfohlen - installiert automatisch Dependencies)
uv run bthome-logger.py
```

### Features

- ✅ Scannt nach BLE-Geräten mit "MAKE" im Namen
- ✅ Zeigt BThome v2 Company ID (0xFCD2) erkannt
- ✅ Dekodiert alle gängigen BThome Object IDs
- ✅ Farbige Terminal-Ausgabe für bessere Lesbarkeit
- ✅ Zeigt RSSI-Werte mit Farb-Codierung
- ✅ Echtzeit-Updates bei neuen Advertisements
- ✅ Unterstützt verschlüsselte und unverschlüsselte Pakete

### Ausgabe-Beispiel

```text
======================================================================
🔵 BThome Logger - Python Edition
Scannt nach BLE-Geräten mit BThome v2 Protocol
======================================================================

Filter: Geräte mit 'MAKE' im Namen
Drücke Ctrl+C zum Beenden

✓ Scanner gestartet...

----------------------------------------------------------------------
[14:32:45.123] 📱 MAKE-ESP32-S3-TS (XX:XX:XX:XX:XX:XX)
  RSSI: -65 dBm
  Raw: d2 fc 40 02 b6 10
  BThome: v2 (unverschlüsselt)
  Werte:
    • Temperatur: 42.78 °C
```

### Troubleshooting

**Problem:** `bleak` kann nicht installiert werden

**Lösung:** Stelle sicher, dass du Python 3.7+ verwendest:

**Problem:** Keine Bluetooth-Berechtigung

**Lösung (Linux):**

```bash
# Füge Benutzer zur bluetooth Gruppe hinzu
sudo usermod -a -G bluetooth $USER
```

Melde dich danach ab und wieder an oder führe `newgrp bluetooth` aus (wirkt nur für das aktuelle Terminal).
