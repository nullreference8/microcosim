#ifndef JOB_FINDITEMMAPTASK_HPP
#define JOB_FINDITEMMAPTASK_HPP
#include <memory>
#include <string>
#include "src/job/ITask.hpp"

namespace Units {
  class Unit;
}

namespace Map {
  class Grid;
}

namespace Item {
  class ItemIdentifier;
}

namespace job {

  class FindItemMapTask : public ITask {
  public:
    void Action();
    bool CheckComplete();
    bool CheckRunning();
    std::string Name;
    std::shared_ptr<Units::Unit> Unit;
    std::shared_ptr<Map::Grid> Grid;
    std::shared_ptr<Item::ItemIdentifier> Content;
    bool IsComplete = false;
    bool IsRunning = false;
  };

  class FindItemMapTaskFactory {
  public:
    std::shared_ptr<job::ITask> Create(std::shared_ptr<Map::Grid> _grid, std::shared_ptr<Units::Unit> _unit, std::shared_ptr<Item::ItemIdentifier> _content);
  };
}
#endif