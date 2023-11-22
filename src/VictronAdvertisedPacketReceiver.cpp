#include "VictronAdvertisedPacketReceiver.h"
#include <Arduino.h>
#include <M5Core2.h>
#include <experimental/array>

#define manDataSizeMax 31
#define victronVendorId 0x02e1

void VictronAdvertisedPacketReceiver::onResult(BLEAdvertisedDevice advertisedDevice) {
  // See if we have manufacturer data and then look to see if it's coming from a Victron device.
  if (advertisedDevice.haveManufacturerData() == true) {
    // Here's the thing: BLE specs say our manufacturer data can be a max of 31 bytes.
    // But: The library code puts this data into a String, which we will then copy to
    // a character (i.e., byte) buffer using String.toCharArray(). Assuming we have the
    // full 31 bytes of manufacturer data allowed by the BLE spec, we'll need to size our
    // buffer with an extra byte for a null terminator. Our toCharArray() call will need
    // to specify *32* bytes so it will copy 31 bytes of data with a null terminator
    // at the end. The real question is WHY does the BLE library code use String???
    // char manCharBuf[manDataSizeMax + 1];

    std::string manData = advertisedDevice.getManufacturerData();
    // int manDataSize = manData.length();  // This does not count the null at the end.

    // Copy the data from the String to a byte array. Must have the +1 so we
    // don't lose the last character to the null terminator.
    // strncpy(manCharBuf, manData.c_str(), manData.length());
    // manData.toCharArray((char *)manCharBuf, manDataSize + 1);

    // Cast the manufacturer data string to our struct
    VictronManufacturerRecord* vicData = reinterpret_cast<VictronManufacturerRecord*>(&manData[0]);

    // ignore this packet if the Vendor ID isn't Victron.
    if (vicData->vendorID != victronVendorId) {
      return;
    }

    Serial.print("Address: ");
    Serial.println(advertisedDevice.getAddress().toString().c_str());

    uint8_t* mac = advertisedDevice.getAddress().getNative()[0];
    auto record = _packetDecoder->Decode(vicData, { mac[0], mac[1], mac[2], mac[3], mac[4], mac[5] });
    if (record != nullptr) {
      Serial.println(record->ToString().c_str());
      M5.Lcd.println(record->ToString().c_str());
      delete record;
    }
  }
}