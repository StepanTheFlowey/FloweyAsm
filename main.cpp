#include "main.hpp"

#include "Terminal.hpp"
#include "Explorer.hpp"
#include "Workspace.hpp"

void shutdown() {
  terminal.clear();
  workspace.save();

  exit(EXIT_SUCCESS);
}

int main() {
  terminal.println(stringWelcome);

  workspace.load();
  workspace.check();

  while(true) {
    terminal.print(stringShoice);
    char ch = terminal.get();
    terminal.flush();

    switch(ch) {
      case '1':
        explorer.interactive();
        break;
      case '2':
        shutdown();
        break;
    }

    terminal.clear();
  }
}
