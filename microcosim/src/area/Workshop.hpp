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

namespace area {
  class Storage;
  class Workshop : public BaseArea {
    public:
      std::vector<std::shared_ptr<crafting::Recipe>> Recipes;
      void AddRecipe(std::shared_ptr<crafting::Recipe> recipe);
      void RemoveRecipe(std::shared_ptr<crafting::Recipe> recipe);
      std::vector<std::shared_ptr<crafting::Recipe>>::iterator FindRecipeByID(int ID);
      std::shared_ptr<area::Storage> LinkedStorage;
  };
}
#endif