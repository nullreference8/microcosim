#include "src/controller/Keyboard.hpp"
#include "raylib.h"
namespace Controller {
  void Keyboard::Update() {
    reset();
    int res = GetKeyPressed();
    while (res != 0) {
      if (res == KEY_LEFT) {
        IsCameraLeftPressed = true;
      } else if (res == KEY_RIGHT) {
        IsCameraRightPressed = true;
      } else if (res == KEY_UP) {
        IsCameraUpPressed = true;
      } else if (res == KEY_DOWN) {
        IsCameraDownPressed = true;
      }

      res = GetKeyPressed();
    }
  };

  void Keyboard::reset() {
    IsCameraLeftPressed = false;
    IsCameraRightPressed = false;
    IsCameraUpPressed = false;
    IsCameraDownPressed = false;
  }
}