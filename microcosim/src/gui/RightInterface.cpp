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
namespace gui {
  RightInterface::RightInterface(std::shared_ptr<game::State> gameState, std::shared_ptr<Map::Grid> grid, int screenWidth, int screenHeight) {
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
      DrawRectangle(RightInterfaceStartX, RightInterfaceStartY, RightInterfaceEndX, RightInterfaceEndY, LIGHTGRAY);
      if (Grid->SelectedArea->AreaType == game::AreaType::STORAGE) {
        int yPos = RightInterfaceStartY + 10;
        int spacing = 10;
        int count = 0;
        for (auto& family : *Families) {
          DrawText(family.Family.c_str(), RightInterfaceStartX + 10, yPos + (spacing * count), 12, BLACK);
          count++;
        }
      }
    }
  }
}