//
// OP   Syntax                             OPID Description
// ---- BASE ----------------------------------------------
// NOP                                     0    Idle clock
// BRK                                     1    Debug break
// HALT <const code>                       2    Stops program
// ---- REGISTERS -----------------------------------
// SET  <a> <c>                            3    ra = c
// MOV  <a> <b>                            4    ra = rb
// SWAP <a> <b>                            5    Swaps registers
// ---- BASIC LOGIC ---------------------------------
// SNT  <a>                                6    a = !a
// SEQ  <a> <b>                            7    a = a == b
// SNQ  <a> <b>                            8    a = a != b
// SGE  <a> <b>                            9    a = a >= b
// SLE  <a> <b>                            10   a = b <= b
// SGT  <a> <b>                            11   a = a > b
// SLT  <a> <b>                            12   a = a < b
// ---- BASIC MATH ----------------------------------
// ADD  <a> <b>                            13   ra += rb
// SUB  <a> <b>                            14   ra -= rb
// MUL  <a> <b>                            15   ra *= rb
// DIV  <a> <b>                            16   ra /= rb
// ---- STACK ---------------------------------------
// PUSH <num in>                           17   Pushs number to stack
// POP  <reg out>                          18   Pops number from stack to register
// ---- MEMORY --------------------------------------
// LD   <reg in> <address>                 19   Loads value from page
// ST   <address> <reg out>                20   Stores value to page
// ---- BRANCH --------------------------------------
// JMP  <line>                             21   Jumps to line
// JMPR <line offset>                      22   Jumps relative to line
// JSR  <subroutine>                       23   Calls subroutine
// RST                                     24   Exits subroutine
//
//Halt codes:
// Code Description
// 0    Sucsessful
// 1    Error
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
"3. Interpretter\n"
"Select: "
;
