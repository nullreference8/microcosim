#ifndef GUIBUTTON_HPP
#define GUIBUTTON_HPP

#include <string>
#include <memory>
#include "raylib.h"
struct Color;
namespace Controller {
  class Mouse;
}

namespace gui {
  class Button {
    public:
      Button(Rectangle position, std::string label, Color color);
      Rectangle Position;
      
      std::string Label;
      std::shared_ptr<Color> BackgroundColor;
      bool IsHover = false;
      bool IsClicked = false;
      void CheckHover(std::shared_ptr<Controller::Mouse> mouse);
      void CheckClicked(std::shared_ptr<Controller::Mouse> mouse);
      void UpdatePosition(Rectangle position);
      virtual void Draw(std::shared_ptr<Controller::Mouse> mouse);
      virtual void ClickAction() = 0;
      virtual void HoverAction() = 0;
    
    private:
      void initActions(std::shared_ptr<Controller::Mouse> mouse);
      bool isMouseInBounds(std::shared_ptr<Controller::Mouse> mouse);
  };
}
#endif