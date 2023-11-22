#pragma once

#include <stdint.h>

enum RecordType : uint8_t {
  SolorCharger = 1,
  BatteryMonitor = 2,
  Inverter = 3,
  DcToDc = 4,
  SmartLithium = 5,
  InverterRS = 6,
  GXDevice = 7,
  ACCharger=8,
  SmartBatteryProtect = 9,
  LynxSmartBMS = 10,
  MultiRS = 11,
  VEBus = 12,
  DCEnergyMeter = 13
};

// Must use the "packed" attribute to make sure the compiler doesn't add any padding to deal with
// word alignment.
struct __attribute__((packed)) VictronManufacturerRecord {
  uint16_t vendorID;                 // vendor ID
  uint8_t beaconType;                // Should be 0x10 (Product Advertisement) for the packets we want
  uint8_t unknownData1[3];           // Unknown data
  RecordType recordType;             // Should be 0x01 (Solar Charger) for the packets we want
  uint16_t nonceDataCounter;         // Nonce
  uint8_t encryptKeyMatch;           // Should match pre-shared encryption key byte 0
  uint8_t victronEncryptedData[21];  // (31 bytes max per BLE spec - size of previous elements)
  uint8_t nullPad;                   // extra byte because toCharArray() adds a \0 byte.
};
