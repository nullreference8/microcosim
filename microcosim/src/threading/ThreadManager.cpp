#include "src/threading/ThreadManager.hpp"
#include <memory>
namespace Threading {
  std::shared_ptr<Threading::Manager> ManagerFactory::Create() {
    Threading::Manager manager;
    return std::make_shared<Threading::Manager>(manager);
  }

  void Manager::add_task(std::function<void(int)> task) {
    pool->push(std::ref(task));
  }
  
  void Manager::start() {
    is_running = true;
    run();
  }
}