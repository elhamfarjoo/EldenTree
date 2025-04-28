#pragma once
#include "EldenTree.hpp"
#include "Event.hpp"
#include <condition_variable>
#include <memory>
#include <mutex>
#include <queue>
#include <string>
#include <thread>

class CLand {
private:
  std::string m_strName;                // Name of the land
  std::queue<VEvent> m_cEventQueue;     // Queue of events for this land
  std::mutex m_cMtx;                    // Mutex for thread safety
  std::condition_variable m_cv;   // Condition variable for synchronization
  bool m_bStop = false;           // Flag to stop the land's processing thread
  std::thread m_cThread;          // Thread for processing events
  size_t m_nEventProcessed = 0; // Event count for this land

  void ExecuteEvents();

public:
  explicit CLand(const std::string &strName);
  size_t GetEventProcessed() { return m_nEventProcessed; }

  // Add an event to the land's queue
  void AddEvent(const VEvent &event);

  // Process events related to this land

  // Stop processing events
  void StartEventExecution();
  void StopEventExecution();
};