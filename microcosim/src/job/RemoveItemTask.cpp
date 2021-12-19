#include "src/job/Jobs.hpp"
#include "src/units/Units.hpp"
#include "src/inventory/Inventory.hpp" 
#include "src/threading/ThreadManager.hpp"
#include "src/item/ItemIdentifier.hpp"
#include "src/map/Map.hpp"
#include "src/item/Item.hpp"
#include <memory>

namespace Jobs { 
  std::shared_ptr<Jobs::ITask> RemoveItemTaskFactory::Create(std::shared_ptr<Map::Grid> _grid, std::shared_ptr<Units::Unit> _unit, std::shared_ptr<Item::ItemIdentifier> _identifier, std::shared_ptr<Item::MatchDegree> _degree) {
    RemoveItemTask task;
    task.Grid = _grid;
    task.Unit = _unit; 
    task.Identifier = _identifier; 
    task.Degree = _degree;
    auto shared = std::make_shared<RemoveItemTask>(task);
    return shared;;
  }; 
  void RemoveItemTask::Action() {
    IsRunning = true;
  };
  bool RemoveItemTask::CheckComplete() {
    if (!IsComplete) {
      if (Unit->currentVector.x == Unit->targetVector.x && Unit->currentVector.y == Unit->targetVector.y) {
        std::shared_ptr<Item::BaseItem> item = Grid->tileMap[Unit->currentVector.y][Unit->currentVector.x].InventoryContents->RemoveItem(*Identifier, *Degree);
        //std::shared_ptr<Item::Tree> treePtr = std::dynamic_pointer_cast<Item::Tree>(item);
        if (item) {
          Unit->inventory->AddItem(item);
          IsComplete = true;
          IsRunning = false;
        }
      }
    }
    return IsComplete;
  };
  bool RemoveItemTask::CheckRunning() {
    return IsRunning;
  }
}