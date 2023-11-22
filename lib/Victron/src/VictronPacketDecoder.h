#pragma once

#include <map>
#include <array>
#include "VictronManufacturerRecord.h"
#include "VictronRecord.h"

#define BD_ADDR_LEN 6
#define KEY_LEN 16

// Bluetooth device address
typedef std::array<uint8_t, BD_ADDR_LEN> bd_addr_t;

/// Bluetooth device address
//typedef uint8_t bd_addr_t[BD_ADDR_LEN];

// Victron manufacturer data key aes-ctr 128
typedef std::array<uint8_t, KEY_LEN> adv_key_t;

class VictronPacketDecoder {
 public:
  VictronPacketDecoder() : _deviceKeys() {}
  VictronRecord* Decode(VictronManufacturerRecord* record, bd_addr_t mac);
  void AddKey(bd_addr_t mac, adv_key_t key);

 private:
  uint8_t* DecryptPacket(VictronManufacturerRecord* record, bd_addr_t mac);
  std::map<bd_addr_t, adv_key_t> _deviceKeys;
};