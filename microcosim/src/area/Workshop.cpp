#include "src/area/Workshop.hpp"
#include "src/crafting/Recipe.hpp"
#include <memory>
#include <algorithm>

namespace area {
  void Workshop::AddRecipe(std::shared_ptr<crafting::Recipe> recipe) {
    auto it = FindRecipeByID(recipe->ID);
    if (it != Recipes.end()) {
      Recipes.push_back(recipe);
    }
  }

  void Workshop::RemoveRecipe(std::shared_ptr<crafting::Recipe> recipe) {
    auto it = FindRecipeByID(recipe->ID);
    if (it != Recipes.end()) {
      Recipes.erase(it);
    }
  }

  std::vector<std::shared_ptr<crafting::Recipe>>::iterator Workshop::FindRecipeByID(int ID) {
    auto it = std::find_if(Recipes.begin(), Recipes.end(), [&ID](std::shared_ptr<crafting::Recipe> obj) {return obj->ID == ID;});
    return it;
  }
}