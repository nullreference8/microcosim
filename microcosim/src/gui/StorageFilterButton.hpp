#ifndef GUI_STORAGE_FILTER_BUTTON_HPP
#define GUI_STORAGE_FILTER_BUTTON_HPP
#include "src/gui/Button.hpp"
#include <memory>
namespace area {
  class Storage;
}
namespace Item {
  enum class MatchDegree;
  class ItemIdentifier;
}
namespace gui {
  class StorageFilterButton : public Button {
  public:
    StorageFilterButton(std::shared_ptr<area::Storage> storageArea, Item::ItemIdentifier itemIdentifier, Item::MatchDegree matchDegree, int startX, int startY, int endX, int endY, std::string text, Color color);
    std::shared_ptr<area::Storage> StorageArea;
    std::shared_ptr<Item::ItemIdentifier> ItemIdentifier;
    std::shared_ptr<Item::MatchDegree> _MatchDegree;
    void ClickAction();
    void HoverAction();
    void Draw(std::shared_ptr<Controller::Mouse> mouse);
  };
}
#endif