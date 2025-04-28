#include "Land.hpp"
#include "main.hpp"
#include <iostream>

CLand::CLand(const std::string &name)
    : m_strName(name), m_bStop(false) {}

void CLand::ExecuteEvents() {
  while (true) {
    std::unique_lock<std::mutex> Lock(m_cMtx);

    // Wait until there is an event in the queue or stop signal
    m_cv.wait(Lock, [this]() { return !m_cEventQueue.empty() || m_bStop; });

    if (m_bStop && m_cEventQueue.empty()) {
      break; // Exit the thread if stop signal is received and no events are
             // left
    }

    // Process the next event
    VEvent Event = m_cEventQueue.front();
    m_cEventQueue.pop();
    m_nEventProcessed++;
    Lock.unlock();

    // Handle the event
    std::visit(
        [this](auto &&ev) {
          using T = std::decay_t<decltype(ev)>;
          if constexpr (std::is_same_v<T, SEventRain>) {
            PrintThreadSafe("Land " + m_strName +
                            " processes SEventRain with amount " +
                            std::to_string(ev.m_iAmount));
          } else if constexpr (std::is_same_v<T, SEventLightning>) {
            PrintThreadSafe("Land " + m_strName +
                            " processes SEventLightning with duration " +
                            std::to_string(ev.m_iDuration));
          } else if constexpr (std::is_same_v<T, SEventWind>) {
            PrintThreadSafe("Land " + m_strName +
                            " processes SEventWind with speed " +
                            std::to_string(ev.m_iSpeed));
          } else if constexpr (std::is_same_v<T, SEventThunder>) {
            PrintThreadSafe("Land " + m_strName +
                            " processes SEventThunder with intensity " +
                            std::to_string(ev.m_iIntensity));
          }
        },
        Event);
    std::this_thread::sleep_for(std::chrono::nanoseconds(1));
  }
}

void CLand::AddEvent(const VEvent &event) {
  {
    std::lock_guard<std::mutex> Lock(m_cMtx);
    m_cEventQueue.push(event);
  }
  m_cv.notify_one(); // Notify the land to process the event
}

void CLand::StartEventExecution() {
  m_cThread = std::thread(&CLand::ExecuteEvents, this);
}

void CLand::StopEventExecution() {
  {
    std::lock_guard<std::mutex> Lock(m_cMtx);
    m_bStop = true;
  }
  m_cv.notify_all(); // Notify the land to stop processing events
  if (m_cThread.joinable()) {
    m_cThread.join(); // Wait for the thread to finish
  }
}