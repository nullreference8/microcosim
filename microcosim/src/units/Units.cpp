#include "src/units/Units.hpp"
#include "src/inventory/Inventory.hpp"
#include "src/job/Jobs.hpp"
#include "src/movement/Movement.hpp"
#include "src/item/ItemIdentifier.hpp"
#include "raylib.h"
#include <memory>

namespace Units {
  Unit::Unit() {
    color = std::shared_ptr<Color>(new Color);
    currentTask = nullptr;
    *color = GRAY;
  }
  void Unit::find_path() {
    path = generator->findPath(currentVector, targetVector);
  }
  void Unit::set_next_move_time(double gameTime) {
    double secondsTilMove = 1 / travelSpeedMPS;
    nextMoveTime = gameTime + secondsTilMove;
  }
  void Unit::check_and_move(std::shared_ptr<Movement::Generator> mov, double gameTime) {
    if (gameTime > nextMoveTime){
      mov->AddUnit(this);
    }
  }
}