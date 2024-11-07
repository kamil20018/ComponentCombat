#pragma once

#include <algorithm>
#include <chrono>
#include <iostream>

namespace timer {

  static inline void time(std::function<void()> func, std::string prefix = "") {
    auto start = std::chrono::high_resolution_clock::now();
    func();
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    if (prefix.size() > 0) std::cout << prefix << " ";
    std::cout << (float)(duration.count()) / 1000.0f << "ms" << std::endl;
  }
};  // namespace timer
