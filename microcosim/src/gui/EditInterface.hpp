#ifndef GUIEDITINTERFACE_HPP
#define GUIEDITINTERFACE_HPP
#include <memory>
#include <list>

namespace game {
  enum class AreaType;
  class State;
}

namespace gui {
  template<class T>
  class EnumButton;
  
  class EditInterface{
    public:
      EditInterface(std::shared_ptr<game::State> gameState, int screenWidth, int screenHeight);

      int EditInterfaceStartX;
      int EditInterfaceStartY;
      int EditInterfaceEndX;
      int EditInterfaceEndY;

      std::shared_ptr<game::State> GameState;

      std::shared_ptr<gui::EnumButton<game::AreaType>> ButtonRoom;
      std::shared_ptr<gui::EnumButton<game::AreaType>> ButtonStorage;

      void Draw(std::shared_ptr<Controller::Mouse> mouse);
  };
}
#endif