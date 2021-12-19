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

namespace Jobs {
  class Manager {
    public:
      void RunJobTasks(std::shared_ptr<Units::Unit> unitList);
      std::shared_ptr<Threading::Manager> tm;
  };
  class ManagerFactory {
    public:
      std::shared_ptr<Jobs::Manager> Create(std::shared_ptr<Threading::Manager> _tm);
  };
}
#endif