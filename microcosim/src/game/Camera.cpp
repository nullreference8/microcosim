#include "src/game/Camera.hpp"
#include "raylib.h"
namespace game {
  Camera::Camera() {
    GameCamera = std::shared_ptr<Camera2D>(new Camera2D);
    GameCamera->target.x = 1;
    GameCamera->target.y = 1;
    GameCamera->zoom = 1.0f;
  }

  void Camera::MoveLeft(int distance) {
    GameCamera->target.x = GameCamera->target.x - distance;
    if (GameCamera->target.x < 0){
      GameCamera->target.x = 0;
    }
  }

  void Camera::MoveRight(int distance) {
    GameCamera->target.x = GameCamera->target.x + distance;
    if (GameCamera->target.x > GetScreenWidth()) {
      GameCamera->target.x = GetScreenWidth();
    }
  }

  void Camera::MoveUp(int distance) {
    GameCamera->target.y = GameCamera->target.y - distance;
    if (GameCamera->target.y < 0) {
      GameCamera->target.y = 0;
    }
  }

  void Camera::MoveDown(int distance) {
    GameCamera->target.y = GameCamera->target.y + distance;
    if (GameCamera->target.y > GetScreenHeight()) {
      GameCamera->target.y = GetScreenHeight();
    }
  }
}
