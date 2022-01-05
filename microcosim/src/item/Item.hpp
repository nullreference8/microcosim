#ifndef ITEM_HPP
#define ITEM_HPP

#include <memory>
#include <vector>
#include <string>

namespace Item {
  class ItemIdentifier;
  enum class MatchDegree { FAMILY, ORDER, TYPE, FORM, EXACT };
  
  class BaseItem {
    public:
      std::shared_ptr<Item::ItemIdentifier> Identifier;
      virtual bool Match(Item::ItemIdentifier identifier, MatchDegree degree);
  };


  class Resource : public BaseItem {
    public:
      int PercentProcessed;
      std::shared_ptr<std::vector<Item::ItemIdentifier>> DeconstructionList;
  };

  class Order : public Resource {
    public:

  };

  class Tree : public Order {
    public:
      int Diameter;
  };

  class Log : public Order {
    public:
      int Diameter;
  };

  class Stone : public Order {
    public:
  };

  class ResourceFactory {
    public:
      std::shared_ptr<Resource> Create(Item::ItemIdentifier identifier);
  };

  class ItemFactory {
    public:
      std::shared_ptr<BaseItem> Create(Item::ItemIdentifier Identifier);
  };
}
#endif