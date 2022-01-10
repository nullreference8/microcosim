#ifndef JOB_CHOPTREEJOBFACTORY_HPP
#define JOB_CHOPTREEJOBFACTORY_HPP
#include <memory>
#include <list>

namespace game {
  class Designation;
  class State;
}

namespace job {
  class Job;
}

namespace job {
  class Job;
  class ChopTreeJobFactory {
  public:
    std::shared_ptr<job::Job> Create(std::shared_ptr<game::State> gameState, std::shared_ptr<game::Designation> designation);
  };
}

#endif