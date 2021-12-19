#ifndef GUITESTBUTTON_HPP
#define GUITESTBUTTON_HPP
#include "src/gui/Button.hpp"
#include "raylib.h"
#include <memory>

namespace gui {
  class ToggleButton : public Button {
    public:
      std::shared_ptr<bool> BooleanTarget;
      ToggleButton(std::shared_ptr<bool> booleanTarget, int startX, int startY, int endX, int endY, std::string text, Color color);
      void ClickAction(); 
      void HoverAction(); 
      void Draw(std::shared_ptr<Controller::Mouse> mouse);
  };
}
#endif