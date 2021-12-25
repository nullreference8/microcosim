#ifndef GUIRIGHTINTERFACE_HPP
#define GUIRIGHTINTERFACE_HPP
#include <memory>
#include <vector>

namespace game {
  class State;
}

namespace Controller {
  class Mouse;
}

namespace Map {
  class Grid;
}

namespace Item {
  class Repository;
  class ItemIdentifier;
  enum class MatchDegree;
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
      std::shared_ptr<Item::Repository> ItemRepo;
      std::shared_ptr<std::vector<Item::ItemIdentifier>> Families;

      void Draw(std::shared_ptr<Controller::Mouse> mouse);
  };
}
#endif