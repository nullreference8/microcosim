#include "src/game/State.hpp"
#include "src/database/Context.hpp"
#include "src/gui/interface/GameInterface.hpp"
#include "src/controller/Mouse.hpp"
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
}