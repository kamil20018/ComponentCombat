#include "CombatLog.hpp"

std::string CombatLog::getHour(tm datetime, bool includeSeconds) {
  char output[50];
  if (includeSeconds)
    strftime(output, 50, "[%H:%M:%S]", &datetime);
  else
    strftime(output, 50, "[%H:%M]", &datetime);
  return output;
}

void CombatLog::addLog(LogEntry logEntry) {
  scrollToBottom = true;
  logs.push_back(logEntry);
  trimLog();
}

void CombatLog::addLog(std::string message, LogType logType) {
  scrollToBottom = true;
  time_t timestamp = time(&timestamp);
  struct tm datetime = *localtime(&timestamp);
  logs.push_back({logType, datetime, message});
  trimLog();
}

void CombatLog::addLog(std::stringstream message, LogType logType) {
  scrollToBottom = true;
  time_t timestamp = time(&timestamp);
  struct tm datetime = *localtime(&timestamp);
  logs.push_back({logType, datetime, message.str()});
  trimLog();
}

void CombatLog::trimLog() {
  if (logs.size() > LOG_CAP) {
    logs.erase(logs.begin(), logs.begin() + (logs.size() - LOG_CAP));
  }
}

std::string CombatLog::constructLog(LogEntry logEntry) {
  return getHour(logEntry.timestamp) + logEntry.message;
}

void CombatLog::display() {
  ImGuiHelper::dockNextWindow(WindowDock::TOP_LEFT, 0.5f, 0.24f, 0.005f, 0.005f);
  ImGui::Begin("test", nullptr, ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoBringToFrontOnFocus);

  for (const auto& logEntry : logs) {
    ImGui::Text(constructLog(logEntry).c_str());
  }
  if (scrollToBottom) {
    ImGui::SetScrollHereY(1.0f);
    scrollToBottom = false;
  }
}