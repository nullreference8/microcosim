#ifndef GUIBOTTOMINTERFACE_HPP
#define GUIBOTTOMINTERFACE_HPP
#include <memory>
#include <unordered_map>

namespace game {
  enum class Mode;
  enum class AreaMode;
  enum class AreaEditMode;
  class State;
}

namespace Controller {
  class Mouse;
}

namespace gui {
  template<class T>
  class EnumButton;
  enum class InterfaceName;
  class BottomInterface{
    public:
      BottomInterface(std::shared_ptr<game::State> gameState, int screenWidth, int screenHeight);

      Rectangle Position;
      Rectangle MouseBlockingPosition;

      std::shared_ptr<game::State> GameState;

      std::shared_ptr<gui::EnumButton<game::Mode>> ButtonSetModeNone;
      std::shared_ptr<gui::EnumButton<game::Mode>> ButtonSetModeEdit;
      std::shared_ptr<gui::EnumButton<game::Mode>> ButtonSetModeDesignation;

      //Area Edit Mode Buttons
      std::shared_ptr<gui::EnumButton<game::AreaMode>> ButtonAreaModeNew;
      std::shared_ptr<gui::EnumButton<game::AreaMode>> ButtonAreaModeEdit;

      std::shared_ptr<gui::EnumButton<game::AreaEditMode>> ButtonAreaEditModeAdd;
      std::shared_ptr<gui::EnumButton<game::AreaEditMode>> ButtonAreaEditModeRemove;

      void Draw(std::shared_ptr<Controller::Mouse> mouse);
      void Clear();
  };
}
#endif