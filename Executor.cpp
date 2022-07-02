#include "Executor.hpp"

#include "Terminal.hpp"

const status_t& Executor::getStatus() const {
  return status_;
}

bool Executor::advence(const OperationBytecode instruction) {
  using Op = Operation;

  switch(instruction.op) {
    case Op::NOT_AN_OP:
    case Op::NOP:
      break;

    case Op::BRK:
      for(register_number_t i = 0; i < REGISTER_COUNT; ++i) {
        terminal.print('r');
        terminal.print(int(i));
        terminal.print(":\t");
        terminal.println(registers_[i]);
      }
      break;

    case Op::HALT:
      status_ = instruction.argConstInt[0];
    default:
      return false;

    case Op::SET:
      registers_[instruction.argRegs[0]] = instruction.argConstInt[1];
      break;

    case Op::MOV:
      registers_[instruction.argRegs[0]] = registers_[instruction.argRegs[1]];
      break;

    case Op::ADD:
      registers_[instruction.argRegs[0]] += registers_[instruction.argRegs[1]];
      break;

    case Op::SUB:
      registers_[instruction.argRegs[0]] -= registers_[instruction.argRegs[1]];
      break;

    case Op::MUL:
      registers_[instruction.argRegs[0]] *= registers_[instruction.argRegs[1]];
      break;

    case Op::DIV:
      registers_[instruction.argRegs[0]] /= registers_[instruction.argRegs[1]];
      break;
  }
  return true;
}
