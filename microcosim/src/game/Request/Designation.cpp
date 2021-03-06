#include "src/game/Request/Designation.hpp"
#include "src/game/Request/DesignationType.hpp"
#include "src/map/Map.hpp"
#include "src/job/Jobs.hpp"
#include "src/job/FindItemMapTask.hpp"
#include "src/item/ItemIdentifier.hpp"
#include "src/item/Item.hpp"

namespace game {
  Designation::Designation(std::shared_ptr<map::Grid> grid, game::DesignationType type, std::shared_ptr<map::Tile> tile) {
    Grid = grid;
    Type = type;
    Tile = tile;
  }

  //job::Job Designation::createChopTreeJob() {}
}