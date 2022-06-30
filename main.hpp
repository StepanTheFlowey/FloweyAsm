//
//   OP   Syntax                             OPID DONE  Description
//   ---- BASE ---------------------------------------------------
//   NOP                                     0    true  Idle clock
//   HALT                                    1    true  Idle user
//   ---- REGISTERS -----------------------------------
//   MOV  <reg to> <from>                    2    true  Sets register to value
//   SWAP <reg first> <reg second>           3    true  Swaps registers
//   ---- BASIC LOGIC ---------------------------------
//   SNT  <reg out> <a>                      4    false Set NoT
//   SEQ  <reg out> <a> <b>                  5    false Set EQual
//   SNQ  <reg out> <a> <b>                  6    false Set Not eQual
//   SGE  <reg out> <a> <b>                  7    false Set Greater Equal
//   SLE  <reg out> <a> <b>                  8    false Set Less Equal
//   SGT  <reg out> <a> <b>                  9    false Set Greater Than
//   SLT  <reg out> <a> <b>                  10   false Set Less Than
//   ---- BASIC MATH ----------------------------------
//   ADD  <reg out> <a> <b>                  11   true  Adds numbers
//   SUB  <reg out> <a> <b>                  12   true  Substracts numbers
//   MUL  <reg out> <a> <b>                  13   true  Multiplys numbers
//   DIV  <reg out> <a> <b>                  14   true  Divides numbers
//   ---- STACK ---------------------------------------
//   PUSH <num in>                           15   false Pushs number to stack
//   POP  <reg out>                          16   false Pops number from stack to register
//   ---- MEMORY --------------------------------------
//   LD   <reg in> <address>                 17   false Loads value from page
//   ST   <address> <reg out>                18   false Stores value to page
//   ---- BRANCH --------------------------------------
//   JMP  <line>                             19   false Jumps to line
//   JMPR <line offset>                      20   false Jumps relative to line
//   JSR  <subroutine>                       21   false Calls subroutine
//   RST                                     22   false Exits subroutine
//
#pragma once

#define STRING_FORCE_IMPL_CHAR 0

#ifndef __cplusplus
#error Code must be compilled as C++!
#endif // !__cplusplus

#if __cplusplus < 199711L
#error C++ standard must be at least 11!
#endif

#define COMPILLER_TIME __TIME__
#define COMPILLER_DATE __DATE__

#if _WIN32

#define STL_IS_AVAILABLE 1
#define PLATFORM_STRING "Windows"
#define PLATFORM_WINDOWS 1

#define NOMINMAX

#else

#define STL_IS_AVAILABLE 0
#define PLATFORM_STRING "unknown"
#define PLATFORM_UNKNOWN 1

#endif

#include <inttypes.h>

constexpr const char* operator""_F(const char* str) {
#if A
  return F(str);
#else
  return str;
#endif
}

const char stringWelcome[] =
"Welcome to FloweyAsm!\n"
"Build date: " COMPILLER_TIME " " COMPILLER_DATE "\n"
"Build platform: " PLATFORM_STRING
;

const char stringShoice[] =
"1. Explorer\n"
"2. Exit\n"
"Select: "
;
