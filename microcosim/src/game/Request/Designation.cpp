#include "src/game/Request/Designation.hpp"
#include "src/game/Request/DesignationType.hpp"
#include "src/map/Map.hpp"
#include "src/job/Jobs.hpp"
#include "src/job/FindItemMapTask.hpp"
#include "src/item/ItemIdentifier.hpp"
#include "src/item/Item.hpp"

namespace game {
  Designation::Designation(std::shared_ptr<Map::Grid> grid, game::DesignationType type) {
    Grid = grid;
    Type = type;
  }

  void Designation::Execute() {
    switch (Type) {
    case game::DesignationType::CHOPTREE:
      
      break;
    default:
      break;

    }
  }

  //job::Job Designation::createChopTreeJob() {}
}