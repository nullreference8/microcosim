#ifndef JOB_HPP
#define JOB_HPP
#include <vector>
#include <string>
#include <memory>

namespace Map {
  class Grid;
}

namespace Item { 
  class ItemIdentifier;
  enum class MatchDegree;
}

namespace job {
  
  class TaskRequest {
    public:
      std::string Name;
      std::shared_ptr<Map::Grid> Grid;
      std::shared_ptr<Item::ItemIdentifier> Identifier;
      std::shared_ptr<Item::MatchDegree> Degree;
  };

  class Job {
      public:
        std::vector<TaskRequest> TaskRequests;
  };
}
#endif