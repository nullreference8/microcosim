#include "src/game/State.hpp"
#include "src/gui/EnumButton.hpp"
#include "src/gui/EditInterface.hpp"
namespace gui {
  EditInterface::EditInterface(std::shared_ptr<game::State> gameState, int screenWidth, int screenHeight) {
    EditInterfaceStartX = 0;
    EditInterfaceStartY = screenHeight - 100;
    EditInterfaceEndX = 100;
    EditInterfaceEndY = 0;
    GameState = gameState;

    ButtonRoom = std::shared_ptr<gui::EnumButton<game::AreaType>>(new gui::EnumButton<game::AreaType>(
      GameState->_AreaType, 
      game::AreaType::ROOM,
      game::AreaType::ROOM, 
      EditInterfaceStartX, 
      EditInterfaceStartY - 100, 
      EditInterfaceEndX, 
      EditInterfaceStartY, 
      "Room", 
      LIGHTGRAY
    ));

    ButtonStorage = std::shared_ptr<gui::EnumButton<game::AreaType>>(new gui::EnumButton<game::AreaType>(
      GameState->_AreaType, 
      game::AreaType::STORAGE,
      game::AreaType::ROOM, 
      EditInterfaceStartX, 
      EditInterfaceStartY - 200, 
      EditInterfaceEndX, 
      EditInterfaceStartY - 100, 
      "Storage", 
      LIGHTGRAY
    ));
  }

  void EditInterface::Draw(std::shared_ptr<Controller::Mouse> mouse) {
    ButtonRoom->Draw(mouse);
    ButtonStorage->Draw(mouse);
  }
}