# Web Bluetooth API

## 什么是Web Bluetooth API

Web Bluetooth API是一组由 W3C 制定的 JavaScript API，它允许 Web 应用程序通过蓝牙低功耗（BLE）协议直接与附近的蓝牙设备进行通信

这意味着开发者可以在网页中实现蓝牙设备的搜索、连接和数据传输，而无需依赖原生应用程序或额外的插件

​​设备请求与筛选​​：通过调用 navigator.bluetooth.requestDevice()方法，浏览器会弹出设备选择器，用户可以从搜索到的设备中选择要连接的设备。开发者可以定义过滤器（filters）来指定要寻找的设备类型或服务

​​建立连接​​：用户选择设备后，使用 device.gatt.connect()方法建立与设备 GATT 服务器的连接

​​发现服务与特征值​​：连接成功后，通过 server.getPrimaryService(serviceUUID)获取所需服务，然后通过 service.getCharacteristic(characteristicUUID)获取特定的特征值（Characteristic）。特征值是数据读写操作的实际接口

​​数据交换​​：最后，使用 characteristic.readValue()读取数据，或使用 characteristic.writeValue()写入数据

还可以通过 startNotifications()方法启用通知，监听设备发来的数据


## 我的想法

本来想做的蓝牙的显示的，但是后发现HC05用的是SPP不是BLE，所以，就放弃了。不过还是学到了，如何用Web Bluetooth API和BT24通信的，因为今天没空，就只留下了代码部分：

```vue
<script setup lang="ts">
const BT24_SERVICE_UUID = 0xffe0; // 注意：Web Bluetooth API通常使用短UUID格式
const BT24_TX_CHARACTERISTIC_UUID = 0xffe1; // 假设用于接收模块数据（通知）
const BT24_RX_CHARACTERISTIC_UUID = 0xffe2; // 假设用于向模块发送数据（写）

let bt24Device = null;
let bt24Server = null;
let bt24Service = null;
let txCharacteristic = null; // 用于接收数据（通知）
let rxCharacteristic = null; // 用于发送数据（写）

async function getDevice(){
    bt24Device = await navigator.bluetooth.requestDevice({
        acceptAllDevices : true,
        optionalServices: [BT24_SERVICE_UUID]
    });

    bt24Server = await bt24Device.gatt.connect();
    // console.log(bt24Server)

    bt24Service = await bt24Server.getPrimaryService(BT24_SERVICE_UUID);

    rxCharacteristic = await bt24Service.getCharacteristic(BT24_RX_CHARACTERISTIC_UUID);
    // console.log(rxCharacteristic)
    txCharacteristic = await bt24Service.getCharacteristic(BT24_TX_CHARACTERISTIC_UUID);
}

async function Send(){
    const encoder = new TextEncoder()
    const dataBuffer = encoder.encode("hello world")
    await rxCharacteristic.writeValue(dataBuffer)
    // console.log(rxCharacteristic.writeValueWithoutResponse)
}

</script>

<template>
    <button @click = getDevice>Connect</button>
    <br></br>
    <button @click = Send>Send</button>
</template>
```
