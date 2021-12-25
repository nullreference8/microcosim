#ifndef AREA_HPP
#define AREA_HPP
#include <memory>
#include <vector>
#include <string>
#include <unordered_map>

namespace Map {
  class Tile;
}

namespace game {
  enum class AreaType;
}

namespace area {
  class BaseArea {
  public:
    game::AreaType AreaType;
    std::shared_ptr<std::unordered_map<std::string, std::shared_ptr<Map::Tile>>> Tiles = std::shared_ptr<std::unordered_map<std::string, std::shared_ptr<Map::Tile>>>(new std::unordered_map<std::string, std::shared_ptr<Map::Tile>>());
    virtual void AddTiles(std::vector<std::shared_ptr<Map::Tile>> tiles);
    virtual void RemoveTiles(std::vector<std::shared_ptr<Map::Tile>> tiles);
    virtual bool LookupTile(int X, int Y);
    std::string GetTileHashValue(std::shared_ptr<Map::Tile> tile);
  };  
}
#endif