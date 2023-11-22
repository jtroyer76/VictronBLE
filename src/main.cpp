#include <Arduino.h>
#include <M5Core2.h>
#include <BLEDevice.h>
#include <BLEScan.h>
#include <BLEAdvertisedDevice.h>

#include "VictronAdvertisedPacketReceiver.h"

int scanTime = 1; // BLE scan time (seconds)

BLEScan* ble_scan;
VictronPacketDecoder* packet_decoder = new VictronPacketDecoder();
VictronAdvertisedPacketReceiver* packet_receiver = new VictronAdvertisedPacketReceiver(packet_decoder);

void setup() {
  Serial.begin(115200);
  delay(1000);
  Serial.println();
  Serial.println("Reset.");
  Serial.println();
 
  // Solar Charge Controller
  packet_decoder->AddKey({ 0xfb, 0x82, 0x3f, 0xe5, 0x4f, 0x08 },
  {
    0xAE, 0x84, 0xf9, 0x1f, 0x8d, 0x5d, 0x84, 0x68,
    0xaf, 0x72, 0x3b, 0x9a, 0x9e, 0xd0, 0xa1, 0x7c,
  });

  // Shunt
  packet_decoder->AddKey({ 0xfb, 0x63, 0x3c, 0xe3, 0x4f, 0x26},
  {
    0x53, 0xf5, 0x27, 0xcc, 0x8d, 0xbb, 0x22, 0x23, 
    0xe3, 0xb7, 0x91, 0xec, 0x42, 0xe4, 0xdb, 0x3c,   
  });

  // Initialize BLE Scanning 
  BLEDevice::init("");
  ble_scan = BLEDevice::getScan(); //create new scan
  ble_scan->setAdvertisedDeviceCallbacks(packet_receiver);
  ble_scan->setActiveScan(true); //active scan uses more power, but get results faster
  ble_scan->setInterval(100);
  ble_scan->setWindow(99); // less or equal setInterval value

  M5.begin();
  M5.Lcd.fillScreen(WHITE);  // Set the screen background.  设置屏幕底色为白色
  delay(500);                // Delay 500ms.  延迟500ms
  M5.Lcd.fillScreen(RED);
  delay(500);
  M5.Lcd.fillScreen(GREEN);
  delay(500);
  M5.Lcd.fillScreen(BLUE);
  delay(500);
  M5.Lcd.fillScreen(BLACK);
  delay(500);
  M5.Lcd.setTextColor(WHITE);
  M5.Lcd.setTextSize(1);

  Serial.println("setup() complete.");
}

void loop() {
  BLEScanResults foundDevices = ble_scan->start(scanTime, false);  
  ble_scan->clearResults(); // delete results fromBLEScan buffer to release memory
}

