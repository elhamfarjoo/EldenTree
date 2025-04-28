#include "God.hpp"
#include "main.hpp"
#include <chrono>
#include <iostream>
#include <random>

CGod::CGod(const std::string &strName, std::shared_ptr<CEldenTree> pcTree)
    : m_strName(strName), m_pcTree(pcTree) {
  // Register the god with the EldenTree
  m_pcTree->RegisterGod(m_strName);
  PrintThreadSafe("God " + m_strName + " has been created and registered.");
}

void CGod::StartEventGeneration() {
  m_bStop = false; // Reset the stop flag
  m_cThread = std::thread(&CGod::GenerateEvents, this);
}

void CGod::StopEventGeneration() {
  {
    std::lock_guard<std::mutex> Lock(m_cMtx);
    m_bStop = true; // Set the stop flag
  }
  if (m_cThread.joinable()) {
    m_cThread.join();
  }
}
size_t CGod::GetEventGenerated() {
  std::lock_guard<std::mutex> Lock(m_cMtx);
  return m_nEventGenerated;
}

//-------------------------------------------------------------

CGodWind::CGodWind(std::shared_ptr<CEldenTree> cTree) : CGod("Wind", cTree) {}

void CGodWind::GenerateEvents() {
  std::random_device Rd;
  std::mt19937 Gen(Rd());
  std::uniform_int_distribution<> SpeedDist(10, 100); // Random wind speed

  while (true) {
    {
      std::lock_guard<std::mutex> Lock(m_cMtx); // Lock the mutex for thread safety
      if(m_bStop) {
        break; // Exit the loop if the stop flag is set
      }
      for (const auto &Land : m_vecLands) {
        
        // Generate a wind event
        SEventWind WindEvent{Land, SpeedDist(Gen)};
        PrintThreadSafe("God " + m_strName +
          " generates a wind event with speed " +
          std::to_string(WindEvent.m_iSpeed) + " in land " + Land);
          
          // Push the event to EldenTree via the callback
          m_pcTree->PushEvent(m_strName, WindEvent);

          // Increment the event count
          m_nEventGenerated++;
      }
    }
    std::this_thread::sleep_for(std::chrono::nanoseconds(1));
  }
}

//-------------------------------------------------------------

CGodRain::CGodRain(std::shared_ptr<CEldenTree> cTree) : CGod("Rain", cTree) {}

void CGodRain::GenerateEvents() {
  std::random_device Rd;
  std::mt19937 Gen(Rd());
  std::uniform_int_distribution<> AmountDist(1, 100); // Random rain amount

  while (true) {
    {
      std::lock_guard<std::mutex> Lock(m_cMtx); // Lock the mutex for thread safety
      if(m_bStop) {
        break; // Exit the loop if the stop flag is set
      }
      for (const auto &Land : m_vecLands) {

        // Generate a rain event
        SEventRain RainEvent{Land, AmountDist(Gen)};
        PrintThreadSafe("God " + m_strName +
                        " generates a rain event with amount " +
                        std::to_string(RainEvent.m_iAmount) + " in land " + Land);

        // Push the event to EldenTree via the callback
        m_pcTree->PushEvent(m_strName, RainEvent);

        // Increment the event count
        m_nEventGenerated++;
      }
    }
    std::this_thread::sleep_for(std::chrono::nanoseconds(1));
  }
}

//-------------------------------------------------------------

CGodThunder::CGodThunder(std::shared_ptr<CEldenTree> cTree) : CGod("Thunder", cTree) {}

void CGodThunder::GenerateEvents() {
  std::random_device Rd;
  std::mt19937 Gen(Rd());
  std::uniform_int_distribution<> IntensityDist(
      1, 100); // Random thunder intensity

  while (true) {
    {
      std::lock_guard<std::mutex> Lock(m_cMtx); // Lock the mutex for thread safety
      if(m_bStop) {
        break; // Exit the loop if the stop flag is set
      }
      for (const auto &Land : m_vecLands) {

        // Generate a thunder event
        SEventThunder ThunderEvent{Land, IntensityDist(Gen)};
        PrintThreadSafe(
            "God " + m_strName + " generates a thunder event with intensity " +
            std::to_string(ThunderEvent.m_iIntensity) + " in land " + Land);

        // Push the event to EldenTree via the callback
        m_pcTree->PushEvent(m_strName, ThunderEvent);

        // Increment the event count
        m_nEventGenerated++;
      }
    }
    std::this_thread::sleep_for(std::chrono::nanoseconds(1));
  }
}

//-------------------------------------------------------------

CGodLightning::CGodLightning(std::shared_ptr<CEldenTree> cTree) : CGod("Lightning", cTree) {}

void CGodLightning::GenerateEvents() {
  std::random_device Rd;
  std::mt19937 Gen(Rd());
  std::uniform_int_distribution<> DurationDist(1, 100); // Random lightning duration

  while (true) {
    {
      std::lock_guard<std::mutex> Lock(m_cMtx); // Lock the mutex for thread safety
      if(m_bStop) {
        break; // Exit the loop if the stop flag is set
      }
      for (const auto &Land : m_vecLands) {

        // Generate a lightning event
        SEventLightning LightningEvent{Land, DurationDist(Gen)};
        PrintThreadSafe(
            "God " + m_strName + " generates a lightning event with duration " +
            std::to_string(LightningEvent.m_iDuration) + " in land " + Land);

        // Push the event to EldenTree via the callback
        m_pcTree->PushEvent(m_strName, LightningEvent);

        // Increment the event count
        m_nEventGenerated++;
      }
    }
    std::this_thread::sleep_for(std::chrono::nanoseconds(1));
  }
}

//-------------------------------------------------------------
// CGodDeath and CGodBirth classes can be implemented similarly