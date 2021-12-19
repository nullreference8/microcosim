#ifndef INVENTORY_HPP
#define INVENTORY_HPP
#include <unordered_map>
#include <vector>
#include <memory>

namespace Item {
  enum class MatchDegree;
  class BaseItem;
  class ItemIdentifier; 
}

namespace Inventory {
  class InventoryContents {
    public:
      InventoryContents();
      std::shared_ptr<std::vector<std::shared_ptr<Item::BaseItem>>> Items;
      std::shared_ptr<std::unordered_map<std::string, std::vector<std::shared_ptr<Item::ItemIdentifier>>>> Contents;
      
      void AddContent(Item::ItemIdentifier item);
      std::vector<std::shared_ptr<Item::ItemIdentifier>> ViewContent(Item::ItemIdentifier item);
      bool HasContent(Item::ItemIdentifier item);
      void RemoveContent(Item::ItemIdentifier item); 
      
      void AddItem(std::shared_ptr<Item::BaseItem> item);
      int FindItemIndex(Item::ItemIdentifier identifier, Item::MatchDegree degree);
      std::shared_ptr<Item::BaseItem> RemoveItem(Item::ItemIdentifier identifier, Item::MatchDegree degree);

    private:
      std::string createTileContentKey(Item::ItemIdentifier item);
  }; 
}
#endif