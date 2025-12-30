#ifndef BLE_ADVERTISING_H
#define BLE_ADVERTISING_H

#include <Arduino.h>

// Shared manufacturer data - Company ID 0xFFFF + Custom data
extern const uint8_t MANUFACTURER_DATA[6];

// Common BLE advertising interface
void setupBLE();
void printBLEStatus();

#endif // BLE_ADVERTISING_H
