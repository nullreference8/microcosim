#include "src/gui/TriButton.hpp"
#include "src/controller/Mouse.hpp"
#include "raylib.h"
#include <memory>

namespace gui {
  TriButton::TriButton(std::shared_ptr<int> intTarget, int startX, int startY, int endX, int endY, std::string text, Color color)
  : Button(startX + 20, startY, endX, endY, text, color) {
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
      DrawRectangle(StartX, StartY, StartX + 10, StartY + 10, WHITE);
    }
    else if (*IntTarget == 1) {
      DrawRectangle(StartX, StartY, StartX + 10, StartY + 10, GREEN);
    }
    else if (*IntTarget == 2) {
      DrawRectangle(StartX, StartY, StartX + 10, StartY + 10, ORANGE);
    }
  };
}