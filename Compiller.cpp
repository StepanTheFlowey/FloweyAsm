#include "Compiller.hpp"

#include "Terminal.hpp"

const OperationDescription translateTable[] = {
  {"NOP" , 0, 0},
  {"HALT", 0, 1},
  {"SET" , 0, 2},
  {"SWAP", 0, 3}
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

OperationBytecode Compiller::processLine(String line) {
  OperationBytecode code;

  String str;
  string_size_t c = 0;
  string_size_t o = 0;
  bool firstWord = true;
  while(!line.isEmpty()) {
    char ch = line.getFront();
    line.popFront();

    ++c;
    ++o;

    if(ch != ' ' && ch != '\n') {
      str.pushBack(ch);
      continue;
    }

    if(firstWord) {
      firstWord = false;

      const OperationDescription* desc = translateOperation(str.c_str());

      if(!desc) {

      }
    }
    c = 0;
    str.clear();
  }
}

void Compiller::error(string_size_t o, string_size_t c, const char* what, const char* in) {
  terminal.println("processing error:");
  terminal.println(in);
  for(; o != c; --o) {
    terminal.println(" ");
  }

  for(; c != string_npos; --c) {
    terminal.println("^");
  }
}
