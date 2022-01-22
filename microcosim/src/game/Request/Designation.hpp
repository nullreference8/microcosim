#ifndef GAME_REQUEST_DESIGNATION_HPP
#define GAME_REQUEST_DESIGNATION_HPP

#include "src/game/Request/IRequest.hpp"

#include <string> 
#include <memory>  

namespace map {
  class Grid;
  class Tile;
}

namespace job {
  class Job;
  class Manager;
}

namespace Units {
  class Unit;
}
//Designations require units to be assigned to them. Once assigned the job is created. Designation goes away when the square
namespace game {
  enum class DesignationType;
  class Designation {
  public:
    Designation(std::shared_ptr<map::Grid> grid, game::DesignationType type, std::shared_ptr<map::Tile> tile);
    std::shared_ptr<map::Grid> Grid;
    std::shared_ptr<map::Tile> Tile;
    game::DesignationType Type;
    std::shared_ptr<Units::Unit> AssignedUnit;
    bool IsRunning = false;
    //void QueueJob();
    //bool CheckComplete();
    //bool CheckRunning();
  };
}
#endif
