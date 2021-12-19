#ifndef TILE_HPP
#define TILE_HPP
#include "src/pathing/AStar.hpp"
#include <algorithm>
#include <unordered_map>
#include <vector>

namespace Inventory {
  class InventoryContents;
}

namespace Map {
  
  class Tile {
    public:
      Tile();
      bool isWall = false;
      bool isWood = false;
      bool isStorage = false;
      bool IsSelected = false;
      AStar::Vec2i positionVector; 
      Inventory::InventoryContents *InventoryContents;
  };

  using TileRow = std::vector<Tile>;
  using TileMap = std::vector<TileRow>;

};
#endif