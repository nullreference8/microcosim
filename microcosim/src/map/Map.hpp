#ifndef MAP_HPP
#define MAP_HPP

#include "src/pathing/AStar.hpp"
#include "src/map/Tile.hpp"
#include <vector>
#include <tuple>
#include <memory>

namespace Item {
  class ItemIdentifier;
}

namespace Controller {
  class Mouse;
}

namespace area {
  class BaseArea;
}

namespace game {
  class State;
}

namespace map { 
  class Grid {
    public:
      Grid(std::shared_ptr<game::State> gameState); 
      std::vector<std::vector<map::Tile>> TileMap;
      int TileSize = 20;
      std::vector<std::vector<int>> mapData;
      std::shared_ptr<std::vector<std::shared_ptr<area::BaseArea>>> Areas = std::shared_ptr<std::vector<std::shared_ptr<area::BaseArea>>>(new std::vector<std::shared_ptr<area::BaseArea>>());
      std::shared_ptr<std::vector<std::shared_ptr<map::Tile>>> SelectedTiles = std::shared_ptr<std::vector<std::shared_ptr<map::Tile>>>(new std::vector<std::shared_ptr<map::Tile>>());
      //Selected BaseArea. Returns nullptr if no area selected
      std::shared_ptr<area::BaseArea> SelectedArea;
      AStar::Generator astarPathing;
      std::shared_ptr<game::State> GameState;
      void InitializeMap();
      Tile* FindNearest(int startX, int startY, Item::ItemIdentifier item);
      void UpdateMouseTracking(std::shared_ptr<Controller::Mouse> mouse);


      int MouseXIndex = -1; 
      int MouseYIndex = -1;
      int SelectedTileXIndex = -1;
      int SelectedTileYIndex = -1;
      bool IsATileSelected = false;
      bool IsClickAndDragActive = false;
      int MouseDragXIndex = -1;
      int MouseDragYIndex = -1;
      int StartX = -1;
      int EndX = -1;
      int StartY = -1;
      int EndY = -1;
    
    private:
      std::tuple<std::vector<int>, bool> expandSearch(int startX, int startY, int distance);
      void detectClickAndDrag(std::shared_ptr<Controller::Mouse> mouse);
      void selectTiles();
      void unselectTiles();
  };

}
#endif