#ifndef THREADING_HPP
#define THREADING_HPP
#include "ctpl.h"
#include <memory>

namespace Threading {
  
  class Manager {
    public:
      Manager() {
        is_running = false;
        pool = std::shared_ptr<ctpl::thread_pool>(new ctpl::thread_pool);
        pool->resize(2);
        run();
      }
      void start();
      void stop();
      void clear();
      void add_task(std::function<void(int)>);
      std::shared_ptr<ctpl::thread_pool> pool;
    private:
      bool is_running;
      void run() {
        if (is_running) {
          if(pool->size() > 0) {
            pool->pop();
          } else {
            std::this_thread::sleep_for (std::chrono::seconds(1));
          }
        }
      }
  };
  class ManagerFactory {
    public:
      std::shared_ptr<Threading::Manager> Create();
  };
}
#endif