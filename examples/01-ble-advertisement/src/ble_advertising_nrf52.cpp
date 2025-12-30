#ifdef PLATFORM_NRF52

#include "ble_advertising.h"
#include <Adafruit_TinyUSB.h>  // Required for Serial to work with Seeed nRF52 Boards
#include <bluefruit.h>

// BLE advertising interval in units of 0.625ms (1000ms = 1600 * 0.625ms)
#define BLE_ADVERTISING_INTERVAL_UNITS 1600

// Global BLE objects
static BLEDis bledis;    // Device Information Service

void setupBLE()
{
  Serial.println("Starting BLE Advertisement Example for nRF52840");
  Serial.println("Step 1: Initializing Bluefruit...");
  
  // Initialize Bluefruit with maximum connections as Peripheral = 0, Central = 0
  Bluefruit.begin(0, 0);
  Serial.println("Step 2: Bluefruit initialized");
  
  Bluefruit.setName("nRF52840-BLE");
  Serial.println("Step 3: Name set");
  
  // Set max TX power
  Bluefruit.setTxPower(4);  // Valid values: -40, -30, -20, -16, -12, -8, -4, 0, 4
  Serial.println("Step 4: TX Power set");
  
  // Configure Device Information Service (optional)
  bledis.setManufacturer("Adafruit Industries");
  bledis.setModel("Feather nRF52840");
  bledis.begin();
  Serial.println("Step 5: Device Info Service started");
  Serial.println("Step 6: Configuring advertising...");
  Bluefruit.Advertising.addFlags(BLE_GAP_ADV_FLAGS_LE_ONLY_GENERAL_DISC_MODE);
  Bluefruit.Advertising.addName();
  
  // Add manufacturer specific data using shared constant
  Bluefruit.Advertising.addData(
    BLE_GAP_AD_TYPE_MANUFACTURER_SPECIFIC_DATA, 
    MANUFACTURER_DATA, 
    sizeof(MANUFACTURER_DATA)
  );
  Serial.println("Step 7: Manufacturer data added");
  
  // Set advertising interval
  Bluefruit.Advertising.setInterval(BLE_ADVERTISING_INTERVAL_UNITS, BLE_ADVERTISING_INTERVAL_UNITS);
  
  // Set advertising timeout (0 = continuous)
  Bluefruit.Advertising.setStopCallback(NULL);
  Bluefruit.Advertising.restartOnDisconnect(true);
  Bluefruit.Advertising.setFastTimeout(0);  // Disable fast advertising timeout
  Serial.println("Step 8: Advertising parameters set");
  
  // Start advertising
  Bluefruit.Advertising.start(0);  // 0 = Don't stop advertising
  Serial.println("Step 9: Advertising started!");
  // Start advertising
  Bluefruit.Advertising.start(0);  // 0 = Don't stop advertising
}

void printBLEStatus()
{
  Serial.println("BLE Advertising started!");
  Serial.println("Device Name: nRF52840-BLE");
  Serial.println("Manufacturer Data: FF FF 01 02 03 04");
}

#endif // PLATFORM_NRF52
