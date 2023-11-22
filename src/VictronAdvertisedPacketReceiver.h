#pragma once

#include <BLEAdvertisedDevice.h>
#include "VictronPacketDecoder.h"

class VictronAdvertisedPacketReceiver : public BLEAdvertisedDeviceCallbacks {
 public:
  VictronAdvertisedPacketReceiver(VictronPacketDecoder* packetDecoder) {
    _packetDecoder = packetDecoder;
  }

  void onResult(BLEAdvertisedDevice advertisedDevice);

 private:
  VictronPacketDecoder* _packetDecoder;
};