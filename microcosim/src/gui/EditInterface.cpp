#include "src/game/State.hpp"
#include "src/gui/EnumButton.hpp"
#include "src/gui/EditInterface.hpp"
#include "src/gui/interface/GameInterface.hpp"
namespace gui {
  EditInterface::EditInterface(std::shared_ptr<game::State> gameState, int screenWidth, int screenHeight) {
    //TODO:  This interface builds backwards, upward negative direction. Change to positive.
    Position.x = 0;
    Position.height = 100;
    //Number buttons = 2
    Position.y = screenHeight - (Position.height);
    Position.width = 100;

    MouseBlockingPosition = Position;
    MouseBlockingPosition.y = Position.y - 200;
    MouseBlockingPosition.height = 200;
    GameState = gameState;

    Rectangle roomButton = Position;
    roomButton.y = roomButton.y - 100;
    ButtonRoom = std::shared_ptr<gui::EnumButton<game::AreaType>>(new gui::EnumButton<game::AreaType>(
      GameState->_AreaType, 
      game::AreaType::ROOM,
      game::AreaType::ROOM, 
      roomButton,
      "Room", 
      LIGHTGRAY
    ));

    Rectangle storageButton = Position;
    storageButton.y = storageButton.y - 200;
    ButtonStorage = std::shared_ptr<gui::EnumButton<game::AreaType>>(new gui::EnumButton<game::AreaType>(
      GameState->_AreaType, 
      game::AreaType::STORAGE,
      game::AreaType::ROOM, 
      storageButton,
      "Storage", 
      LIGHTGRAY
    ));
  }

  void EditInterface::Draw(std::shared_ptr<Controller::Mouse> mouse) {
    ButtonRoom->Draw(mouse);
    ButtonStorage->Draw(mouse);
    (*GameState->ActiveInterfaces)[gui::InterfaceName::EDIT] = MouseBlockingPosition;
  }

  void EditInterface::Clear() {
    (*GameState->ActiveInterfaces).erase(gui::InterfaceName::EDIT);
  };
}