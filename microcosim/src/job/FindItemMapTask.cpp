#include "src/job/FindItemMapTask.hpp"
#include "src/units/Units.hpp"
#include "src/inventory/Inventory.hpp" 
#include "src/threading/ThreadManager.hpp"
#include "src/item/ItemIdentifier.hpp"
#include "src/map/Map.hpp"
#include <memory>

namespace job {
  std::shared_ptr<job::ITask> FindItemMapTaskFactory::Create(std::shared_ptr<Map::Grid> _grid, std::shared_ptr<Units::Unit> _unit, std::shared_ptr<Item::ItemIdentifier> _content) {
    FindItemMapTask task;
    task.Grid = _grid;
    task.Unit = _unit;
    task.Content = _content;
    task.Name = "FindItemMapTask";
    auto shared = std::make_shared<FindItemMapTask>(task);
    return shared;
  };
  void FindItemMapTask::Action() {
    IsRunning = true;
    Map::Tile* res = Grid->FindNearest(Unit->currentVector.x, Unit->currentVector.y, *Content);
    if (res != NULL) {
      Unit->targetVector.x = res->positionVector.x;
      Unit->targetVector.y = res->positionVector.y;
    }
  };
  bool FindItemMapTask::CheckComplete() {
    if (!IsComplete) {
      auto tileMap = Grid->tileMap;
      bool foundGridVector = tileMap[Unit->targetVector.y][Unit->targetVector.x].InventoryContents->HasContent(*Content);
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