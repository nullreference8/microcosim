#include "src/item/Item.hpp"
#include "src/item/ItemIdentifier.hpp"
#include <memory>
#include <string>
#include <map>


namespace Item {

  std::shared_ptr<Resource> ResourceFactory::Create(ItemIdentifier identifier) {
    if (identifier.Family == "Wood") {
      if (identifier.Order == "Maple") {
        if (identifier.Type == "Tree") {
          auto tree = std::shared_ptr<Tree>(new Tree);
          tree->Diameter = 305;
          tree->Identifier = std::make_shared<ItemIdentifier>(identifier);
          auto logIdentifier = std::shared_ptr<ItemIdentifier>(new ItemIdentifier);
          logIdentifier->Family == identifier.Family;
          logIdentifier->Order == identifier.Order;
          logIdentifier->Type == "Log";
          tree->DeconstructionYieldMap->insert({logIdentifier, 5});
          tree->PercentProcessed = 0;
          return tree;
        }

        if (identifier.Type == "Log") {
          auto log = std::shared_ptr<Log>(new Log);
          log->Identifier = std::make_shared<ItemIdentifier>(identifier);
          log->Diameter = 305;
          log->PercentProcessed = 0;
          return log;
        }
      }
    }
  }

  bool BaseItem::Match(ItemIdentifier identifier, MatchDegree degree) {
    if (this->Identifier->Family == identifier.Family) {
      if (degree == MatchDegree::FAMILY) {
        return true;
      }
      if (this->Identifier->Order == identifier.Order) {
        if (degree == MatchDegree::ORDER) {
          return true;
        }
        if(this->Identifier->Type == identifier.Type) {
          //TODO: When item properties are implemented, exact match must be moved
          if (degree == MatchDegree::TYPE || degree == MatchDegree::EXACT) {
            return true;
          }
        }
      }
    }
    return false;
  }

  
  std::shared_ptr<BaseItem> ItemFactory::Create(ItemIdentifier identifier) {
    if (identifier.Family == "Resource") {
      ResourceFactory factory;
      return factory.Create(identifier);
    }
  }


}