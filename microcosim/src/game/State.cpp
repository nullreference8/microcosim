#include "src/game/State.hpp"
#include "src/database/Context.hpp"
namespace game {
  State::State() {
    database::Context dbContext;
    //dbContext.InitDB();
    DbContext = std::make_shared<database::Context>(dbContext);
  }
}