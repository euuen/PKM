# 低功耗蓝牙 BLE

BLE，全名：Bluetooth Low Energe

```cpp
#include <BLEDevice.h>
#include <BLEUtils.h>
#include <BLEScan.h>
#include <BLEAdvertisedDevice.h>
#include <BLEClient.h>
#include <BLE2902.h>

// BT24配置（与AT指令一致）
#define TARGET_NAME "MyBT24"
#define SERVICE_UUID        "FFE0"
#define CHARACTERISTIC_UUID "FFE1"

BLEClient* pClient;
BLERemoteCharacteristic* pRemoteCharacteristic;
bool deviceFound = false;
BLEAdvertisedDevice* targetDevice;
bool isConnected = false;

// 扫描回调
class MyAdvertisedDeviceCallbacks : public BLEAdvertisedDeviceCallbacks {
  void onResult(BLEAdvertisedDevice advertisedDevice) {
    if (advertisedDevice.getName() == TARGET_NAME) {
      Serial.printf("Found target: %s\n", advertisedDevice.toString().c_str());
      targetDevice = new BLEAdvertisedDevice(advertisedDevice);
      deviceFound = true;
    }
  }
};

// 连接BT24
bool connectToBT24() {
  if (!pClient->connect(targetDevice->getAddress())) {
    Serial.println("Connection failed");
    return false;
  }
  Serial.println("Connected to BT24");
  
  // 获取服务
  BLERemoteService* pRemoteService = pClient->getService(SERVICE_UUID);
  if (pRemoteService == nullptr) {
    Serial.println("Service not found");
    pClient->disconnect();
    return false;
  }

  // 获取特征值
  pRemoteCharacteristic = pRemoteService->getCharacteristic(CHARACTERISTIC_UUID);
  if (pRemoteCharacteristic == nullptr) {
    Serial.println("Characteristic not found");
    pClient->disconnect();
    return false;
  }

  // 启用通知
  if (pRemoteCharacteristic->canNotify()) {
    pRemoteCharacteristic->registerForNotify(notifyCallback);
  }
  
  return true;
}

// 通知回调
static void notifyCallback(BLERemoteCharacteristic* pChar, uint8_t* data, size_t length, bool isNotify) {
  Serial.print("Received: ");
  for (int i = 0; i < length; i++) {
    Serial.print((char)data[i]);
  }
  Serial.println();
}

// 重新连接
void reconnect() {
  if (deviceFound && !isConnected) {
    Serial.println("Attempting reconnect...");
    if (connectToBT24()) {
      isConnected = true;
      Serial.println("Reconnected!");
    }
  }
}

void setup() {
  Serial.begin(115200);
  Serial.println("ESP32 BLE Client Starting...");
  
  BLEDevice::init("ESP32_Master");
  
  // 开始扫描
  BLEScan* pScan = BLEDevice::getScan();
  pScan->setAdvertisedDeviceCallbacks(new MyAdvertisedDeviceCallbacks());
  pScan->setActiveScan(true);
  pScan->start(5); // 扫描5秒

  if (!deviceFound) {
    Serial.println("BT24 not found!");
    return;
  }

  pClient = BLEDevice::createClient();
  if (connectToBT24()) {
    isConnected = true;
    Serial.println("Ready for communication");
  }
}

void loop() {
  if (isConnected && pClient->isConnected()) {
    // 1. 发送命令到BT24
    static unsigned long lastCommand = 0;
    if (millis() - lastCommand > 5000) {
      // 切换LED状态
      static bool ledState = false;
      ledState = !ledState;
      
      if (ledState) {
        pRemoteCharacteristic->writeValue("LED_ON");
        Serial.println("Sent: LED_ON");
      } else {
        pRemoteCharacteristic->writeValue("LED_OFF");
        Serial.println("Sent: LED_OFF");
      }
      
      lastCommand = millis();
    }
    
    // 2. 主动读取数据（可选）
    if (millis() - lastCommand > 2000 && millis() - lastCommand < 4000) {
      std::string value = pRemoteCharacteristic->readValue();
      Serial.print("Read value: ");
      Serial.println(value.c_str());
    }
  } else {
    // 断线重连
    reconnect();
    delay(2000);
  }
}
```

## 省流

低速，低功耗
