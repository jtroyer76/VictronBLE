#pragma once

#include <string>

class VictronRecord {
 public:
  virtual std::string ToString() = 0;
  virtual ~VictronRecord() = default;
};