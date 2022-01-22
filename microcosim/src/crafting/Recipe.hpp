#ifndef CRAFTING_RECIPE_HPP
#define CRAFTING_RECIPE_HPP
#include <memory>
#include <string>
#include <unordered_map>

namespace Item {
  class ItemIdentifier;
  class Tool;
}

namespace area {
  class Workshop;
}

namespace game {
  class State;
}

namespace map {
  class Tile;
}

namespace crafting {
  

  class Recipe {
    public:
      Recipe(std::unordered_map<std::string, int> inputItems, std::unordered_map<std::string, int> outputItems, int totalProcessingTime);
      
      //Key is ItemIdentifierHash
      //std::unordered_map<std::string, ToolRegistry> RequiredTools;
      
      //Key is ItemIdentifierHash
      std::unordered_map<std::string, int> InputItems;
      
      //Key is ItemIdentifierHash
      std::unordered_map<std::string, int> OutputItems;
      int TotalProcessingTime;
      int StartTime = 0;
      int ID = 0;
      int IsComplete = false;

      void StartProcessing(std::shared_ptr<game::State> state);
      bool CheckComplete(std::shared_ptr<game::State> state);
      std::unordered_map<std::string, int> Recipe::ClaimItems();
      bool IsStarted();
  };
}
#endif