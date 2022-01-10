#include "src/game/State.hpp"
#include "src/gui/EnumButton.hpp"
#include "src/gui/BottomInterface.hpp"
#include "src/gui/interface/GameInterface.hpp"
#include "src/controller/Mouse.hpp"
namespace gui {
  BottomInterface::BottomInterface(std::shared_ptr<game::State> gameState, int screenWidth, int screenHeight) {
    Position = Rectangle{};
    Position.width = 100;
    Position.height = 100;
    Position.x = 0;
    Position.y = screenHeight - Position.height;
    GameState = gameState;
    MouseBlockingPosition = Position;
    MouseBlockingPosition.width = 450;

    Rectangle noneButtonPosition = Position;
    ButtonSetModeNone = std::shared_ptr<gui::EnumButton<game::Mode>>(new gui::EnumButton<game::Mode>(
      GameState->_Mode, 
      game::Mode::NONE, 
      game::Mode::NONE, 
      noneButtonPosition,
      "Exit Edit Mode", 
      LIGHTGRAY
    ));

    Rectangle setModeButtonPosition = Position;
    ButtonSetModeEdit = std::shared_ptr<gui::EnumButton<game::Mode>>(new gui::EnumButton<game::Mode>(
      GameState->_Mode, 
      game::Mode::EDIT,
      game::Mode::NONE, 
      setModeButtonPosition,
      "Edit Mode", 
      LIGHTGRAY
    ));

    Rectangle setModeButtonDesignationPosition = Position;
    setModeButtonDesignationPosition.x = setModeButtonDesignationPosition.x + 100;
    ButtonSetModeDesignation = std::shared_ptr<gui::EnumButton<game::Mode>>(new gui::EnumButton<game::Mode>(
      GameState->_Mode,
      game::Mode::DESIGNATION,
      game::Mode::NONE,
      setModeButtonDesignationPosition,
      "Designation Mode",
      LIGHTGRAY
    ));

    Rectangle areaModeButton = Position;
    areaModeButton.x = areaModeButton.x + 100;
    ButtonAreaModeNew = std::shared_ptr<gui::EnumButton<game::AreaMode>>(new gui::EnumButton<game::AreaMode>(
      GameState->_AreaMode, 
      game::AreaMode::NEW, 
      game::AreaMode::SELECT, 
      areaModeButton,
      "New Area", 
      LIGHTGRAY
    ));

    Rectangle areaModeEditButton = Position;
    areaModeEditButton.x = areaModeEditButton.x + 200;
    ButtonAreaModeEdit = std::shared_ptr<gui::EnumButton<game::AreaMode>>(new gui::EnumButton<game::AreaMode>(
      GameState->_AreaMode, 
      game::AreaMode::EDIT, 
      game::AreaMode::SELECT, 
      areaModeEditButton,
      "Edit Area", 
      LIGHTGRAY
    ));

    Rectangle areaModeAddButton = Position;
    areaModeAddButton.x = areaModeAddButton.x + 300;
    areaModeAddButton.height = 50;
    areaModeAddButton.width = 50;
    ButtonAreaEditModeAdd = std::shared_ptr<gui::EnumButton<game::AreaEditMode>>(new gui::EnumButton<game::AreaEditMode>(
      GameState->_AreaEditMode, 
      game::AreaEditMode::ADD, 
      game::AreaEditMode::ADD, 
      areaModeAddButton,
      "Add", 
      LIGHTGRAY
    ));

    Rectangle areaEditModeRemoveButton = Position;
    areaEditModeRemoveButton.x = areaEditModeRemoveButton.x + 350;
    areaEditModeRemoveButton.height = 50;
    areaEditModeRemoveButton.width = 50;
    ButtonAreaEditModeRemove = std::shared_ptr<gui::EnumButton<game::AreaEditMode>>(new gui::EnumButton<game::AreaEditMode>(
      GameState->_AreaEditMode, 
      game::AreaEditMode::REMOVE, 
      game::AreaEditMode::ADD, 
      areaEditModeRemoveButton,
      "Remove", 
      LIGHTGRAY
    ));

    /*Rectangle areaModeEditButton = Position;
    areaModeEditButton.x = areaModeEditButton.x + 200;
    areaModeEditButton.y = areaModeEditButton.y + 50;
    areaModeEditButton.height = 50;
    ButtonAreaModeEdit = std::shared_ptr<gui::EnumButton<game::AreaMode>>(new gui::EnumButton<game::AreaMode>(
      GameState->_AreaMode, 
      game::AreaMode::EDIT, 
      game::AreaMode::SELECT, 
      areaModeEditButton,
      "Edit Area", 
      LIGHTGRAY
    ));*/
  }

  void BottomInterface::Draw(std::shared_ptr<Controller::Mouse> mouse) {
    if (*GameState->_Mode == game::Mode::EDIT) {
      ButtonSetModeNone->Draw(mouse);
      ButtonAreaModeNew->Draw(mouse);
      ButtonAreaEditModeAdd->Draw(mouse);
      ButtonAreaEditModeRemove->Draw(mouse);
      ButtonAreaModeEdit->Draw(mouse);
    } else if (*GameState->_Mode == game::Mode::NONE || *GameState->_Mode == game::Mode::DESIGNATION) {
      ButtonSetModeEdit->Draw(mouse);
      ButtonSetModeDesignation->Draw(mouse);
    }

    (*GameState->ActiveInterfaces)[gui::InterfaceName::BOTTOM] = MouseBlockingPosition;
  }

  void BottomInterface::Clear() {
    (*GameState->ActiveInterfaces).erase(gui::InterfaceName::BOTTOM);
  };
}