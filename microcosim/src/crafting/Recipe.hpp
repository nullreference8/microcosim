#ifndef CRAFTING_RECIPE_HPP
#define CRAFTING_RECIPE_HPP
#include <memory>
#include <unordered_map>

namespace Item {
  class ItemIdentifier;
}

namespace area {
  class Workshop;
}

namespace game {
  class State;
}

namespace crafting {
  class Recipe {
    public:
      Recipe(std::unordered_map<std::shared_ptr<Item::ItemIdentifier>, int> inputItems, std::unordered_map<std::shared_ptr<Item::ItemIdentifier>, int> outputItems, int totalProcessingTime);
      std::unordered_map<std::shared_ptr<Item::ItemIdentifier>, int> InputItems;
      std::unordered_map<std::shared_ptr<Item::ItemIdentifier>, int> OutputItems;
      int TotalProcessingTime;
      int StartTime = 0;
      int ID = 0;

      void StartProcessing(std::shared_ptr<game::State> state);
      bool CheckComplete(std::shared_ptr<game::State> state);
      bool IsStarted();
  };
}
#endif