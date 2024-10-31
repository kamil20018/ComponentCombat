#pragma once

#include <SFML/Graphics.hpp>
class State {
 public:
  State(){};
  virtual ~State(){};

  virtual void init() = 0;
  virtual void processInput() = 0;
  virtual void update() = 0;
  virtual void draw() = 0;
  virtual void pause() {};
  virtual void start() {};
};