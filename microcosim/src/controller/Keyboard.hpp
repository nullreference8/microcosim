#ifndef KEYBOARD_HPP
#define KEYBOARD_HPP

namespace Controller {
  class Keyboard {
    public:
      bool IsCameraLeftPressed = false;
      bool IsCameraRightPressed = false; 
      bool IsCameraUpPressed = false;
      bool IsCameraDownPressed = false;

      void Update();
    
    private:
      void reset();
  };
}
#endif