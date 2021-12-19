#ifndef MOUSE_HPP
#define MOUSE_HPP
#include <list>
#include <memory>
#include <string>

namespace Controller {
  class Mouse {
    public:
      enum class Mode { NONE, AREADEFINITION };
      Mode Mode;
      bool IsMouseLeftPressed = false;
      bool IsMouseLeftDown = false;
      bool IsMouseLeftReleased = false;
      int MouseX = 0;
      int MouseY = 0;

      void UpdateMouse();
      std::shared_ptr<std::list<std::string>> GetDebugText();
    private:
      void getMousePosition();
      void checkMouseButtonStates();
  };
}
#endif