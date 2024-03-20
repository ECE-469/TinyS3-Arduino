#include <BLEDevice.h>
#include <BLEUtils.h>
#include <BLEServer.h>
#include <sstream>

// See the following for generating UUIDs:
// https://www.uuidgenerator.net/
#define SERVICE_UUID "f3641400-00b0-4240-ba50-05ca45bf8abc"
#define CHARACTERISTIC_UUID "f3641401-00b0-4240-ba50-05ca45bf8abc"
#define CHARACTERISTIC_CO_UUID "f3641403-00b0-4240-ba50-05ca45bf8abc"
#define DEVICE_NAME "TinyS3 Arduino"

class MyCallbackHandler : public BLECharacteristicCallbacks
{
  void onRead(BLECharacteristic *pCharacteristic)
  {
    struct timeval tv;
    gettimeofday(&tv, nullptr);
    std::ostringstream os;
    os << "Time: " << tv.tv_sec;
    pCharacteristic->setValue(os.str());
  }
};

MyCallbackHandler *myCallbackHandler = new MyCallbackHandler();
BLECharacteristic *pCharacteristic;

void ble_init()
{

  BLEDevice::init(DEVICE_NAME);
  BLEServer *pServer = BLEDevice::createServer();
  BLEService *pService = pServer->createService(SERVICE_UUID);
  pCharacteristic = pService->createCharacteristic(
      CHARACTERISTIC_CO_UUID,
      BLECharacteristic::PROPERTY_READ | BLECharacteristic::PROPERTY_NOTIFY);
  pCharacteristic->setValue("Elapsed Time");
  pCharacteristic->setCallbacks(myCallbackHandler);
  pService->start();
  BLEAdvertising *pAdvertising = BLEDevice::getAdvertising();
  pAdvertising->addServiceUUID(SERVICE_UUID);
  pAdvertising->setScanResponse(true);
  pAdvertising->setMinPreferred(0x06);
  pAdvertising->setMinPreferred(0x12);
  BLEDevice::startAdvertising();
  Serial.println("Characteristic defined! Now you can read it in your phone!");
}

