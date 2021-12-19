#include "src/game/State.hpp"
#include "src/gui/EnumButton.hpp"
#include "src/gui/BottomInterface.hpp"
#include "src/controller/Mouse.hpp"
namespace gui {
  BottomInterface::BottomInterface(std::shared_ptr<game::State> gameState, int screenWidth, int screenHeight) {
    BottomInterfaceStartX = 0;
    BottomInterfaceStartY = screenHeight - 100;
    BottomInterfaceEndX = screenWidth;
    BottomInterfaceEndY = screenHeight - 100;
    GameState = gameState;

    ButtonSetModeNone = std::shared_ptr<gui::EnumButton<game::Mode>>(new gui::EnumButton<game::Mode>(
      GameState->_Mode, 
      game::Mode::NONE, 
      game::Mode::NONE, 
      BottomInterfaceStartX, 
      BottomInterfaceStartY, 
      BottomInterfaceStartX + 100, 
      BottomInterfaceStartY + 100, 
      "Exit Edit Mode", 
      LIGHTGRAY
    ));

    ButtonSetModeEdit = std::shared_ptr<gui::EnumButton<game::Mode>>(new gui::EnumButton<game::Mode>(
      GameState->_Mode, 
      game::Mode::EDIT,
      game::Mode::NONE, 
      BottomInterfaceStartX, 
      BottomInterfaceStartY, 
      BottomInterfaceStartX + 100, 
      BottomInterfaceStartY + 100, 
      "Edit Mode", 
      LIGHTGRAY
    ));

    ButtonAreaModeNew = std::shared_ptr<gui::EnumButton<game::AreaMode>>(new gui::EnumButton<game::AreaMode>(
      GameState->_AreaMode, 
      game::AreaMode::NEW, 
      game::AreaMode::SELECT, 
      BottomInterfaceStartX + 100, 
      BottomInterfaceStartY, 
      BottomInterfaceStartX + 200, 
      BottomInterfaceStartY + 100,  
      "New Area", 
      LIGHTGRAY
    ));

    ButtonAreaModeEdit = std::shared_ptr<gui::EnumButton<game::AreaMode>>(new gui::EnumButton<game::AreaMode>(
      GameState->_AreaMode, 
      game::AreaMode::EDIT, 
      game::AreaMode::SELECT, 
      BottomInterfaceStartX + 200, 
      BottomInterfaceStartY, 
      BottomInterfaceStartX + 300, 
      BottomInterfaceStartY + 100, 
      "Edit Area", 
      LIGHTGRAY
    ));

    ButtonAreaEditModeAdd = std::shared_ptr<gui::EnumButton<game::AreaEditMode>>(new gui::EnumButton<game::AreaEditMode>(
      GameState->_AreaEditMode, 
      game::AreaEditMode::ADD, 
      game::AreaEditMode::ADD, 
      BottomInterfaceStartX + 200, 
      BottomInterfaceStartY, 
      BottomInterfaceStartX + 250, 
      BottomInterfaceStartY + 50, 
      "Add", 
      LIGHTGRAY
    ));

    ButtonAreaEditModeRemove = std::shared_ptr<gui::EnumButton<game::AreaEditMode>>(new gui::EnumButton<game::AreaEditMode>(
      GameState->_AreaEditMode, 
      game::AreaEditMode::REMOVE, 
      game::AreaEditMode::ADD, 
      BottomInterfaceStartX + 250, 
      BottomInterfaceStartY, 
      BottomInterfaceStartX + 300, 
      BottomInterfaceStartY + 50, 
      "Remove", 
      LIGHTGRAY
    ));

    ButtonAreaModeEdit = std::shared_ptr<gui::EnumButton<game::AreaMode>>(new gui::EnumButton<game::AreaMode>(
      GameState->_AreaMode, 
      game::AreaMode::EDIT, 
      game::AreaMode::SELECT, 
      BottomInterfaceStartX + 200, 
      BottomInterfaceStartY + 50, 
      BottomInterfaceStartX + 300, 
      BottomInterfaceStartY + 100, 
      "Edit Area", 
      LIGHTGRAY
    ));
  }

  void BottomInterface::Draw(std::shared_ptr<Controller::Mouse> mouse) {
    if (*GameState->_Mode == game::Mode::EDIT) {
      ButtonSetModeNone->Draw(mouse);
      ButtonAreaModeNew->Draw(mouse);
      ButtonAreaEditModeAdd->Draw(mouse);
      ButtonAreaEditModeRemove->Draw(mouse);
      ButtonAreaModeEdit->Draw(mouse);
    } else if (*GameState->_Mode == game::Mode::NONE) {
      ButtonSetModeEdit->Draw(mouse);
    }
  }
}