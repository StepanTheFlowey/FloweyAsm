#include "Workspace.hpp"

#include "Explorer.hpp"

Workspace workspace;

void Workspace::load() {

}

void Workspace::save() {

}

void Workspace::check() {
  if(!explorer.isExist(WORKSPACE_DIR_STATIC)) {
    explorer.mkdir(WORKSPACE_DIR_STATIC);
  }
  if(!explorer.isExist(WORKSPACE_DIR_DYNAMIC)) {
    explorer.mkdir(WORKSPACE_DIR_DYNAMIC);
  }

  explorer.setRoot(WORKSPACE_DIR_STATIC);
}
