#include "src/crafting/Recipe.hpp"
#include "src/area/Workshop.hpp"
#include "src/item/ItemIdentifier.hpp"
#include "src/game/State.hpp"
namespace crafting {
  /*Recipe::Recipe(std::unordered_map<std::string, int> inputItems, std::unordered_map<std::string, int> outputItems, int totalProcessingTime) {
    InputItems = inputItems;
    OutputItems = outputItems;
    TotalProcessingTime = totalProcessingTime;
  }*/

  void Recipe::StartProcessing(std::shared_ptr<game::State> state) {
    StartTime = (int)state->GameTime;
  };

  bool Recipe::IsStarted() {
    if (StartTime > 0) {
      return true;
    }
    return false;
  }
  
  bool Recipe::CheckComplete(std::shared_ptr<game::State> state) {
    if (StartTime + TotalProcessingTime <= (int)state->GameTime) {
      IsComplete = true;
      return true;
    }
    return false;
  }

  std::unordered_map<std::string, int> Recipe::ClaimItems() {
    if (IsComplete) {
      return OutputItems;
    }
  }
}