#include <BLEDevice.h>
#include <BLEUtils.h>
#include <BLEServer.h>
#include <sstream>

// See the following for generating UUIDs:
// https://www.uuidgenerator.net/
#define SERVICE_UUID "f3641400-00b0-4240-ba50-05ca45bf8abc"
#define CHARACTERISTIC_UUID "f3641401-00b0-4240-ba50-05ca45bf8abc"
#define CHARACTERISTIC_CO_UUID "f3641403-00b0-4240-ba50-05ca45bf8abc"
#define CHARACTERISTIC_CO2_UUID "f3641404-00b0-4240-ba50-05ca45bf8abc"
#define DEVICE_NAME "TinyS3 Arduino"

// TODO: Fix this terrible implementation
// ideas: use a map where the sensor name is the key and the characteristic is the value

class CustomServerCallbacks : public BLEServerCallbacks
{
  void onConnect(BLEServer *pServer)
  {
    Serial.println("Client connected");
  };

  void onDisconnect(BLEServer *pServer)
  {
    Serial.println("Client disconnected");
    delay(100); // give the client time to get the last notification
    BLEDevice::startAdvertising();
  };
};

class BLE
{
public:
  BLE()
  {
    CustomServerCallbacks *myServerCallbacks = new CustomServerCallbacks();
    BLEDevice::init(DEVICE_NAME);
    BLEServer *pServer = BLEDevice::createServer();
    pServer->setCallbacks(myServerCallbacks);
    BLEService *pService = pServer->createService(SERVICE_UUID);
    _init_characteristics(pService);
    pService->start();
    _init_advertising();
  }

  BLECharacteristic *get_CO_characteristic()
  {
    return coCharacteristic;
  }

  BLECharacteristic *get_CO2_characteristic()
  {
    return co2Characteristic;
  }

private:
  BLECharacteristic *coCharacteristic;
  BLECharacteristic *co2Characteristic;

  void _init_characteristics(BLEService *pService)
  {
    coCharacteristic = create_characteristic(CHARACTERISTIC_CO_UUID, pService);
    co2Characteristic = create_characteristic(CHARACTERISTIC_CO2_UUID, pService);
  }

  void _init_advertising()
  {
    BLEAdvertising *pAdvertising = BLEDevice::getAdvertising();
    pAdvertising->addServiceUUID(SERVICE_UUID);
    pAdvertising->setScanResponse(true);
    pAdvertising->setMinPreferred(0x06);
    pAdvertising->setMinPreferred(0x12);
    BLEDevice::startAdvertising();
  }

  BLECharacteristic *create_characteristic(const char *uuid, BLEService *pService)
  {
    BLECharacteristic *characteristic = pService->createCharacteristic(uuid, BLECharacteristic::PROPERTY_READ | BLECharacteristic::PROPERTY_NOTIFY);
    BLEUUID cccdUUID(BLEUUID((uint16_t)0x2902)); // Standard UUID for CCCD
    BLEDescriptor *pDescriptor = new BLEDescriptor(cccdUUID);
    pDescriptor->setAccessPermissions(ESP_GATT_PERM_READ | ESP_GATT_PERM_WRITE);
    characteristic->addDescriptor(pDescriptor);
    return characteristic;
  }
};