#include "src/game/State.hpp"
#include "src/gui/interface/GameInterface.hpp"
#include "src/gui/BottomInterface.hpp"
#include "src/gui/RightInterface.hpp"
#include "src/gui/EditInterface.hpp"
#include "src/map/Map.hpp"
#include "src/controller/Mouse.hpp"
namespace gui {
  GameInterface::GameInterface(std::shared_ptr<game::State> gameState, std::shared_ptr<map::Grid> grid, int screenWidth, int screenHeight) {
    GameState = gameState;
    Grid = grid;
    ScreenWidth = screenWidth;
    ScreenHeight = screenHeight;

    BottomInterface = std::shared_ptr<gui::BottomInterface>(new gui::BottomInterface(GameState, screenWidth, screenHeight));
    RightInterface = std::shared_ptr<gui::RightInterface>(new gui::RightInterface(GameState, Grid, screenWidth, screenHeight));
    EditInterface = std::shared_ptr<gui::EditInterface>(new gui::EditInterface(GameState, screenWidth, screenHeight));
  }

  void GameInterface::Draw(std::shared_ptr<Controller::Mouse> mouse) {
    BottomInterface->Draw(mouse);
    RightInterface->Draw(mouse);
    if (*GameState->_Mode == game::Mode::EDIT) {
      EditInterface->Draw(mouse);
    }
  }

  void GameInterface::Clear() {
    BottomInterface->Clear();
    RightInterface->Clear();
    EditInterface->Clear();
  }
}