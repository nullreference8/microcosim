#ifndef JOB_HPP
#define JOB_HPP
#include <vector>
#include <string>
#include <memory>

namespace Map {
  class Grid;
}

namespace Units {
  class Unit;
}

namespace Item { 
  class ItemIdentifier;
  enum class MatchDegree;
}

namespace Jobs {
  class TaskRequest {
    public:
      std::string Name;
      std::shared_ptr<Map::Grid> Grid;
      std::shared_ptr<Item::ItemIdentifier> Identifier;
      std::shared_ptr<Item::MatchDegree> Degree;
  };

  class ITask {
    public:
      virtual void Action() = 0;
      virtual bool CheckComplete() = 0;
      virtual bool CheckRunning() = 0;
  };

  class FindContentTask : public ITask {
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
  class FindContentTaskFactory{
    public: 
        std::shared_ptr<Jobs::ITask> Create(std::shared_ptr<Map::Grid> _grid, std::shared_ptr<Units::Unit> _unit, std::shared_ptr<Item::ItemIdentifier> _content);
  };

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
  class RemoveItemTaskFactory{
    public:
        std::shared_ptr<Jobs::ITask> Create(std::shared_ptr<Map::Grid> _grid, std::shared_ptr<Units::Unit> _unit, std::shared_ptr<Item::ItemIdentifier> _identifier, std::shared_ptr<Item::MatchDegree> _degree);
  };

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
  class FindPathTaskFactory{
      public:
        std::shared_ptr<Jobs::ITask> Create(std::shared_ptr<Map::Grid> _grid, std::shared_ptr<Units::Unit> _unit);
  };
  class Job {
      public:
        std::vector<TaskRequest> TaskRequests;
  };
}
#endif