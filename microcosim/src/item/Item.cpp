#include "src/item/Item.hpp"
#include "src/item/ItemIdentifier.hpp"
#include <memory>
#include <string>
#include <unordered_map>


namespace Item {

  std::shared_ptr<Resource> ResourceFactory::Create(ItemIdentifier identifier) {
    if (identifier.Family == "Resource") {
      if (identifier.Order == "Wood") {
        if (identifier.Form == "Tree") {
          auto tree = std::shared_ptr<Tree>(new Tree);
          tree->Diameter = 305;
          tree->Identifier = std::make_shared<ItemIdentifier>(identifier);
          ItemIdentifier logIdentifier;
          logIdentifier.Family = identifier.Family;
          logIdentifier.Order = identifier.Order;
          logIdentifier.Form = "Log";
          std::vector<ItemIdentifier> dYield;
          dYield.push_back(logIdentifier);
          dYield.push_back(logIdentifier);
          dYield.push_back(logIdentifier);
          dYield.push_back(logIdentifier);
          dYield.push_back(logIdentifier);
          tree->DeconstructionList = std::make_shared<std::vector<ItemIdentifier>>(dYield);
          tree->PercentProcessed = 0;
          return tree;
        }

        if (identifier.Form == "Log") {
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
          if (degree == MatchDegree::TYPE) {
            return true;
          }
        }
        if (this->Identifier->Form == identifier.Form) {
          if (degree == MatchDegree::FORM) {
            return true;
          }
        }
        if (this->Identifier->Form == identifier.Form || this->Identifier->Type == identifier.Type) {
          if (degree == MatchDegree::EXACT) {
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