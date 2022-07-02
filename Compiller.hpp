#pragma once

#include "main.hpp"

#include "String.hpp"


using register_t = int64_t;
using register_number_t = uint8_t;
using operation_id_t = uint8_t;

enum class Operation : operation_id_t {
  NOP = 0,
  BRK,
  HALT,

  SET,
  MOV,
  SWAP,

  ADD = 12,
  SUB,
  MUL,
  DIV,

  NOT_AN_OP
};

constexpr register_number_t REGISTER_COUNT = 32;


struct OperationDescription {
  const char* name = nullptr;
  uint8_t argsCount = 0;
  Operation id = Operation::NOT_AN_OP;
};

struct OperationBytecode {
  Operation op = Operation::NOT_AN_OP;
  union {
    register_number_t argRegs[8];
    int32_t argConstInt[2];
    float argConstFloat[2];
  };
};

class Compiller {
public:

  Compiller() = default;

  ~Compiller() = default;

  OperationBytecode processLine(const String& line);
protected:

  void error(string_size_t o, string_size_t c, const char* what, const char* in);
};
