#ifndef JOB_UNITSETTARGETTILETASK_HPP
#define JOB_UNITSETTARGETTILETASK_HPP
#include <memory> 
#include <string>
#include "src/job/ITask.hpp"

namespace Units {
  class Unit;
}

namespace Map {
  class Tile;
}

namespace job {
  class UnitSetTargetTileTask : public ITask {
  public:
    void Action();
    bool CheckComplete();
    bool CheckRunning();
    std::string Name;
    std::shared_ptr<Units::Unit> Unit;
    std::shared_ptr<Map::Tile> Tile;
    bool IsComplete = false;
    bool IsRunning = false;
  };
  class UnitSetTargetTileTaskFactory {
  public:
    std::shared_ptr<job::ITask> Create(std::shared_ptr<Map::Tile> tile, std::shared_ptr<Units::Unit> unit);
  };
}

#endif