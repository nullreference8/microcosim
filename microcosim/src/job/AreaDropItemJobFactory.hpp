#ifndef JOB_AREADROPITEMJOBFACTORY_HPP
#define JOB_AREADROPITEMJOBFACTORY_HPP
#include <memory>
#include <list>

namespace game {
  class Designation;
  class State;
}

namespace job {
  class Job;
}

namespace Units {
  class Unit;
}

namespace Item {
  class ItemIdentifier;
}

namespace area {
  class Storage;
}

namespace job {
  class Job;
  class AreaDropItemJobFactory {
  public:
    std::shared_ptr<job::Job> Create(std::shared_ptr<game::State> gameState, std::shared_ptr<area::Storage> storage, std::shared_ptr<Units::Unit> unit, std::shared_ptr<Item::ItemIdentifier> item);
  };
}

#endif