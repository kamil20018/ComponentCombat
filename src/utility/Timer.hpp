#pragma once

#include <SFML/Graphics.hpp>
#include <algorithm>
#include <chrono>
#include <iostream>

class Timer {
 public:
  static inline std::vector<float> timestamps;
  static inline void clear() {
    timestamps.clear();
  }
  static inline size_t dataCap{1000};
  static inline void time(std::function<void()> func, std::string prefix = "") {
    auto start = std::chrono::high_resolution_clock::now();
    func();
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    timestamps.push_back(duration.count() / 1000.0f);
    if (timestamps.size() > dataCap) {
      timestamps.erase(timestamps.begin());
    }
  }
  static inline void show() {
    // std::vector<float> test{12, 545, 20, 5};
    auto maxVal = std::max(timestamps.begin(), timestamps.end());
    float cap;
    if (maxVal != timestamps.end()) {
      cap = *maxVal;
      cap *= 1.1f;
    } else {
      cap = 100.0f;
    }
    ImGui::Begin("Character Creation", nullptr, ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoTitleBar);
    ImGui::PlotLines("", timestamps.data(), timestamps.size(), 0, nullptr, -1.0f, cap, ImVec2(0, 100));
    ImGui::End();
  }
};  // namespace timer
