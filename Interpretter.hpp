#pragma once

#include "main.hpp"

#include "Compiller.hpp"
#include "Executor.hpp"

class Interpretter {
public:

  Interpretter() = default;

  ~Interpretter() = default;

  void interactive();
protected:

  Compiller compiller_;
  Executor executor_;
};
