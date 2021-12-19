#ifndef GAME_HPP
#define GAME_HPP
#include <memory>
#include <ctime>

namespace database {
  class Context;
}

namespace game {
  enum class Mode { NONE, EDIT };
  enum class AreaMode { SELECT, EDIT, NEW };
  enum class AreaType { ROOM, STORAGE };
  enum class AreaEditMode { ADD, REMOVE };
  class State {
    public:
      State();
      std::clock_t Start = std::clock();
      double GameTime = (std::clock() - Start) / (double)CLOCKS_PER_SEC;
      std::shared_ptr<Mode> _Mode = std::make_shared<Mode>(Mode::NONE);
      std::shared_ptr<AreaMode> _AreaMode = std::make_shared<AreaMode>(AreaMode::SELECT);
      std::shared_ptr<AreaType> _AreaType = std::make_shared<AreaType>(AreaType::ROOM);
      std::shared_ptr<AreaEditMode> _AreaEditMode = std::make_shared<AreaEditMode>(AreaEditMode::ADD);
      std::shared_ptr<database::Context> DbContext;
  };
}
#endif