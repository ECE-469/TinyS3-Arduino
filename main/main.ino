#include <BLEDevice.h>
#include <BLEUtils.h>
#include <BLEServer.h>
#include <sstream>

// See the following for generating UUIDs:
// https://www.uuidgenerator.net/

#define SERVICE_UUID        "55e55347-53e5-429a-9d3b-c89a6df5c88e"
#define CHARACTERISTIC_UUID "9e8f3ee8-efd7-4eb3-878a-5d287ad61033"

class MyCallbackHandler: public BLECharacteristicCallbacks {
  void onRead(BLECharacteristic* pCharacteristic) {
  struct timeval tv;
  gettimeofday(&tv, nullptr);
  std::ostringstream os;
  os << "Time: " << tv.tv_sec;
  pCharacteristic->setValue(os.str());
  }
};

MyCallbackHandler *myCallbackHandler = new MyCallbackHandler();
BLECharacteristic *pCharacteristic;

void setup() {
  Serial.begin(115200);
  Serial.println("Starting BLE work!");

  BLEDevice::init("TinyS3 Arduino");
  BLEServer *pServer = BLEDevice::createServer();
  BLEService *pService = pServer->createService(SERVICE_UUID);
  pCharacteristic = pService->createCharacteristic(
                                         CHARACTERISTIC_UUID,
                                         BLECharacteristic::PROPERTY_READ
                                       );
  pCharacteristic->setValue("Elapsed Time");
  pCharacteristic->setCallbacks(myCallbackHandler);
  pService->start();
  // BLEAdvertising *pAdvertising = pServer->getAdvertising();  // this still is working for backward compatibility
  BLEAdvertising *pAdvertising = BLEDevice::getAdvertising();
  pAdvertising->addServiceUUID(SERVICE_UUID);
  pAdvertising->setScanResponse(true);
  pAdvertising->setMinPreferred(0x06);  // functions that help with iPhone connections issue
  pAdvertising->setMinPreferred(0x12);
  BLEDevice::startAdvertising();
  Serial.println("Characteristic defined! Now you can read it in your phone!");
}

void loop() {
  // put your main code here, to run repeatedly:
  pCharacteristic->notify();
  delay(1000);
}