#ifndef JOB_FINDPATHTASK_HPP
#define JOB_FINDPATHTASK_HPP
#include <memory> 
#include <string>
#include "src/job/ITask.hpp"
#include "src/job/FindPathTask.hpp"

namespace Units {
  class Unit;
}

namespace Map {
  class Grid;
}

namespace job {
  class FindPathTask : public ITask {
  public:
    void Action();
    bool CheckComplete();
    bool CheckRunning();
    std::string Name;
    std::shared_ptr<Units::Unit> Unit;
    std::shared_ptr<Map::Grid> Grid;
    bool IsComplete = false;
    bool IsRunning = false;
  };
  class FindPathTaskFactory {
  public:
    std::shared_ptr<job::ITask> Create(std::shared_ptr<Map::Grid> _grid, std::shared_ptr<Units::Unit> _unit);
  };
}

#endif