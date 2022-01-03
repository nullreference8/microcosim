#include "src/item/ItemIdentifier.hpp"
#include "src/map/Tile.hpp"
#include "src/inventory/Inventory.hpp"
#include "src/area/Storage.hpp"
#include "src/game/State.hpp"
#include <unordered_map>
#include <string>

namespace area {
  Storage::Storage() {
    AreaType = game::AreaType::STORAGE;
    AcceptedItems = std::shared_ptr<std::unordered_map<std::string, int>>(new std::unordered_map<std::string, int>{});
  }
  std::string Storage::GetAllFamilyFilter(Item::ItemIdentifier item) {
    return item.Family + ":ALL";
  }

  std::string Storage::GetAllOrderFilter(Item::ItemIdentifier item) {
    return item.Family + ":" + item.Order + ":ALL";
  }

  std::string Storage::GetAllTypeFilter(Item::ItemIdentifier item) {
    return item.Family + ":" + item.Order + ":" + item.Type + ":ALL";
  }

  std::string Storage::GetAllFormFilter(Item::ItemIdentifier item) {
    return item.Family + ":" + item.Order + ":" + item.Type + ":" + item.Form + ":ALL";
  }


  void Storage::SetItemFilter(Item::ItemIdentifier item, int quantity) {
    auto itemFilter = item.GetHashString();
    (*AcceptedItems)[itemFilter] = quantity;
  }

  void Storage::SetAllFamilyFilter(Item::ItemIdentifier item) {
    auto familyFilter = GetAllFamilyFilter(item);
    (*AcceptedItems)[familyFilter] = 1;
  }

  void Storage::SetAllOrderFilter(Item::ItemIdentifier item) {
    auto orderFilter = GetAllOrderFilter(item);
    (*AcceptedItems)[orderFilter] = 1;
  }

  void Storage::SetAllTypeFilter(Item::ItemIdentifier item) {
    auto typeFilter = GetAllTypeFilter(item);
    (*AcceptedItems)[typeFilter] = 1;
  }

  void Storage::SetAllFormFilter(Item::ItemIdentifier item) {
    auto formFilter = GetAllFormFilter(item);
    (*AcceptedItems)[formFilter] = 1;
  }

  void Storage::RemoveItemFilter(Item::ItemIdentifier item) {
    auto itemFilter = item.GetHashString();
    AcceptedItems->erase(itemFilter);
  }

  void Storage::RemoveItemFilter(std::string itemFilterString) {
    AcceptedItems->erase(itemFilterString);
  }

  bool Storage::AcceptsItem(Item::ItemIdentifier item) {
    if (!AcceptedItems) {
      return false;
    }
    auto familyFilter = GetAllFamilyFilter(item);
    if (AcceptedItems->find(familyFilter) != AcceptedItems->end()) {
      return true;
    }

    auto orderFilter = GetAllOrderFilter(item);
    if (AcceptedItems->find(orderFilter) != AcceptedItems->end()) {
      return true;
    }

    auto formFilter = GetAllFormFilter(item);
    if (AcceptedItems->find(formFilter) != AcceptedItems->end()) {
      return true;
    }

    auto itemFilter = item.GetHashString();
    if (AcceptedItems->find(itemFilter) != AcceptedItems->end()) {
      return true;
    }
    return false;
  }

  std::string Storage::FindOpenTile(Item::ItemIdentifier item) {
    for (auto &pair : *Tiles) {
      auto tileInventory = pair.second->InventoryContents;
      if (tileInventory->Contents->size() == 0 || tileInventory->HasContent(item)) {
        return pair.first;
      }
    }
  }
}