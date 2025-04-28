#include "EldenTree.hpp"
#include "Event.hpp"
#include <atomic>
#include <memory>
#include <string>
#include <thread>

class CGod {
protected:
  std::thread m_cThread;
  std::mutex m_cMtx; // Mutex for thread safety
  bool m_bStop = false; // Flag to control the thread
  std::string m_strName;
  std::shared_ptr<CEldenTree> m_pcTree;
  std::vector<std::string> m_vecLands; // List of lands associated with this god
  size_t m_nEventGenerated = 0;      // Event count for this god

protected:
  virtual void GenerateEvents() = 0; // Function to generate events
public:
  CGod(const std::string &strName, std::shared_ptr<CEldenTree> pcTree);

  size_t GetEventGenerated();

  void AddLand(const std::string &strLand) { m_vecLands.push_back(strLand); }
  void StartEventGeneration();
  void StopEventGeneration();
};

class CGodWind : public CGod {
private:
  void GenerateEvents();

public:
  CGodWind(std::shared_ptr<CEldenTree> pcTree);
};

class CGodRain : public CGod {
private:
  void GenerateEvents();

public:
  CGodRain(std::shared_ptr<CEldenTree> pcTree);
};

class CGodThunder : public CGod {
private:
  void GenerateEvents();

public:
  CGodThunder(std::shared_ptr<CEldenTree> pcTree);
};

class CGodLightning : public CGod {
private:
  void GenerateEvents();

public:
  CGodLightning(std::shared_ptr<CEldenTree> pcTree);
};

class CGodDeath : public CGod {
private:
  void GenerateEvents();

public:
  CGodDeath(std::shared_ptr<CEldenTree> pcTree);
};

class CGodBirth : public CGod {
private:
  void GenerateEvents();

public:
  CGodBirth(std::shared_ptr<CEldenTree> pcTree);
};
