#include "../include/EldenTree.hpp"
#include "../include/God.hpp"
#include "../include/Land.hpp"
#include "../include/main.hpp"

#include <chrono>
#include <iostream>
#include <memory>

int main() {
  //TODO: Define Gods and Lands to be part of separate vectors, making the code more generic and more readable.
  // Create the EldenTree instance
  std::shared_ptr<CEldenTree> Tree = std::make_shared<CEldenTree>();

  // Create the gods
  CGodRain RainGod(Tree);
  CGodThunder ThunderGod(Tree);
  CGodLightning LightningGod(Tree);
  CGodWind WindGod(Tree);

  // Create the lands
  std::shared_ptr<CLand> Atlantis = std::make_shared<CLand>("Atlantis");
  std::shared_ptr<CLand> Olympus = std::make_shared<CLand>("Olympus");
  std::shared_ptr<CLand> Rome = std::make_shared<CLand>("Rome");
  std::shared_ptr<CLand> Norse = std::make_shared<CLand>("Norse");
  std::shared_ptr<CLand> Perspolis = std::make_shared<CLand>("Perspolis");
  std::shared_ptr<CLand> Memphis = std::make_shared<CLand>("Memphis");
  std::shared_ptr<CLand> Babylon = std::make_shared<CLand>("Babylon");
  std::shared_ptr<CLand> Troy = std::make_shared<CLand>("Troy");

  // Register the lands with the EldenTree
  Tree->RegisterLand("Atlantis", Atlantis);
  Tree->RegisterLand("Olympus", Olympus);
  Tree->RegisterLand("Rome", Rome);
  Tree->RegisterLand("Norse", Norse);
  Tree->RegisterLand("Perspolis", Perspolis);
  Tree->RegisterLand("Memphis", Memphis);
  Tree->RegisterLand("Babylon", Babylon);
  Tree->RegisterLand("Troy", Troy);

  // Add lands to the gods
  RainGod.AddLand("Atlantis");
  RainGod.AddLand("Olympus");
  RainGod.AddLand("Rome");
  RainGod.AddLand("Norse");
  RainGod.AddLand("Perspolis");

  ThunderGod.AddLand("Olympus");
  ThunderGod.AddLand("Rome");
  ThunderGod.AddLand("Norse");
  ThunderGod.AddLand("Perspolis");
  ThunderGod.AddLand("Babylon");

  LightningGod.AddLand("Atlantis");
  LightningGod.AddLand("Olympus");

  WindGod.AddLand("Atlantis");
  WindGod.AddLand("Rome");


  // Start the event routing thread
  auto Start = std::chrono::high_resolution_clock::now();

  // Start the lands' processing threads
  Atlantis->StartEventExecution();
  Olympus->StartEventExecution();
  Rome->StartEventExecution();
  Norse->StartEventExecution();
  Perspolis->StartEventExecution();
  Memphis->StartEventExecution();
  Babylon->StartEventExecution();
  Troy->StartEventExecution();
  // Start the EldenTree's event routing thread
  Tree->StartEventRouting();
  // Start the Gods' event generation threads
  RainGod.StartEventGeneration();
  ThunderGod.StartEventGeneration();
  LightningGod.StartEventGeneration();
  WindGod.StartEventGeneration();

  // Allow some time for event generation
  std::this_thread::sleep_for(std::chrono::seconds(1));

  // Stop the Gods' event generation thread
  RainGod.StopEventGeneration();
  ThunderGod.StopEventGeneration();
  LightningGod.StopEventGeneration();
  WindGod.StopEventGeneration();
  // Stop the EldenTree's event routing thread
  Tree->StopEventRouting();
  // Stop the lands' processing threads
  Atlantis->StopEventExecution();
  Olympus->StopEventExecution();
  Rome->StopEventExecution();
  Norse->StopEventExecution();
  Perspolis->StopEventExecution();
  Memphis->StopEventExecution();
  Babylon->StopEventExecution();
  Troy->StopEventExecution();

  // Process events generated and processed and measure the time taken
  auto End = std::chrono::high_resolution_clock::now();

  // Calculate the duration
  std::chrono::duration<double> Duration = End - Start;
  size_t nProcessed =
      Atlantis->GetEventProcessed() + Olympus->GetEventProcessed() +
      Rome->GetEventProcessed() + Norse->GetEventProcessed() +
      Perspolis->GetEventProcessed() + Memphis->GetEventProcessed() +
      Babylon->GetEventProcessed() + Troy->GetEventProcessed();

  size_t nGenerated =
      RainGod.GetEventGenerated() + ThunderGod.GetEventGenerated() +
      LightningGod.GetEventGenerated() + WindGod.GetEventGenerated();

  std::cout << "Generated " << nGenerated << " and Processed " << nProcessed
            << " events in " << Duration.count() << " seconds." << std::endl;
}
