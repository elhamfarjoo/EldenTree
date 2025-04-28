#pragma once
#include <string>
#include <variant>

enum EEventType {
  EEVENTTYPE_BIRTH = 0,
  EEVENTTYPE_DEATH,
  EEVENTTYPE_RAIN,
  EEVENTTYPE_THUNDER,
  EEVENTTYPE_LIGHTNING,
  EEVENTTYPE_WIND,
  // Add more event types as needed
};

struct SEventBirth {
  std::string m_strLand;
  std::string m_strName;
};
struct SEventDeath {
  std::string m_strLand;
  std::string m_strName;
  std::string m_strCause;
};
struct SEventRain {
  std::string m_strLand;
  int m_iAmount;
};
struct SEventThunder {
  std::string m_strLand;
  int m_iIntensity;
};
struct SEventLightning {
  std::string m_strLand;
  int m_iDuration;
};
struct SEventWind {
  std::string m_strLand;
  int m_iSpeed;
};
// Define a variant type for events
using VEvent = std::variant<SEventBirth, SEventDeath, SEventRain, SEventThunder,
                            SEventLightning, SEventWind>;
