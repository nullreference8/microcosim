#include "src/game/State.hpp"
#include "src/gui/EnumButton.hpp"
#include "src/gui/RightInterface.hpp"
#include "src/controller/Mouse.hpp"
#include "src/map/Map.hpp"
namespace gui {
  RightInterface::RightInterface(std::shared_ptr<game::State> gameState, std::shared_ptr<Map::Grid> grid, int screenWidth, int screenHeight) {
    RightInterfaceStartX = screenWidth - 300;
    RightInterfaceStartY = 0;
    RightInterfaceEndX = screenWidth;
    RightInterfaceEndY = screenHeight - 100;
    GameState = gameState;
    Grid = grid;
  }

  void RightInterface::Draw(std::shared_ptr<Controller::Mouse> mouse) {
    if (Grid->SelectedArea) {
      DrawRectangle(RightInterfaceStartX, RightInterfaceStartY, RightInterfaceEndX, RightInterfaceEndY, LIGHTGRAY);
    }
  }
}