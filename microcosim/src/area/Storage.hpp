#ifndef STORAGE_HPP
#define STORAGE_HPP
#include "src/area/Area.hpp"
#include <memory>
#include <unordered_map>

namespace Item {
  enum class ItemDegree;
  class ItemIdentifier;
}

namespace area {
  class Storage : public BaseArea {
    public:
      Storage();
      std::shared_ptr<std::unordered_map<std::string, int>> AcceptedItems;

      std::string GetAllFamilyFilter(Item::ItemIdentifier item);
      std::string GetAllOrderFilter(Item::ItemIdentifier item);
      std::string GetAllTypeFilter(Item::ItemIdentifier item);
      std::string GetAllFormFilter(Item::ItemIdentifier item);
      std::string FindOpenTile(Item::ItemIdentifier item);
      void SetItemFilter(Item::ItemIdentifier item, int quantity);
      void SetAllFamilyFilter(Item::ItemIdentifier item);
      void SetAllOrderFilter(Item::ItemIdentifier item);
      void SetAllTypeFilter(Item::ItemIdentifier item);
      void SetAllFormFilter(Item::ItemIdentifier item);
      void RemoveItemFilter(Item::ItemIdentifier item);
      void RemoveItemFilter(std::string itemFilterString);
      bool AcceptsItem(Item::ItemIdentifier item);
  };
}
#endif