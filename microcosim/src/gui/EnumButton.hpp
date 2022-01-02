#ifndef GUITENUMBUTTON_HPP
#define GUIENUMBUTTON_HPP
#include "src/gui/Button.hpp"
#include "raylib.h"
#include <memory>

namespace gui {
  template <class T>
  class EnumButton : public Button {
    public:
      EnumButton(std::shared_ptr<T> enumTarget, T enumValue, T defaultValue, Rectangle position, std::string text, Color color);
      std::shared_ptr<T> EnumTarget;
      T EnumValue;
      T DefaultValue;
      void ClickAction(); 
      void HoverAction(); 
      void Draw(std::shared_ptr<Controller::Mouse> mouse);
  };
  
  template <class T>
  EnumButton<T>::EnumButton(std::shared_ptr<T> enumTarget, T enumValue, T defaultValue, Rectangle position, std::string text, Color color) 
  : Button(position, text, color) {
    EnumTarget = enumTarget;
    EnumValue = enumValue;
    DefaultValue = defaultValue;
  }

  template <class T>  
  void EnumButton<T>::ClickAction() {
    if (*EnumTarget == EnumValue) {
      *EnumTarget = DefaultValue;
    } else {
      *EnumTarget = EnumValue;
    }
  }

  template <class T>
  void EnumButton<T>::HoverAction() {
    //TODO: Visual change
  }

  template <class T>
  void EnumButton<T>::Draw(std::shared_ptr<Controller::Mouse> mouse) {
    Button::Draw(mouse);
    if (*EnumTarget == EnumValue) {
      DrawText("Active", Position.x + 5, Position.y + Position.height - 15, 10, BLACK);
    } else {
      DrawText("Inactive", Position.x + 5, Position.y + Position.height - 15, 10, BLACK);
    }
  }
}
#endif