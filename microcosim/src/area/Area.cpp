#include "src/area/Area.hpp"
#include "src/map/Tile.hpp"
#include "src/inventory/Inventory.hpp"
#include <string>
namespace area {
  bool BaseArea::LookupTile(int X, int Y) {
    auto hashValue = "X" + std::to_string(X) + "Y" + std::to_string(Y);
    if(Tiles->find(hashValue) != Tiles->end()) {
      return true;
    };
    return false;
  }

  void BaseArea::AddTiles(std::vector<std::shared_ptr<Map::Tile>> tiles) {
    for (auto tile : tiles) {
      std::string tileHashValue = GetTileHashValue(tile);
      if(Tiles->find(tileHashValue) == Tiles->end()) {
        (*Tiles)[tileHashValue] = tile;
      }
    }
  }

  void BaseArea::RemoveTiles(std::vector<std::shared_ptr<Map::Tile>> tiles) {
    for (auto tile : tiles) {
      std::string tileHashValue = GetTileHashValue(tile);
      if(Tiles->find(tileHashValue) != Tiles->end()) {
        Tiles->erase(tileHashValue);
      }
    }
  }

  std::shared_ptr<Map::Tile> BaseArea::GetOpenTile() {
    for (auto& tile : *Tiles) {
      if (tile.second->InventoryContents->Items->size() == 0) {
        return tile.second;
      }
    }
    return nullptr;
  }

  std::string BaseArea::GetTileHashValue(std::shared_ptr<Map::Tile> tile) {
    return "X" + std::to_string(tile->positionVector.x) + "Y" + std::to_string(tile->positionVector.y);
  }

}