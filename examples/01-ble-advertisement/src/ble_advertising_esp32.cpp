#ifdef PLATFORM_ESP32

#include "ble_advertising.h"
#include <BLEDevice.h>
#include <BLEUtils.h>
#include <BLEServer.h>
#include <BLEAdvertising.h>

// BLE advertising interval in ms
#define BLE_ADVERTISING_INTERVAL_MS 1000

// Global BLE objects
static BLEAdvertising *pAdvertising = nullptr;

void setupBLE()
{
  Serial.println("Starting BLE Advertisement Example for ESP32-C3");
  
  // Initialize BLE
  BLEDevice::init("ESP32-C3-BLE");
  
  // Create BLE Server (needed for advertising)
  BLEServer *pServer = BLEDevice::createServer();
  
  // Get advertising object
  pAdvertising = BLEDevice::getAdvertising();
  
  // Set advertising data
  BLEAdvertisementData advertisementData;
  advertisementData.setFlags(0x06); // BR_EDR_NOT_SUPPORTED | LE General Discoverable Mode
  advertisementData.setName("ESP32-C3-BLE");
  
  // Set manufacturer data using shared constant
  advertisementData.setManufacturerData(
    std::string(reinterpret_cast<const char*>(MANUFACTURER_DATA), sizeof(MANUFACTURER_DATA))
  );
  
  pAdvertising->setAdvertisementData(advertisementData);
  
  // Set scan response data (optional)
  BLEAdvertisementData scanResponseData;
  scanResponseData.setCompleteServices(BLEUUID((uint16_t)0x180A)); // Device Information Service
  pAdvertising->setScanResponseData(scanResponseData);
  
  // Set advertising interval
  pAdvertising->setMinInterval(BLE_ADVERTISING_INTERVAL_MS);
  pAdvertising->setMaxInterval(BLE_ADVERTISING_INTERVAL_MS);
  
  // Start advertising
  pAdvertising->start();
}

void printBLEStatus()
{
  Serial.println("BLE Advertising started!");
  Serial.println("Device Name: ESP32-C3-BLE");
  Serial.println("Manufacturer Data: FF FF 01 02 03 04");
}

#endif // PLATFORM_ESP32
