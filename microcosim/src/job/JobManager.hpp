#ifndef JOBMANAGER_HPP
#define JOBMANAGER_HPP
#include <memory>
#include <list>

namespace Units {
  class Unit;
}

namespace Threading {
  class Manager;
}

namespace job {
  class Manager {
    public:
      Manager(std::shared_ptr<Threading::Manager> tm);
      void RunJobTasks(std::shared_ptr<Units::Unit> unitList);
      std::shared_ptr<Threading::Manager> ThreadingManager;
  };
}
#endif