#include "src/gui/Button.hpp"
#include "src/controller/Mouse.hpp"
#include "raylib.h"
namespace gui {
  Button::Button(int startX, int startY, int endX, int endY, std::string label, Color color) {
    StartX = startX;
    StartY = startY;
    EndX = endX;
    EndY = endY;
    Label = label;
    BackgroundColor = std::shared_ptr<Color>(new Color);
    *BackgroundColor = color;
    Width = EndX - StartX;
    Height = EndY - StartY;
    WidthCenter = startX + (Width / 2);
    HeightCenter = startY + (Height / 2);
  }

  void Button::CheckClicked(std::shared_ptr<Controller::Mouse> mouse) {
    if (mouse->IsMouseLeftPressed) {
      if (Button::isMouseInBounds(mouse)) {
        IsClicked = true;
      }
    } else {
      IsClicked = false;
    }
  }

  void Button::CheckHover(std::shared_ptr<Controller::Mouse> mouse) {
    if (Button::isMouseInBounds(mouse)) {
      IsHover = true;
    } else {
      IsHover = false;
    }
  }

  void Button::Draw(std::shared_ptr<Controller::Mouse> mouse) {
    initActions(mouse);
    DrawRectangle(StartX, StartY, Width, Height, *BackgroundColor);
    auto color = BLACK;
    DrawText(Label.c_str(), StartX + 5, StartY + 5, 10, color);
  }

  void Button::UpdatePosition(int startX, int startY, int endX, int endY) {
    StartX = startX;
    StartY = startY;
    EndX = endX;
    EndY = endY;
  }

  void Button::initActions(std::shared_ptr<Controller::Mouse> mouse) {
    CheckHover(mouse);
    CheckClicked(mouse);
    if (IsHover) {
      HoverAction();
    }
    if (IsClicked) {
      ClickAction();
    }
  }

  bool Button::isMouseInBounds(std::shared_ptr<Controller::Mouse> mouse) {
    if (mouse->MouseX > StartX && mouse->MouseX < EndX && mouse->MouseY > StartY && mouse->MouseY < EndY) {
      return true;
    }
    return false;
  }
}