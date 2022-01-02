#include "src/gui/ToggleButton.hpp"
#include "raylib.h"

namespace gui {
  ToggleButton::ToggleButton(std::shared_ptr<bool> booleanTarget, Rectangle position, std::string text, Color color) 
  : Button(position, text, color) {
    BooleanTarget = booleanTarget;
  }

  void ToggleButton::ClickAction() {
    *BooleanTarget = !*BooleanTarget;
  }

  void ToggleButton::HoverAction() {
    //TODO: Visual change
  }

  void ToggleButton::Draw(std::shared_ptr<Controller::Mouse> mouse) {
    Button::Draw(mouse);
    if (*BooleanTarget) {
      DrawText("Active", Position.x + 5, Position.y + Position.height - 15, 10, BLACK);
    } else {
      DrawText("Inactive", Position.x + 5, Position.y + Position.height - 15, 10, BLACK);
    }
  }
}
