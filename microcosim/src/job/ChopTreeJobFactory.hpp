#ifndef JOB_CHOPTREEJOBFACTORY_HPP
#define JOB_CHOPTREEJOBFACTORY_HPP
#include <memory>
#include <list>

namespace Map {
  class Grid;
  class Tile;
}

namespace Units {
  class Unit;
}

namespace game {
  class Designation;
}

namespace job {
  class Job;
}

namespace job {
  class Job;
  class ChopTreeJobFactory {
  public:
    std::shared_ptr<job::Job> Create(std::shared_ptr<Map::Grid> grid, std::shared_ptr<std::list<std::shared_ptr<Units::Unit>>> units, std::shared_ptr<game::Designation> designation);
  };
}

#endif