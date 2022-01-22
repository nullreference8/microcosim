#include "src/job/DropItemTask.hpp"
#include "src/units/Units.hpp"
#include "src/inventory/Inventory.hpp" 
#include "src/threading/ThreadManager.hpp"
#include "src/item/ItemIdentifier.hpp"
#include "src/map/Map.hpp"
#include "src/game/State.hpp"
#include "src/item/Item.hpp"
#include <memory> 

namespace job {
  std::shared_ptr<job::ITask> DropItemTaskFactory::Create(std::shared_ptr<game::State> gameState, std::shared_ptr<Units::Unit> _unit, std::shared_ptr<Item::ItemIdentifier> _identifier) {
    DropItemTask task;
    task.Grid = gameState->Grid;
    task.Unit = _unit;
    task.Identifier = _identifier;
    task.Degree = std::make_shared<Item::MatchDegree>(Item::MatchDegree::EXACT);
    auto shared = std::make_shared<DropItemTask>(task);
    return shared;;
  };
  void DropItemTask::Action() {
    IsRunning = true;
  };
  bool DropItemTask::CheckComplete() {
    if (!IsComplete) {
      if (Unit->currentVector == Unit->targetVector) {
        //std::shared_ptr<Item::Tree> treePtr = std::dynamic_pointer_cast<Item::Tree>(item);
        for (auto& item : *Unit->inventory->Items) {
          if (item->Match(*Identifier, *Degree)) {
            auto removed = Unit->inventory->RemoveItem(*Identifier, *Degree);
            Grid->TileMap[Unit->currentVector.y][Unit->currentVector.x].InventoryContents->AddItem(removed);
            IsComplete = true;
            IsRunning = false;
          }
        }
      }
    }
    return IsComplete;
  };
  bool DropItemTask::CheckRunning() {
    return IsRunning;
  }
}