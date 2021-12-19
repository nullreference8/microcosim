#include "src/job/Jobs.hpp"
#include "src/units/Units.hpp"
#include "src/inventory/Inventory.hpp" 
#include "src/threading/ThreadManager.hpp"
#include "src/item/ItemIdentifier.hpp"
#include "src/map/Map.hpp"
#include <memory>

namespace Jobs { 
  std::shared_ptr<Jobs::ITask> FindContentTaskFactory::Create(std::shared_ptr<Map::Grid> _grid, std::shared_ptr<Units::Unit> _unit, std::shared_ptr<Item::ItemIdentifier> _content) {
    FindContentTask task;
    task.Grid = _grid;
    task.Unit = _unit; 
    task.Content = _content; 
    auto shared = std::make_shared<FindContentTask>(task);
    return shared;
  }; 
  void FindContentTask::Action() {
    IsRunning = true;
    Map::Tile* res = Grid->FindNearest(Unit->currentVector.x, Unit->currentVector.y, *Content); 
    if (res != NULL) {
      Unit->targetVector.x = res->positionVector.x;
      Unit->targetVector.y = res->positionVector.y;
    }
  };
  bool FindContentTask::CheckComplete() {
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
  bool FindContentTask::CheckRunning() {
    return IsRunning;
  }
}