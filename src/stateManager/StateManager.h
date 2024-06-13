#pragma once

#include <memory>

#include "State.h"

class StateManager {
 public:
  StateManager();
  ~StateManager();

  void addState(std::shared_ptr<State> toAdd, bool replace = false);
  void popCurrent();
  void processStateChange();
  std::shared_ptr<State> &getCurrent();

 private:
  std::vector<std::shared_ptr<State> > stateStack;
  std::shared_ptr<State> newState;

  bool add;
  bool replace;
  bool remove;
};