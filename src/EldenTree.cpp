#include "EldenTree.hpp"
#include "Land.hpp"
#include "main.hpp"
#include <Variant>
#include <algorithm>

void CEldenTree::RegisterGod(const std::string &strGodName) {
  std::lock_guard<std::mutex> Lock(m_cMtx);
  if (std::find(m_vecGods.begin(), m_vecGods.end(), strGodName) ==
      m_vecGods.end()) {
    m_umapGodEvents[strGodName] = std::queue<VEvent>();
    m_vecGods.push_back(strGodName);
  }
}

void CEldenTree::RegisterLand(const std::string &strLandName,
                              std::shared_ptr<CLand> pcLand) {
  std::lock_guard<std::mutex> Lock(m_cMtx);
  if (m_umapLands.find(strLandName) == m_umapLands.end()) {
    m_umapLands[strLandName] = pcLand;
  }
}
void CEldenTree::PushEvent(const std::string &strGodName, const VEvent &vEvent) {
  std::lock_guard<std::mutex> Lock(m_cMtx);
  if (m_umapGodEvents.find(strGodName) != m_umapGodEvents.end()) {
    m_umapGodEvents[strGodName].push(vEvent);
  }
}

void CEldenTree::StartEventRouting() {
  m_bStop = false; // Reset the stop flag
  m_cThread = std::thread(&CEldenTree::RouteEvents, this);
}

void CEldenTree::StopEventRouting() {
  {
    std::lock_guard<std::mutex> Lock(m_cMtx);
    m_bStop = true; // Set the stop flag
  }

  if (m_cThread.joinable()) {
    m_cThread.join();
  }
}

void CEldenTree::RouteEvents() {
  while (true) {
    std::optional<VEvent> Event = GetNextEvent();
    if (Event) {
      std::string StrLand = std::visit(
          [](const auto &ev) {
            // Access the common member `strLand`
            return ev.m_strLand;
          },
          *Event);

      // Check if the land exists
      auto It = m_umapLands.find(StrLand);
      if (It != m_umapLands.end()) {
        It->second->AddEvent(*Event);
      } else {
        PrintThreadSafe("Warning: Land " + StrLand +
                        " not found. Event discarded.");
      }

    } else if (!m_bStop) {
      std::this_thread::sleep_for(
          std::chrono::nanoseconds(10)); // Sleep to avoid busy waiting
    } else {
      break; // Exit the loop if stop signal is received
    }
  }
}

std::optional<VEvent> CEldenTree::GetNextEvent() {
  std::lock_guard<std::mutex> Lock(m_cMtx);
  if (m_vecGods.empty())
    return std::nullopt;

  size_t nNattempts = 0;
  while (nNattempts++ < m_vecGods.size()) {
    auto &strGodName = m_vecGods[m_nCurrentIndex];
    m_nCurrentIndex = (m_nCurrentIndex + 1) % m_vecGods.size();

    auto &Queue = m_umapGodEvents[strGodName];
    if (!Queue.empty()) {
      VEvent vEvent = Queue.front();
      Queue.pop();
      return vEvent;
    }
  }
  return std::nullopt; // No events available
}
