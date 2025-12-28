#include <Arduino.h>
#include <BLEDevice.h>
#include <BLEUtils.h>
#include <BLEServer.h>
#include <BLEAdvertising.h>

// BLE advertising interval in ms
#define BLE_ADVERTISING_INTERVAL 1000

BLEAdvertising *pAdvertising;

void setup() {
  Serial.begin(115200);
  delay(1000);
  
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
  
  // Set manufacturer data (example: Company ID 0xFFFF + custom data)
  uint8_t manufacturerData[6] = {0xFF, 0xFF, 0x01, 0x02, 0x03, 0x04};
  advertisementData.setManufacturerData(std::string((char*)manufacturerData, 6));
  
  pAdvertising->setAdvertisementData(advertisementData);
  
  // Set scan response data (optional)
  BLEAdvertisementData scanResponseData;
  scanResponseData.setCompleteServices(BLEUUID((uint16_t)0x180A)); // Device Information Service
  pAdvertising->setScanResponseData(scanResponseData);
  
  // Set advertising interval
  pAdvertising->setMinInterval(BLE_ADVERTISING_INTERVAL);
  pAdvertising->setMaxInterval(BLE_ADVERTISING_INTERVAL);
  
  // Start advertising
  pAdvertising->start();
  
  Serial.println("BLE Advertising started!");
  Serial.println("Device Name: ESP32-C3-BLE");
  Serial.println("Manufacturer Data: FF FF 01 02 03 04");
}

void loop() {
  // Keep advertising running
  delay(10000);
  Serial.println("Still advertising...");
}
