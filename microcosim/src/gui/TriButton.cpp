#include "src/gui/TriButton.hpp"
#include "src/controller/Mouse.hpp"
#include "raylib.h"
#include <memory>

namespace gui {
  TriButton::TriButton(std::shared_ptr<int> intTarget, Rectangle position, std::string text, Color color)
  : Button(position, text, color) {
    IntTarget = intTarget;
  };
  void TriButton::ClickAction() {
    if (*IntTarget == 0){
      *IntTarget = 1;
    } else if (*IntTarget == 1) {
      *IntTarget = 0;
    } else if (*IntTarget == 2) {
      *IntTarget = 0;
    }
  };
  void TriButton::HoverAction() {

  };
  void TriButton::Draw(std::shared_ptr<Controller::Mouse> mouse) {
    Button::Draw(mouse);
    if (*IntTarget == 0) {
      DrawRectangle(Position.x, Position.y, Position.x + 10, Position.y + 10, WHITE);
    }
    else if (*IntTarget == 1) {
      DrawRectangle(Position.x, Position.y, Position.x + 10, Position.y + 10, GREEN);
    }
    else if (*IntTarget == 2) {
      DrawRectangle(Position.x, Position.y, Position.x + 10, Position.y + 10, ORANGE);
    }
  };
}