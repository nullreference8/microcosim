#ifndef GAME_HPP
#define GAME_HPP
#include "raylib.h"
#include <memory>
#include <unordered_map>
#include <ctime>
#include <list>

namespace Controller {
  class Mouse;
}

namespace database {
  class Context;
}

namespace gui {
  enum class InterfaceName;
}

namespace Units {
  class Unit;
  enum class Responsibility;
}

namespace Map {
  class Grid;
}

namespace game {
  enum class Mode { NONE, EDIT, DESIGNATION };
  enum class AreaMode { SELECT, EDIT, NEW };
  enum class AreaType { ROOM, STORAGE };
  enum class AreaEditMode { ADD, REMOVE };
  class Designation;
  class State {
    public:
      State();
      std::clock_t Start = std::clock();
      double GameTime = (std::clock() - Start) / (double)CLOCKS_PER_SEC;
      std::shared_ptr<Mode> _Mode = std::make_shared<Mode>(Mode::NONE);
      std::shared_ptr<AreaMode> _AreaMode = std::make_shared<AreaMode>(AreaMode::SELECT);
      std::shared_ptr<AreaType> _AreaType = std::make_shared<AreaType>(AreaType::ROOM);
      std::shared_ptr<AreaEditMode> _AreaEditMode = std::make_shared<AreaEditMode>(AreaEditMode::ADD);
      std::shared_ptr<std::unordered_map<gui::InterfaceName, Rectangle>> ActiveInterfaces;
      std::shared_ptr<database::Context> DbContext;
      std::shared_ptr<std::list<std::shared_ptr<Units::Unit>>> Units;
      std::shared_ptr<Map::Grid> Grid;
      //TODO create a means to cleanup designation requests
      std::shared_ptr<std::list<game::Designation>> Designations = std::shared_ptr<std::list<game::Designation>>(new std::list<game::Designation>());

      bool ActiveInterfaceClicked(std::shared_ptr<Controller::Mouse> mouse);
      void RunDesignations();
      void CheckAreaItemDrop();
      std::shared_ptr<Units::Unit> FindUnitByResponsibility(Units::Responsibility responsibility);
  };
}
#endif