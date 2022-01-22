#ifndef AREA_HPP
#define AREA_HPP
#include <memory>
#include <vector>
#include <string>
#include <unordered_map>

namespace map {
  class Tile;
}

namespace game {
  enum class AreaType;
}

namespace area {
  class BaseArea {
  public:
    game::AreaType AreaType;
    std::shared_ptr<std::unordered_map<std::string, std::shared_ptr<map::Tile>>> Tiles = std::shared_ptr<std::unordered_map<std::string, std::shared_ptr<map::Tile>>>(new std::unordered_map<std::string, std::shared_ptr<map::Tile>>());
    virtual void AddTiles(std::vector<std::shared_ptr<map::Tile>> tiles);
    virtual void RemoveTiles(std::vector<std::shared_ptr<map::Tile>> tiles);
    virtual bool LookupTile(int X, int Y);
    virtual std::shared_ptr<map::Tile> GetOpenTile();
    int x0;
    int y0;
    int x1;
    int y1;
    std::string GetTileHashValue(std::shared_ptr<map::Tile> tile);
  };  
}
#endif