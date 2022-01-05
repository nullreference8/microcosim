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
  class ITask;
  class Job {
    public:
      std::vector<std::shared_ptr<job::ITask>> Tasks;
  };
}
#endif