#include <iostream>
#include <mutex>
#include <string>

#define ENABLE_DEBUG 0 // Set to 1 to enable debug messages
inline std::mutex PrintMutex; // Global mutex for synchronizing console output

inline void PrintThreadSafe(const std::string &strMessage) {
#if ENABLE_DEBUG
  std::lock_guard<std::mutex> lock(PrintMutex); // Lock the mutex
  std::cout << strMessage << std::endl;
#endif
}
