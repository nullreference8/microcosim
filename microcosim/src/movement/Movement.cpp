#include <vector>
#include "src/movement/Movement.hpp"
#include "src/units/Units.hpp" 

namespace Movement {
  void Movement::Generator::AddUnit(Units::Unit* unit) {
    auto pathsize = unit->path.size();
    if (!(unit->currentVector.x == unit->targetVector.x && unit->currentVector.y == unit->targetVector.y) && pathsize > 0) {
      unitsToUpdate.push_back(unit);
    }
  }

  void Movement::Generator::MoveAllAndClear(double gameTime) {
    for(auto unit : unitsToUpdate) {
      int nextPathIndex = unit->currentPathIndex + 1;
      unit->currentVector = unit->path[nextPathIndex];
      unit->currentPathIndex = nextPathIndex;
      unit->ClearPath();
      unit->set_next_move_time(gameTime);
    }
    unitsToUpdate.clear();
  }
}