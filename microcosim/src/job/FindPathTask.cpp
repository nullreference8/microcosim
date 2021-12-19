#include "src/job/Jobs.hpp"
#include "src/units/Units.hpp"
#include "src/map/Map.hpp"
#include <memory>

namespace Jobs {
  std::shared_ptr<Jobs::ITask> FindPathTaskFactory::Create(std::shared_ptr<Map::Grid> _grid, std::shared_ptr<Units::Unit> _unit) {
    FindPathTask task;
    task.Grid = _grid;
    task.Unit = _unit;
    return std::make_shared<FindPathTask>(task);
  }; 
  void FindPathTask::Action(){
    IsRunning = true;
    Unit->path = AStar::CoordinateList{};
    auto path = Grid->astarPathing.findPath(Unit->currentVector, Unit->targetVector);
    Unit->path = path;
  };
  bool FindPathTask::CheckComplete(){
    if (!IsComplete) {
      if (Unit->path.size() > 0) {
        IsComplete = true;
        IsRunning = false;
      }
    }
    return IsComplete;
  };
  bool FindPathTask::CheckRunning(){
    return IsRunning;
  };
}