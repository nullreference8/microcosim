#include "src/item/ItemIdentifier.hpp"

namespace Item {
  std::string ItemIdentifier::GetHashString() {
    return this->Family + ":" + this->Order + ":" + this->Type + ":" + this->Form;
  }
}