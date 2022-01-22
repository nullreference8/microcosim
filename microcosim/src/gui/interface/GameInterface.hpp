#ifndef GUI_GAME_INTERFACE_HPP
#define GUI_GAME_INTERFACE_HPP
#include "raylib.h"
#include <memory>
#include <unordered_map>

namespace Controller {
  class Mouse;
}

namespace game {
  class State;
}

namespace map {
  class Grid;
}

namespace gui {
  enum class InterfaceName {GAME, BOTTOM, RIGHT, EDIT};
  class BottomInterface;
  class RightInterface;
  class EditInterface;
  class GameInterface{
    public:
      GameInterface(std::shared_ptr<game::State> gameState, std::shared_ptr<map::Grid> grid, int screenWidth, int screenHeight);
      std::shared_ptr<game::State> GameState;
      std::shared_ptr<map::Grid> Grid;
      int ScreenWidth = 0;
      int ScreenHeight = 0;

      std::shared_ptr<gui::BottomInterface> BottomInterface;
      std::shared_ptr<gui::RightInterface> RightInterface;
      std::shared_ptr<gui::EditInterface> EditInterface;

      void IsActiveInterfaceClicked(std::shared_ptr<Controller::Mouse> mouse);
      void Draw(std::shared_ptr<Controller::Mouse> mouse);
      void Clear();
  };
}
#endif