#include "src/game/State.hpp"
#include "src/database/Context.hpp"
#include "src/gui/interface/GameInterface.hpp"
#include "src/controller/Mouse.hpp"
#include "src/game/Request/Designation.hpp"
#include "src/game/Request/DesignationType.hpp"
#include "src/job/ChopTreeJobFactory.hpp"
#include "src/map/Map.hpp"
#include "src/units/Units.hpp"
#include "src/area/Storage.hpp"
#include "src/inventory/Inventory.hpp"
#include "src/item/ItemIdentifier.hpp"
#include "src/job/AreaDropItemJobFactory.hpp"
namespace game {
  State::State() {
    database::Context dbContext;
    //dbContext.InitDB();
    DbContext = std::make_shared<database::Context>(dbContext);
    ActiveInterfaces = std::shared_ptr<std::unordered_map<gui::InterfaceName, Rectangle>>(new std::unordered_map<gui::InterfaceName, Rectangle>);
  }

  bool State::ActiveInterfaceClicked(std::shared_ptr<Controller::Mouse> mouse) {
    for (const auto& [key, value] : *ActiveInterfaces) {
      if (mouse->MouseX >= value.x && mouse->MouseX <= value.x + value.width && mouse->MouseY >= value.y && mouse->MouseY <= value.y + value.height) {
        return true;
      }
    }
    return false;
  }

  void State::RunDesignations() {
    for (auto& des : *Designations)  {
      if (des.IsRunning){
        continue;
      }
      if (des.Type == game::DesignationType::CHOPTREE) {
        //NOTE this might break, pointer to reference?
        auto unit = FindUnitByResponsibility(Units::Responsibility::CHOP);
        if (unit) {
          job::ChopTreeJobFactory fact;
            des.AssignedUnit = unit;
          auto job = fact.Create(std::make_shared<game::State>(*this), std::make_shared<game::Designation>(des));
          unit->jobs.push_back(job);
          des.IsRunning = true;
        }

      }
    }
  }

  void State::CheckAreaItemDrop() {
    for (auto& area : *Grid->Areas) {
      if (area->AreaType == game::AreaType::STORAGE) {
        auto storage = std::dynamic_pointer_cast<area::Storage>(area);
        for (auto& unit : *Units) {
          for (auto& content : *unit->inventory->Contents) {
            auto itemIdentifier = content.second.back();
            if (!itemIdentifier->MarkedForDrop && storage->AcceptsItem(*itemIdentifier)) {
              job::AreaDropItemJobFactory afact;
              auto job = afact.Create(std::make_shared<game::State>(*this), storage, unit, itemIdentifier);
              unit->jobs.push_back(job);
              itemIdentifier->MarkedForDrop = true;
            }
          }
        }
      }
    }
  }

  std::shared_ptr<Units::Unit> State::FindUnitByResponsibility(Units::Responsibility responsibility) {
    for (auto unit : *Units) {
      if (!unit->currentTask) {
        for (auto& resp : unit->Responsibilities) {
          if (resp == responsibility) {
            return  unit;
          }
        }
      }
    }
    return nullptr;
  }
}