#ifndef TILE_HPP
#define TILE_HPP
#include "src/pathing/AStar.hpp"
#include <algorithm>
#include <unordered_map>
#include <vector>

namespace Inventory {
  class InventoryContents;
}

namespace map {
  
  class Tile {
    public:
      Tile();
      bool isWall = false;
      bool isWood = false;
      bool isStorage = false;
      bool IsSelected = false;
      int Elevation = 0;
      AStar::Vec2i positionVector; 
      Inventory::InventoryContents *InventoryContents;
  };

};
#endif