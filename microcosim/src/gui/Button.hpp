#ifndef GUIBUTTON_HPP
#define GUIBUTTON_HPP

#include <string>
#include <memory>
struct Color;
namespace Controller {
  class Mouse;
}

namespace gui {
  class Button {
    public:
      Button(int startX, int startY, int endX, int endY, std::string label, Color color);
      int StartX = 0;
      int StartY = 0;
      int EndX = 0;
      int EndY = 0;
      int Width = 0;
      int Height = 0;
      int WidthCenter = 0;
      int HeightCenter = 0;
      std::string Label;
      std::shared_ptr<Color> BackgroundColor;
      bool IsHover = false;
      bool IsClicked = false;
      void CheckHover(std::shared_ptr<Controller::Mouse> mouse);
      void CheckClicked(std::shared_ptr<Controller::Mouse> mouse);
      void UpdatePosition(int startX, int startY, int endX, int endY);
      virtual void Draw(std::shared_ptr<Controller::Mouse> mouse);
      virtual void ClickAction() = 0;
      virtual void HoverAction() = 0;
    
    private:
      void initActions(std::shared_ptr<Controller::Mouse> mouse);
      bool isMouseInBounds(std::shared_ptr<Controller::Mouse> mouse);
  };
}
#endif