#ifndef JOB_DROPITEMTASK_HPP
#define JOB_DROPITEMTASK_HPP
#include <memory> 
#include <string>
#include "src/job/ITask.hpp"  

namespace Units {
  class Unit;
}

namespace game {
  class State;
}

namespace Item {
  class ItemIdentifier;
  enum class MatchDegree;
}

namespace Map {
  class Grid;
}

namespace job {
  class DropItemTask : public ITask {
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
  class DropItemTaskFactory {
  public:
    std::shared_ptr<job::ITask> Create(std::shared_ptr<game::State> gameState, std::shared_ptr<Units::Unit> _unit, std::shared_ptr<Item::ItemIdentifier> _identifier);
  };
}
#endif