#pragma once

#include <array>
#include <ctime>
#include <iostream>
#include <sstream>
#include <vector>

#include "ImGuiHelper.hpp"

enum class LogType { COMBAT, LOOT, COUNT };

struct LogEntry {
  LogType logType;
  tm timestamp;
  std::string message;
};

constexpr int LOG_CAP = 50;

class CombatLog {
 public:
  CombatLog() = delete;
  static std::string getHour(tm datetime, bool includeSeconds = true);
  static void addLog(LogEntry logEntry);
  static void addLog(std::string message, LogType logType);
  static void addLog(std::stringstream message, LogType logType);
  static void display();

 private:
  inline static std::vector<LogEntry> logs{};
  static std::string constructLog(LogEntry LogEntry);
  static void trimLog();
  static inline bool scrollToBottom = true;
};
