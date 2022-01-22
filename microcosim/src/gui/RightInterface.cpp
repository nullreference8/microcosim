#include "src/game/State.hpp"
#include "src/gui/EnumButton.hpp"
#include "src/gui/RightInterface.hpp"
#include "src/controller/Mouse.hpp"
#include "src/map/Map.hpp"
#include "src/area/Area.hpp"
#include "src/area/Storage.hpp"
#include "src/game/State.hpp"
#include "src/item/Repository.hpp"
#include "src/item/ItemIdentifier.hpp"
#include "src/item/Item.hpp"
#include "src/gui/interface/GameInterface.hpp"
#include "src/gui/StorageFilterButton.hpp"
namespace gui {
  RightInterface::RightInterface(std::shared_ptr<game::State> gameState, std::shared_ptr<map::Grid> grid, int screenWidth, int screenHeight) {
    Position.width = 300;
    Position.x = screenWidth - Position.width;
    Position.y = 0;
    Position.height = screenHeight - 100;

    RightInterfaceStartX = screenWidth - 300;
    RightInterfaceStartY = 0;
    RightInterfaceEndX = screenWidth;
    RightInterfaceEndY = screenHeight - 100;

    GameState = gameState;
    Grid = grid;
    ItemRepo = std::shared_ptr<Item::Repository>(new Item::Repository(GameState));
    Families = ItemRepo->SelectFamilies();
    
  }

  void RightInterface::Draw(std::shared_ptr<Controller::Mouse> mouse) {
    if (Grid->SelectedArea) {
      (*GameState->ActiveInterfaces)[gui::InterfaceName::RIGHT] = Position;
      DrawRectangle(RightInterfaceStartX, RightInterfaceStartY, RightInterfaceEndX, RightInterfaceEndY, LIGHTGRAY);
      if (Grid->SelectedArea->AreaType == game::AreaType::STORAGE) {
        int yPos = Position.y + 10;
        int spacing = 10;
        int count = 0;
        for (auto& family : *Families) {
          auto strg = std::dynamic_pointer_cast<area::Storage>(Grid->SelectedArea);
          Rectangle storageFilterButtonPosition = Position;
          storageFilterButtonPosition.x = storageFilterButtonPosition.x + 10;
          storageFilterButtonPosition.y = yPos + (spacing * count);
          storageFilterButtonPosition.height = 100;
          auto btn = gui::StorageFilterButton(strg, family, Item::MatchDegree::FAMILY, storageFilterButtonPosition, family.Family, LIGHTGRAY);
          btn.Draw(mouse);
          count++;
        }
      }
    }
  }

  void RightInterface::Clear() {
    (*GameState->ActiveInterfaces).erase(gui::InterfaceName::RIGHT);
  };
}