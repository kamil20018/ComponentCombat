#include "StateManager.h"

StateManager::StateManager() : add(false), replace(false), remove(false) {}

StateManager::~StateManager() {}

/*Adds the state from which the method was called and puts the new state atop
of the state stack. That results in the preservation of state from which this
method was called.*/
void StateManager::addState(std::shared_ptr<State> toAdd, bool replace) {
  this->add = true;
  this->newState = std::move(toAdd);
  this->replace = replace;
}

/*Pops the current state erasing it completely*/
void StateManager::popCurrent() { this->remove = true; }

void StateManager::processStateChange() {
  if (this->remove && !this->stateStack.empty()) {
    this->stateStack.pop_back();

    if (!stateStack.empty()) {
      stateStack.back()->start();
    }

    this->remove = false;
  }

  if (this->add) {
    if (this->replace && !stateStack.empty()) {
      this->stateStack.pop_back();
    }

    if (!this->stateStack.empty()) {
      this->stateStack.back()->pause();
    }

    this->stateStack.push_back(std::move(this->newState));

    this->stateStack.back()->init();
    this->stateStack.back()->start();
    this->add = false;
  }
}

std::shared_ptr<State>& StateManager::getCurrent() { return stateStack.back(); }