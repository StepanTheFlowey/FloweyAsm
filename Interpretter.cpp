#include "Interpretter.hpp"

#include "Terminal.hpp"

void Interpretter::interactive() {
  do {
    terminal.print("> ");
  } while(executor_.advence(compiller_.processLine(terminal.scanln() + '\n')));
}
