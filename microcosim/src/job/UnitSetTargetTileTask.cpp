#include "src/job/UnitSetTargetTileTask.hpp"
#include "src/units/Units.hpp"
#include "src/map/Tile.hpp"
namespace job {
  std::shared_ptr<job::ITask> UnitSetTargetTileTaskFactory::Create(std::shared_ptr<map::Tile> tile, std::shared_ptr<Units::Unit> unit) {
    UnitSetTargetTileTask task;
    task.Name = "UnitSetTargetTileTask";
    task.Tile = tile;
    task.Unit = unit;
    return std::make_shared<job::UnitSetTargetTileTask>(task);
  }

  void UnitSetTargetTileTask::Action() {
    IsRunning = true;
    Unit->targetVector = Tile->positionVector;
  }

  bool UnitSetTargetTileTask::CheckComplete() {
    if (!IsComplete) {
      if (Unit->targetVector == Tile->positionVector) {
        IsComplete = true;
      }
    }
    return IsComplete;
  };

  bool UnitSetTargetTileTask::CheckRunning() {
    return IsRunning;
  }
}
