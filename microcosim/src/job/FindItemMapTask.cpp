#include "src/job/FindItemMapTask.hpp"
#include "src/units/Units.hpp"
#include "src/inventory/Inventory.hpp" 
#include "src/threading/ThreadManager.hpp"
#include "src/item/ItemIdentifier.hpp"
#include "src/map/Map.hpp"
#include "src/game/State.hpp"
#include <memory>

namespace job {
  std::shared_ptr<job::ITask> FindItemMapTaskFactory::Create(std::shared_ptr<game::State> gameState, std::shared_ptr<Units::Unit> _unit, std::shared_ptr<Item::ItemIdentifier> _content) {
    FindItemMapTask task;
    task.Grid = gameState->Grid;
    task.Unit = _unit;
    task.Content = _content;
    task.Name = "FindItemMapTask";
    auto shared = std::make_shared<FindItemMapTask>(task);
    return shared;
  };
  void FindItemMapTask::Action() {
    IsRunning = true;
    map::Tile* res = Grid->FindNearest(Unit->currentVector.x, Unit->currentVector.y, *Content);
    if (res != NULL) {
      Unit->targetVector.x = res->positionVector.x;
      Unit->targetVector.y = res->positionVector.y;
    }
  };
  bool FindItemMapTask::CheckComplete() {
    if (!IsComplete) {
      auto TileMap = Grid->TileMap;
      bool foundGridVector = TileMap[Unit->targetVector.y][Unit->targetVector.x].InventoryContents->HasContent(*Content);
      if (foundGridVector) {
        IsComplete = true;
        IsRunning = false;
      }
    }
    return IsComplete;
  };
  bool FindItemMapTask::CheckRunning() {
    return IsRunning;
  }
}