#ifndef ITEM_REPOSITORY_HPP
#define ITEM_REPOSITORY_HPP
#include <memory>
#include <vector>
#include <future>

namespace game {
  class State;
}

namespace database {
  class Context;
}

namespace Item {
  class ItemIdentifier;
  class Repository {
    public:
      Repository(std::shared_ptr<game::State> gameState);
      std::shared_ptr<game::State> GameState;
      std::shared_ptr<std::vector<Item::ItemIdentifier>> SelectAllIdentifier();
      std::shared_ptr<std::vector<Item::ItemIdentifier>> SelectFamilies();
      std::shared_ptr<std::vector<Item::ItemIdentifier>> SelectOrders(Item::ItemIdentifier identifier);
      std::shared_ptr<std::vector<Item::ItemIdentifier>> SelectType(Item::ItemIdentifier identifier);
      std::shared_ptr<std::vector<Item::ItemIdentifier>> SelectForm(Item::ItemIdentifier identifier);
  };
}
#endif