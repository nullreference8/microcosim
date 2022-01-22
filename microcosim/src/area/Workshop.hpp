#ifndef AREA_WORKSHOP_HPP
#define AREA_WORKSHOP_HPP
#include "src/area/Area.hpp"
#include <memory>
#include <unordered_map>
#include <vector>

namespace Item {
  enum class ItemDegree;
  class ItemIdentifier;
}

namespace crafting {
  class Recipe;
}

namespace Units {
  class Unit;
}

namespace area {
  class Storage;
  class Workshop : public BaseArea {
    public:
      std::vector<std::shared_ptr<crafting::Recipe>> Recipes;
      void AddRecipe(std::shared_ptr<crafting::Recipe> recipe);
      void RemoveRecipe(std::shared_ptr<crafting::Recipe> recipe);
      void ScanForRecipeTools();
      void ScanForRecipeItems();
      void Update();
      std::vector<std::shared_ptr<crafting::Recipe>>::iterator FindRecipeByID(int ID);
      std::shared_ptr<area::Storage> LinkedStorage;
  };
  class ToolRegistry {
    std::shared_ptr<map::Tile> CurrentLocation;
    //std::shared_ptr<Item::Tool> Tool;
    std::shared_ptr<Units::Unit> HeldBy;
  };
}
#endif