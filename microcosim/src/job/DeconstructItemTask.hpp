#ifndef JOB_DECONSTRUCTITEMTASK_HPP
#define JOB_DECONSTRUCTITEMTASK_HPP
#include <memory> 
#include <string>
#include "src/job/ITask.hpp"

namespace game {
  class State;
}

namespace Units {
  class Unit;
}

namespace map {
  class Grid;
}

namespace Item {
  class ItemIdentifier;
  enum class MatchDegree;
}

namespace job {
  class DeconstructItemTask : public ITask {
  public:
    void Action();
    bool CheckComplete();
    bool CheckRunning();
    std::string Name;
    std::shared_ptr<Units::Unit> Unit;
    std::shared_ptr<map::Grid> Grid;
    std::shared_ptr<Item::ItemIdentifier> ItemIdentifier;
    std::shared_ptr<Item::MatchDegree> MatchDegree;
    bool IsComplete = false;
    bool IsRunning = false;
  };
  class DeconstructItemTaskFactory {
  public:
    std::shared_ptr<job::ITask> Create(std::shared_ptr<Item::ItemIdentifier> item, std::shared_ptr<Item::MatchDegree> matchDegree, std::shared_ptr<game::State> gameState, std::shared_ptr<Units::Unit> unit);
  };
}

#endif