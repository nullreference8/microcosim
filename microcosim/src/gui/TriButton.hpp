#ifndef GUI_TRIBUTTON_HPP
#define GUI_TRIBUTTON_HPP

#include "src/gui/Button.hpp"
#include <string>
#include <memory>

namespace Controller {
  class Mouse;
}

namespace gui {
  class TriButton : public Button {
    public:
      TriButton(std::shared_ptr<int> intTarget, int startX, int startY, int endX, int endY, std::string text, Color color);
      std::shared_ptr<int> IntTarget;
      void ClickAction();
      void HoverAction();
      void Draw(std::shared_ptr<Controller::Mouse> mouse);
  };
}
#endif