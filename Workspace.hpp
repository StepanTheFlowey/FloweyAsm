#pragma once

#define WORKSPACE_DIR_STATIC  "rom"
#define WORKSPACE_DIR_DYNAMIC "ram"

class Workspace {
public:

  Workspace() = default;

  ~Workspace() = default;

  void load();

  void save();

  void check();
};
extern Workspace workspace;
