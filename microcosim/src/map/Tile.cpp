#include "src/map/Tile.hpp"
#include "src/inventory/Inventory.hpp"
namespace Map {
  Tile::Tile(){
    InventoryContents = new Inventory::InventoryContents();
  }
}