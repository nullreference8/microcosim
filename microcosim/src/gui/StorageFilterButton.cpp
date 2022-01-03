#include "src/gui/StorageFilterButton.hpp"
#include "src/item/Item.hpp"
#include "src/item/ItemIdentifier.hpp"
#include "src/area/Storage.hpp"
#include "raylib.h"
namespace gui {
  StorageFilterButton::StorageFilterButton(std::shared_ptr<area::Storage> storageArea, Item::ItemIdentifier itemIdentifier, Item::MatchDegree matchDegree, Rectangle position, std::string text, Color color)
    : Button(position, text, color) {
    StorageArea = storageArea;
    ItemIdentifier = std::make_shared<Item::ItemIdentifier>(itemIdentifier);
    _MatchDegree = std::make_shared<Item::MatchDegree>(matchDegree);
  };
  void StorageFilterButton::ClickAction() {
    switch (*_MatchDegree)
    {
      case Item::MatchDegree::FAMILY: {
        if (!StorageArea->AcceptsItem(*ItemIdentifier)) {
          StorageArea->SetAllFamilyFilter(*ItemIdentifier);
        } else {
          StorageArea->RemoveItemFilter(StorageArea->GetAllFamilyFilter(*ItemIdentifier));
        }
        break;
      }
      case Item::MatchDegree::ORDER: {
        if (!StorageArea->AcceptsItem(*ItemIdentifier)) {
          StorageArea->SetAllOrderFilter(*ItemIdentifier);
        } else {
          StorageArea->RemoveItemFilter(StorageArea->GetAllOrderFilter(*ItemIdentifier));
        }
        break;
      }
      case Item::MatchDegree::TYPE: {
        if (!StorageArea->AcceptsItem(*ItemIdentifier)) {
          StorageArea->SetAllTypeFilter(*ItemIdentifier);
        } else {
          StorageArea->RemoveItemFilter(StorageArea->GetAllTypeFilter(*ItemIdentifier));
        }
        break;
      }
      case Item::MatchDegree::FORM: {
        if (!StorageArea->AcceptsItem(*ItemIdentifier)) {
          StorageArea->SetAllFormFilter(*ItemIdentifier);
        } else {
          StorageArea->RemoveItemFilter(StorageArea->GetAllFormFilter(*ItemIdentifier));
        }
        break;
      }
      default: {
        break;
      }
    }
  };
  void StorageFilterButton::HoverAction() {

  };
  void StorageFilterButton::Draw(std::shared_ptr<Controller::Mouse> mouse) {
    Button::Draw(mouse);
    if (StorageArea->AcceptsItem(*ItemIdentifier)) {
      DrawRectangle(Position.x, Position.y, 20, 20, GREEN);
    }
    else {
      DrawRectangle(Position.x, Position.y, 20, 20, RED);
    }
  };
}