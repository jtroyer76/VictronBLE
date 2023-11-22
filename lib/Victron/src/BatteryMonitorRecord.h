#pragma once

#include "VictronRecord.h"
#include <stdint.h>

struct __attribute__((packed)) BatteryMonitorData {
  enum AuxInput : uint8_t {
    AuxVoltage = 0,
    MidVoltage = 1,
    Temperature = 2,
    None = 3,
  };

  uint16_t timeToGo;
  uint16_t batteryVoltage;
  uint16_t alarmReason;
  uint16_t auxValue;
  AuxInput auxIntput : 2;
  int32_t batteryCurrent : 22;
  int32_t consumedAh : 20;
  uint16_t stateOfCharge : 10;
  int16_t unused : 10;
};

class BatteryMonitorRecord : public VictronRecord {
 public:
  BatteryMonitorRecord(BatteryMonitorData* record) {
    data = record;
  }

  ~BatteryMonitorRecord() {
    delete[] data;
  }

  BatteryMonitorData* data;

  std::string ToString() {
    char message[100];
    snprintf(message,
             100,
             "BatteryMonitor=> Battery: %hd Volts: %hd Amps: %hd\n",
             data->stateOfCharge,
             data->batteryVoltage,
             data->batteryCurrent);

    return std::string(message);
  }
};