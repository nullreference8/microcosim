#include "src/gui/Button.hpp"
#include "src/controller/Mouse.hpp"
namespace gui {
  Button::Button(Rectangle position, std::string label, Color color) {
    Position = position;
    Label = label;
    BackgroundColor = std::shared_ptr<Color>(new Color);
    *BackgroundColor = color;

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
    DrawRectangle(Position.x, Position.y, Position.width, Position.height, *BackgroundColor);
    auto color = BLACK;
    DrawText(Label.c_str(), Position.x + 5, Position.y + 5, 10, color);
  }

  void Button::UpdatePosition(Rectangle position) {
    Position = position;
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
    if (mouse->MouseX > Position.x && mouse->MouseX < Position.x + Position.width && mouse->MouseY > Position.y && mouse->MouseY < Position.y + Position.height) {
      return true;
    }
    return false;
  }
}