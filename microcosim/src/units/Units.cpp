#include "src/units/Units.hpp"
#include "src/inventory/Inventory.hpp"
#include "src/job/AreaDropItemJobFactory.hpp"
#include "src/job/Jobs.hpp"
#include "src/movement/Movement.hpp"
#include "src/item/ItemIdentifier.hpp"
#include "src/game/State.hpp"
#include "src/map/Map.hpp"
#include "src/area/Area.hpp"
#include "src/area/Storage.hpp"
#include "raylib.h"
#include <memory>

namespace Units {
  Unit::Unit() {
    color = std::shared_ptr<Color>(new Color);
    Responsibilities.push_back(Units::Responsibility::CHOP);
    Responsibilities.push_back(Units::Responsibility::HAUL);
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

  void Unit::ClearPath() {
    if (currentVector == targetVector) {
      path = AStar::CoordinateList{};
      currentPathIndex = 0;
    }
  }

  void Unit::CheckDropItem(std::shared_ptr<game::State> gameState) {
    /*for (auto& content : *inventory->Contents) {
      for (auto& area : *gameState->Grid->Areas) {
        if (area->AreaType == game::AreaType::STORAGE) {
          auto storage = std::dynamic_pointer_cast<area::Storage>(area);
          auto itemIdentifier = content.second.front();
          if (!itemIdentifier->MarkedForDrop && storage->AcceptsItem(*itemIdentifier)) {
            job::AreaDropItemJobFactory afact;
            auto unitPtr = std::make_shared<Units::Unit>(this);
            auto job = afact.Create(gameState, storage, unitPtr, itemIdentifier);
            this->jobs.push_back(job);
            itemIdentifier->MarkedForDrop = true;
          }
        }
      }
    }*/
  }
}