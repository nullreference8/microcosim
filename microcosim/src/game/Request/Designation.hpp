#ifndef GAME_REQUEST_DESIGNATION_HPP
#define GAME_REQUEST_DESIGNATION_HPP

#include "src/game/Request/IRequest.hpp"

#include <string> 
#include <memory>  

namespace Map {
  class Grid;
}

namespace job {
  class Job;
}

namespace game {
  enum class DesignationType;
  class Designation : public game::IRequest {
  public:
    Designation(std::shared_ptr<Map::Grid> grid, game::DesignationType type );
    std::shared_ptr<Map::Grid> Grid;
    game::DesignationType Type;
    void Execute();
    //bool CheckComplete();
    //bool CheckRunning();

  private:
    std::shared_ptr<job::Job> createChopTreeJob();
  };
}
#endif
