#include <algorithm>
#include <unordered_map>
#include <vector>
#include <memory>
#include "src/inventory/Inventory.hpp"
#include "src/item/Item.hpp"
#include "src/item/ItemIdentifier.hpp"

namespace Inventory {
  InventoryContents::InventoryContents() {
    Items = std::shared_ptr<std::vector<std::shared_ptr<Item::BaseItem>>>(new std::vector<std::shared_ptr<Item::BaseItem>>());
    Contents = std::shared_ptr<std::unordered_map<std::string, std::vector<std::shared_ptr<Item::ItemIdentifier>>>>(new std::unordered_map<std::string, std::vector<std::shared_ptr<Item::ItemIdentifier>>>());
  }

  void InventoryContents::AddItem(std::shared_ptr<Item::BaseItem> item) {
    AddContent(*item->Identifier);
    Items->push_back(item);
  }

  std::shared_ptr<Item::BaseItem> InventoryContents::RemoveItem(Item::ItemIdentifier identifier, Item::MatchDegree degree) {
    //TODO: Not threadsafe
  
    int index = FindItemIndex(identifier, degree);
    if (index == -1) {
      return nullptr;
    }
    auto res = Items->at(index);
    std::swap(Items->at(index), Items->back());
    Items->pop_back();
    RemoveContent(*res->Identifier);
    return res;
  }

  int InventoryContents::FindItemIndex(Item::ItemIdentifier identifier, Item::MatchDegree degree) {
    int length = Items->size();
    for(int i = 0; i < length; i++) {
      auto _items = *Items;
      if (_items[i]->Match(identifier, degree)) {
        return i;
      }
    }
    return -1;
  }

  void InventoryContents::AddContent(Item::ItemIdentifier item) {
    std::string key = item.GetHashString();
    auto itemptr = std::make_shared<Item::ItemIdentifier>(item);
    if (Contents->find(key) == Contents->end()) {
      (*Contents)[key].push_back(itemptr);
    } else {
      (*Contents)[key] = std::vector<std::shared_ptr<Item::ItemIdentifier>> {itemptr};
    }
  }

  std::vector<std::shared_ptr<Item::ItemIdentifier>> InventoryContents::ViewContent(Item::ItemIdentifier item) {
    std::string key = item.GetHashString(); 
    return (*Contents)[key];
  }

  bool InventoryContents::HasContent(Item::ItemIdentifier item) {
    std::string key = item.GetHashString();
    if (Contents->find(key) != Contents->end()) {
      return true;
    } else {
      return false;
    }
  }

  void InventoryContents::RemoveContent(Item::ItemIdentifier item) {
    std::string key = item.GetHashString();
    std::vector<std::shared_ptr<Item::ItemIdentifier>> contents = (*Contents)[key];
    if (contents.size() > 0) {
      contents.pop_back();
    }
    if (contents.size() == 0) {
      Contents->erase(key); 
    } else {
      (*Contents)[key] = contents;
    }
  }
}