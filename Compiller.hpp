#pragma once

#include "main.hpp"

#include "String.hpp"

using register_t = int64_t;
using operation_id_t = uint8_t;
using register_number_t = uint8_t;

struct OperationDescription {
  const char* name = nullptr;
  operation_id_t id = 0;
  uint8_t argsCount = 0;
};

struct OperationBytecode {
  operation_id_t op = 0;
  register_number_t args[4]{};
};

class Compiller {
public:

  Compiller() = default;

  ~Compiller() = default;

  OperationBytecode processLine(String line);

protected:

  void error(string_size_t o, string_size_t c, const char* what, const char* in);

};
