#include "src/controller/Mouse.hpp"
#include "raylib.h"
namespace Controller {
  void Mouse:: UpdateMouse() {
    getMousePosition();  
    checkMouseButtonStates();
  };

  void Mouse::getMousePosition() {
    MouseX = GetMouseX();
    MouseY = GetMouseY();
  };

  void Mouse::checkMouseButtonStates() {
    if (IsMouseButtonDown(0)) {
      IsMouseLeftDown = true;
    }

    if (IsMouseButtonPressed(0)) {
      IsMouseLeftPressed = true;
    } else {
      IsMouseLeftPressed = false;
    }

    if (IsMouseButtonReleased(0)) {
      IsMouseLeftDown = false;
      IsMouseLeftReleased = true;
    } else {
      IsMouseLeftReleased = false;
    }
  }

  std::shared_ptr<std::list<std::string>> Mouse::GetDebugText() {
    std::list<std::string> debugList;
    std::string xy_str = "X: " + std::to_string(MouseX) + " Y: " + std::to_string(MouseY);
    debugList.push_back(xy_str);
    std::string mouseLeftDownStr = "Mouse Left Pressed: " + std::to_string(IsMouseLeftPressed);
    debugList.push_back(mouseLeftDownStr);
    std::string mouseLeftDownHeldStr = "Mouse Left Down: " + std::to_string(IsMouseLeftDown);
    debugList.push_back(mouseLeftDownHeldStr);
    return std::make_shared<std::list<std::string>>(debugList);
  };
}
