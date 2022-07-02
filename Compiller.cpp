#include "Compiller.hpp"

#include "Terminal.hpp"

const OperationDescription translateTable[] = {
  { "NOP" , 0, Operation::NOP  },
  { "BRK" , 0, Operation::BRK  },
  { "HALT", 1, Operation::HALT },

  { "SET" , 2, Operation::SET  },
  { "MOV" , 2, Operation::MOV  },
  { "SWAP", 2, Operation::SWAP },

  { "ADD" , 2, Operation::ADD  },
  { "SUB" , 2, Operation::SUB  },
  { "MUL" , 2, Operation::MUL  },
  { "DIV" , 2, Operation::DIV  },
};
constexpr int translateTableSize = sizeof(translateTable) / sizeof(OperationDescription);

const OperationDescription* translateOperation(const char* name) {
  for(operation_id_t i = 0; i < translateTableSize; ++i) {
    if(strcmp(name, translateTable[i].name) == 0) {
      return &translateTable[i];
    }
  }
  return nullptr;
}

OperationBytecode Compiller::processLine(const String& lineIn) {
  using Op = Operation;

  OperationBytecode code;
  String line = lineIn;

  String str;
  string_size_t count = 0;
  string_size_t offset = 0;
  uint8_t argsCount = 0;
  uint8_t arg = 0;
  bool firstWord = true;

  while(!line.isEmpty()) {
    char ch = line.getFront();
    line.popFront();

    if(ch != ' ' && ch != '\n') {
      str.pushBack(ch);
      ++offset;
      ++count;
      continue;
    }

    str.truncate();
    if(str.isEmpty()) {
      ++offset;
      continue;
    }

    if(firstWord) {
      firstWord = false;

      const OperationDescription* desc = translateOperation(str.c_str());

      if(!desc) {
        error(offset, count, "no such op", lineIn.c_str());
        return code;
      }

      code.op = desc->id;
      argsCount = desc->argsCount;
    }
    else {
      if(argsCount == arg) {
        error(offset, count, "args overflow", lineIn.c_str());
        code.op = Op::NOT_AN_OP;
        return code;
      }

      switch(code.op) {
        case Op::HALT:
          code.argConstInt[0] = str.parseLong();
        case Op::SET:
          if(arg == 0) {
            code.argRegs[0] = str.parseInt();
          }
          else {
            code.argConstInt[1] = str.parseLong();
          }
          break;
        default:
          code.argRegs[arg] = str.parseInt();
          break;
      }
      ++arg;
    }
    ++offset;
    count = 0;
    str.clear();
  }

  if(arg != argsCount) {
    offset = lineIn.getLenght() - 1;
    offset = offset > 255 ? 0 : offset;
    count = offset;
    error(offset, count, "args underflow", lineIn.c_str());
    code.op = Op::NOT_AN_OP;
  }
  return code;
}

void Compiller::error(string_size_t offset, string_size_t count, const char* what, const char* in) {
  terminal.println("process error:");
  terminal.println(what);
  terminal.print(in);
  for(; offset != count; --offset) {
    terminal.print(" ");
  }
  for(; count != 0; --count) {
    terminal.print("^");
  }
  terminal.println();
}
