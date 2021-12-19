#ifndef CAMERA_HPP
#define CAMERA_HPP
#include <memory>

struct Camera2D;
namespace game {
  class Camera {
    public:
      Camera();
      std::shared_ptr<Camera2D> GameCamera;
      void MoveLeft(int distance);
      void MoveRight(int distance);
      void MoveUp(int distance);
      void MoveDown(int distance);
  };
}
#endif