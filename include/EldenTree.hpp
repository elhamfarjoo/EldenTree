#pragma once
#include "Event.hpp"
#include <atomic>
#include <memory>
#include <mutex>
#include <optional>
#include <queue>
#include <string>
#include <thread>
#include <unordered_map>
#include <variant>
#include <vector>

class CLand; // Forward declaration

class CEldenTree {
public:
  void RegisterGod(const std::string &strGodName);
  void PushEvent(const std::string &strGodName, const VEvent &vEvent);
  void RegisterLand(const std::string &strLandName, std::shared_ptr<CLand> pcLand);
  void StartEventRouting();
  void StopEventRouting();

private:
  std::optional<VEvent> GetNextEvent();
  void RouteEvents();
  std::unordered_map<std::string, std::queue<VEvent>> m_umapGodEvents;
  std::unordered_map<std::string, std::shared_ptr<CLand>> m_umapLands;
  std::vector<std::string> m_vecGods;
  size_t m_nCurrentIndex = 0;
  std::mutex m_cMtx;
  std::thread m_cThread;
  bool m_bStop = false; // Stop flag for the thread
};
