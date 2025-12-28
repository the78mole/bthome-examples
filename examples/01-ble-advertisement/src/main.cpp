#include <Arduino.h>

// Platform-specific includes
#ifdef PLATFORM_ESP32
  #include <BLEDevice.h>
  #include <BLEUtils.h>
  #include <BLEServer.h>
  #include <BLEAdvertising.h>
  
  // BLE advertising interval in ms
  #define BLE_ADVERTISING_INTERVAL 1000
  
  BLEAdvertising *pAdvertising;
#endif

#ifdef PLATFORM_NRF52
  #include <bluefruit.h>
  
  // BLE advertising interval in units of 0.625ms
  #define BLE_ADVERTISING_INTERVAL 1600  // 1000ms (1600 * 0.625ms)
  
  BLEDis bledis;    // Device Information Service
#endif

void setup() {
  Serial.begin(115200);
  
#ifdef PLATFORM_NRF52
  // Wait for serial port to connect (useful for native USB)
  while (!Serial) delay(10);
#endif
  
  delay(1000);
  
#ifdef PLATFORM_ESP32
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
#endif

#ifdef PLATFORM_NRF52
  Serial.println("Starting BLE Advertisement Example for nRF52840");
  
  // Initialize Bluefruit with maximum connections as Peripheral = 0, Central = 0
  Bluefruit.begin(0, 0);
  Bluefruit.setName("nRF52840-BLE");
  
  // Set max TX power
  Bluefruit.setTxPower(4);  // Valid values: -40, -30, -20, -16, -12, -8, -4, 0, 4
  
  // Configure Device Information Service (optional)
  bledis.setManufacturer("Adafruit Industries");
  bledis.setModel("Feather nRF52840");
  bledis.begin();
  
  // Set up advertising packet
  Bluefruit.Advertising.addFlags(BLE_GAP_ADV_FLAGS_LE_ONLY_GENERAL_DISC_MODE);
  Bluefruit.Advertising.addName();
  
  // Add manufacturer specific data
  // Format: Company ID (2 bytes, little endian) + Custom data
  uint8_t manufacturerData[6] = {0xFF, 0xFF, 0x01, 0x02, 0x03, 0x04};
  Bluefruit.Advertising.addData(BLE_GAP_AD_TYPE_MANUFACTURER_SPECIFIC_DATA, 
                                manufacturerData, 
                                sizeof(manufacturerData));
  
  // Set advertising interval
  Bluefruit.Advertising.setInterval(BLE_ADVERTISING_INTERVAL, BLE_ADVERTISING_INTERVAL);
  
  // Set advertising timeout (0 = continuous)
  Bluefruit.Advertising.setStopCallback(NULL);
  Bluefruit.Advertising.restartOnDisconnect(true);
  Bluefruit.Advertising.setFastTimeout(0);  // Disable fast advertising timeout
  
  // Start advertising
  Bluefruit.Advertising.start(0);  // 0 = Don't stop advertising
  
  Serial.println("BLE Advertising started!");
  Serial.println("Device Name: nRF52840-BLE");
  Serial.println("Manufacturer Data: FF FF 01 02 03 04");
#endif
}

void loop() {
  // Keep advertising running
  delay(10000);
  Serial.println("Still advertising...");
}
