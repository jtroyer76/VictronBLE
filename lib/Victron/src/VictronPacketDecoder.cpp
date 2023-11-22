#include "VictronPacketDecoder.h"
#include "BatteryMonitorRecord.h"
#include "SolarChargerRecord.h"

#include <aes.hpp>

VictronRecord* VictronPacketDecoder::Decode(VictronManufacturerRecord* record, bd_addr_t mac) {
  uint8_t* decrypted = DecryptPacket(record, mac);
  if (decrypted == nullptr)
    return nullptr;

  switch (record->recordType) {
    case RecordType::SolorCharger:
      return new SolarChargerRecord(reinterpret_cast<SolarData*>(decrypted));

    case RecordType::BatteryMonitor:
      return new BatteryMonitorRecord(reinterpret_cast<BatteryMonitorData*>(decrypted));

    default:
      return nullptr;
  }
}

void VictronPacketDecoder::AddKey(bd_addr_t mac, adv_key_t key) {
  _deviceKeys[mac] = key;
}

uint8_t* VictronPacketDecoder::DecryptPacket(VictronManufacturerRecord* vicData, bd_addr_t mac) {
  auto key = _deviceKeys[mac];

  if (vicData->encryptKeyMatch != key[0]) {
    //Serial.println("Key does not match");
    return nullptr;
  }

  uint8_t* rawPacket = new uint8_t[16]();

  // The number of encrypted bytes is given by the number of bytes in the manufacturer
  // data as a whole minus the number of bytes (10) in the header part of the data.
  uint16_t encrDataSize = 16;
  for (int i = 0; i < encrDataSize; i++) {
    rawPacket[i] = vicData->victronEncryptedData[i];
  }

  // Initialize IV
  uint8_t data_counter_lsb = (vicData->nonceDataCounter) & 0xff;
  uint8_t data_counter_msb = ((vicData->nonceDataCounter) >> 8) & 0xff;
  uint8_t iv[16] = {data_counter_lsb, data_counter_msb, 0};

  AES_ctx ctx;
  AES_init_ctx_iv(&ctx, key.data(), iv);
  AES_CTR_xcrypt_buffer(&ctx, rawPacket, encrDataSize);

  return rawPacket;
}