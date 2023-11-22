#pragma once

#include "VictronRecord.h"
#include <stdint.h>

struct __attribute__((packed)) SolarData {
  uint8_t deviceState;
  uint8_t errorCode;
  int16_t batteryVoltage;
  int16_t batteryCurrent;
  uint16_t todayYield;
  uint16_t pvPower;
  uint8_t outputCurrentLo;  // Low 8 bits of output current (in 0.1 Amp increments)
  uint8_t outputCurrentHi;  // High 1 bit of ourput current (must mask off unused bits)
  uint8_t unused[4];        // Not currently used by Victron, but it could be in the future.
};

class SolarChargerRecord : public VictronRecord {
 public:
  SolarChargerRecord(SolarData* record) {
    data = record;
  }

  ~SolarChargerRecord() {
    delete[] data;
  }

  SolarData* data;

  std::string ToString() {
    char message[100];
    snprintf(message,
             100,
             "SolarCharger=> Power: %hd Volts: %hd Amps: %hd\n",
             data->pvPower,
             data->batteryVoltage,
             data->batteryCurrent);

    return std::string(message);
  }
};