#pragma once

#include "Compiller.hpp"

using status_t = int32_t;

class Executor {
public:

  Executor() = default;

  ~Executor() = default;

  const status_t& getStatus() const;

  bool advence(const OperationBytecode op);
protected:

  status_t status_ = 0;
  register_t registers_[REGISTER_COUNT]{};
};
