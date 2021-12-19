#include "src/gui/ToggleButton.hpp"
#include "raylib.h"

namespace gui {
  ToggleButton::ToggleButton(std::shared_ptr<bool> booleanTarget, int startX, int startY, int endX, int endY, std::string text, Color color) 
  : Button(startX, startY, endX, endY, text, color) {
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
      DrawText("Active", StartX + 5, EndY - 15, 10, BLACK);
    } else {
      DrawText("Inactive", StartX + 5, EndY - 15, 10, BLACK);
    }
  }
}
