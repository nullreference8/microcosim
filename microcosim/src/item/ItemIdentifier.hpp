#ifndef ITEM_IDENTIFIER_HPP
#define ITEM_IDENTIFIER_HPP
#include <memory>
#include <string>

namespace Item {
  class ItemIdentifier {
    public:
      std::string Family;
      std::string Order;
      std::string Type;
      std::string Form;
      std::string Name;

      std::string GetHashString();
  };

}
#endif