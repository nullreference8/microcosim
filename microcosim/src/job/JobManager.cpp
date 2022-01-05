#include "src/job/JobManager.hpp"
#include "src/threading/ThreadManager.hpp"
#include "src/units/Units.hpp"
#include "src/job/Jobs.hpp"
namespace job {

  std::shared_ptr<job::Manager> ManagerFactory::Create(std::shared_ptr<Threading::Manager> _tm) {
    job::Manager manager;
    manager.tm = _tm;
    return std::make_shared<job::Manager>(manager);
  };

  void Manager::RunJobTasks(std::shared_ptr<Units::Unit> unit) {
    if (!unit->currentTask && unit->jobs.size() > 0 && unit->jobs.back()->Tasks.size() > 0) {
      auto task = unit->jobs.back()->Tasks.back();
      unit->currentTask = task;
      if (unit && unit->currentTask) {
        tm->pool->push([unit](int threadId) { unit->currentTask->Action(); }); 
      }
    } else if (unit->currentTask && unit->currentTask->CheckComplete()) {
      if (unit->jobs.size() > 0) {
        auto tasks = &unit->jobs.back()->Tasks;
        tasks->pop_back();
        unit->currentTask = nullptr;
        if (tasks->size() == 0) {
          unit->jobs.pop_back();
        }
      }
    }
  }
}