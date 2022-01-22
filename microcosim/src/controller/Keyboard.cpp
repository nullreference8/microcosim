#include "src/controller/Keyboard.hpp"
#include "raylib.h"
namespace Controller {
  void Keyboard::Update() {
    reset();
    if (IsKeyDown(KEY_LEFT)) {
      IsCameraLeftPressed = true;
    }
    if (IsKeyDown(KEY_RIGHT)) {
      IsCameraRightPressed = true;
    }
    if (IsKeyDown(KEY_UP)) {
      IsCameraUpPressed = true;
    }
    if (IsKeyDown(KEY_DOWN)) {
      IsCameraDownPressed = true;
    }
    /*
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
    }*/
  };

  void Keyboard::reset() {
    IsCameraLeftPressed = false;
    IsCameraRightPressed = false;
    IsCameraUpPressed = false;
    IsCameraDownPressed = false;
  }
}