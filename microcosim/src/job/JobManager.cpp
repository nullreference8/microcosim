#include "src/job/JobManager.hpp"
#include "src/threading/ThreadManager.hpp"
#include "src/units/Units.hpp"
#include "src/job/Jobs.hpp"
namespace Jobs {

  std::shared_ptr<Jobs::Manager> ManagerFactory::Create(std::shared_ptr<Threading::Manager> _tm) {
    Jobs::Manager manager;
    manager.tm = _tm;
    return std::make_shared<Jobs::Manager>(manager);
  };

  void Manager::RunJobTasks(std::shared_ptr<Units::Unit> unit) {
    if (!unit->currentTask && unit->jobs.size() > 0 && unit->jobs.back()->TaskRequests.size() > 0) {
      auto taskRequests = unit->jobs.back()->TaskRequests;
      auto tr = taskRequests.back();
      if (tr.Name == "FindContent") {
        Jobs::FindContentTaskFactory factory;
        auto res = factory.Create(tr.Grid, unit, tr.Identifier);
        unit->currentTask = res;
      } else if (tr.Name == "FindPath") {
        Jobs::FindPathTaskFactory factory;
        auto res = factory.Create(tr.Grid, unit);
        unit->currentTask = res;
      } else if (tr.Name == "RemoveItem") {
        Jobs::RemoveItemTaskFactory factory;
        auto res = factory.Create(tr.Grid, unit, tr.Identifier, tr.Degree);
        unit->currentTask = res;
      }
      if (unit && unit->currentTask) {
        tm->pool->push([unit](int threadId) { unit->currentTask->Action(); }); 
      }
    } else if (unit->currentTask && unit->currentTask->CheckComplete()) {
      if (unit->jobs.size() > 0) {
        auto taskRequests = &unit->jobs.back()->TaskRequests;
        taskRequests->pop_back();
        unit->currentTask = nullptr;
        if (taskRequests->size() == 0) {
          unit->jobs.pop_back();
        }
      }
    }
  }
}