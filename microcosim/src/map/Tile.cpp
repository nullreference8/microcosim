#include "src/map/Tile.hpp"
#include "src/inventory/Inventory.hpp"
namespace map {
  Tile::Tile(){
    InventoryContents = new Inventory::InventoryContents();
  }
}