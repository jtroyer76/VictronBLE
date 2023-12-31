#include <gtest/gtest.h>

#include "VictronPacketDecoder.h"
#include "BatteryMonitorRecord.h"

TEST(VictronPacketDecoder, DecryptPacket) {

  unsigned char data[] = {
      0xE1, 0x02, 0x10, 0x02, 0x89, 0xA3, 0x02, 0x3D, 0x74, 0x53, 0x00, 0x91, 0x6e,
      0x1B, 0x0B, 0x64, 0x48, 0x74, 0x19, 0x7D, 0x9B, 0xA8, 0x62, 0xA7, 0x0C,
  };

  bd_addr_t mac { 0xfb, 0x82, 0x3f, 0xe5, 0x4f, 0x08 };
  adv_key_t key { 0x53, 0xf5, 0x27, 0xcc, 0x8d, 0xbb, 0x22, 0x23, 0xe3, 0xb7, 0x91, 0xec, 0x42, 0xe4, 0xdb, 0x3c };
    
  auto packetDecoder = new VictronPacketDecoder();
  packetDecoder->AddKey(mac, key);
  auto record = reinterpret_cast<VictronManufacturerRecord*>(data);

  VictronRecord* decoded = packetDecoder->Decode(record, 25);
  auto batteryMonitor = dynamic_cast<BatteryMonitorRecord*>(decoded);

  EXPECT_NE(batteryMonitor, nullptr);
  EXPECT_EQ(batteryMonitor->data->timeToGo, 0xFFFF);
}