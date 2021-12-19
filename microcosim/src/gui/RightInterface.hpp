#ifndef GUIRIGHTINTERFACE_HPP
#define GUIRIGHTINTERFACE_HPP
#include <memory>
#include <list>

namespace game {
  class State;
}

namespace Controller {
  class Mouse;
}

namespace Map {
  class Grid;
}

namespace gui {

  class RightInterface{
    public:
      RightInterface(std::shared_ptr<game::State> gameState, std::shared_ptr<Map::Grid> grid, int screenWidth, int screenHeight);

      int RightInterfaceStartY;
      int RightInterfaceStartX;
      int RightInterfaceEndX;
      int RightInterfaceEndY;

      std::shared_ptr<game::State> GameState;
      std::shared_ptr<Map::Grid> Grid;

      void Draw(std::shared_ptr<Controller::Mouse> mouse);
  };
}
#endif