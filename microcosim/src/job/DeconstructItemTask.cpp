#include "src/job/DeconstructItemTask.hpp"
#include "src/units/Units.hpp"
#include "src/map/Map.hpp"
#include "src/map/Tile.hpp"
#include "src/item/ItemIdentifier.hpp"
#include "src/item/Item.hpp"
#include "src/inventory/Inventory.hpp"
namespace job {
  std::shared_ptr<job::ITask> DeconstructItemTaskFactory::Create(std::shared_ptr<Item::ItemIdentifier> item, std::shared_ptr<Item::MatchDegree> matchDegree, std::shared_ptr<Map::Grid> grid, std::shared_ptr<Units::Unit> unit) {
    DeconstructItemTask task;
    task.Name = "DeconstructItemTask";
    task.MatchDegree = matchDegree;
    task.Unit = unit;
    task.ItemIdentifier = item;
    task.Grid = grid;
    return std::make_shared<job::DeconstructItemTask>(task);
  }

  void DeconstructItemTask::Action() {
    IsRunning = true;
  }

  bool DeconstructItemTask::CheckComplete() {
    auto tileInventory = Grid->tileMap[Unit->currentVector.y][Unit->currentVector.x].InventoryContents;
    if (Unit->currentVector == Unit->targetVector) {
      if (tileInventory->FindItemIndex(*ItemIdentifier, *MatchDegree) != -1) {
        auto item = tileInventory->RemoveItem(*ItemIdentifier, *MatchDegree);
        auto resource = std::dynamic_pointer_cast<Item::Resource>(item);
        for (const auto& value : *resource->DeconstructionList) {
          Item::ResourceFactory factory;
          auto dItem = factory.Create(value);
          Unit->inventory->AddItem(dItem);
        }
      }
      IsComplete = true;
    }
    return IsComplete;
  };

  bool DeconstructItemTask::CheckRunning() {
    return IsRunning;
  }
}
