#ifndef JOB_REMOVEITEMTASK_HPP
#define JOB_REMOVEITEMTASK_HPP
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
  enum class MatchDegree;
}

namespace job {
  class RemoveItemTask : public ITask {
  public:
    void Action();
    bool CheckComplete();
    bool CheckRunning();
    std::string Name;
    std::shared_ptr<Units::Unit> Unit;
    std::shared_ptr<Map::Grid> Grid;
    std::shared_ptr<Item::ItemIdentifier> Identifier;
    std::shared_ptr<Item::MatchDegree> Degree;
    bool IsComplete = false;
    bool IsRunning = false;
  };
  class RemoveItemTaskFactory {
  public:
    std::shared_ptr<job::ITask> Create(std::shared_ptr<Map::Grid> _grid, std::shared_ptr<Units::Unit> _unit, std::shared_ptr<Item::ItemIdentifier> _identifier, std::shared_ptr<Item::MatchDegree> _degree);
  };
}
#endif