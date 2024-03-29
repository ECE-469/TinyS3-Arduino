#include "BLE.h"

std::map<SENSOR_NAME, UUID> sensor_uuid_map = {
    {"CHARACTERISTIC", CHARACTERISTIC_UUID},
    {"CO", CHARACTERISTIC_CO_UUID},
    {"CO2", CHARACTERISTIC_CO2_UUID},
    {"O3", CHARACTERISTIC_O3_UUID}};

void CustomServerCallbacks::onConnect(BLEServer *pServer)
{
  Serial.println("Client connected");
}

void CustomServerCallbacks::onDisconnect(BLEServer *pServer)
{
  Serial.println("Client disconnected");
  delay(100); // give the client time to get the last notification
  BLEDevice::startAdvertising();
}

BLE::BLE()
{
  BLEDevice::init(DEVICE_NAME);
  BLEServer *pServer = BLEDevice::createServer();
  CustomServerCallbacks *myServerCallbacks = new CustomServerCallbacks();
  pServer->setCallbacks(myServerCallbacks);
  BLEService *pService = pServer->createService(SERVICE_UUID);
  _init_characteristics(pService);
  pService->start();
  _init_advertising();
}

BLECharacteristic *BLE::get_characteristic(std::string name)
{
  UUID uuid = sensor_uuid_map[name];
  return characteristic_map[uuid];
}

void BLE::_init_characteristics(BLEService *pService)
{
  std::vector<std::string> sensor_list = {"CO", "CO2"};
  for (auto sensor : sensor_list)
  {
    UUID sensor_uuid = sensor_uuid_map[sensor];
    BLECharacteristic *characteristic = create_characteristic(sensor_uuid, pService);
    characteristic_map[sensor_uuid] = characteristic;
  }
}

void BLE::_init_advertising()
{
  BLEAdvertising *pAdvertising = BLEDevice::getAdvertising();
  pAdvertising->addServiceUUID(SERVICE_UUID);
  pAdvertising->setScanResponse(true);
  pAdvertising->setMinPreferred(0x06);
  pAdvertising->setMinPreferred(0x12);
  BLEDevice::startAdvertising();
}

BLECharacteristic *BLE::create_characteristic(const UUID uuid, BLEService *pService)
{
  BLECharacteristic *characteristic = pService->createCharacteristic(uuid, BLECharacteristic::PROPERTY_READ | BLECharacteristic::PROPERTY_NOTIFY);
  BLEUUID cccdUUID(BLEUUID((uint16_t)0x2902)); // Standard UUID for CCCD
  BLEDescriptor *pDescriptor = new BLEDescriptor(cccdUUID);
  pDescriptor->setAccessPermissions(ESP_GATT_PERM_READ | ESP_GATT_PERM_WRITE);
  characteristic->addDescriptor(pDescriptor);
  return characteristic;
}