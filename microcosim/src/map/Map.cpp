#include "src/map/Map.hpp"
#include "src/inventory/Inventory.hpp"
#include "src/item/Item.hpp"
#include "src/item/ItemIdentifier.hpp"
#include "src/controller/Mouse.hpp"
#include "src/area/Area.hpp"
#include "src/area/Storage.hpp"
#include "src/game/State.hpp"
#include "src/game/Request/Designation.hpp"
#include "src/game/Request/DesignationType.hpp"
#include "raylib.h"
#include <memory>
#include <vector>
#include <list>

namespace map {
    Grid::Grid(std::shared_ptr<game::State> gameState) {
      GameState = gameState;
      /*mapData =
      { 
        { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
        { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
        { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
        { 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
        { 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
        { 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
        { 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
        { 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
        { 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 3, 3, 3, 0, 0 },
        { 0, 0, 2, 2, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 3, 3, 3, 0, 0 },
        { 0, 0, 2, 2, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 3, 3, 3, 0, 0 },
        { 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 3, 3, 3, 0, 0 },
        { 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
        { 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
        { 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
        { 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
        { 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
        { 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
        { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
        { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
        { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }
      };*/
      astarPathing.setWorldSize({20, 20});
      astarPathing.setHeuristic(AStar::Heuristic::euclidean);
      astarPathing.setDiagonalMovement(true);
      int tileY = 0;
      for (auto const& i : mapData) {
        auto tileRow = std::vector<map::Tile>{};
        int tileX = 0;

        for (auto const& k : i) {
          Tile tile;
          AStar::Vec2i positionVector;
          positionVector.x = tileX;
          positionVector.y = tileY; 
          tile.positionVector = positionVector;

          if (k == 1) {
            tile.isWall = true;
            astarPathing.addCollision(tile.positionVector);
          } else if (k == 2) {
            tile.isStorage = true;
          } else if (k == 3) {
            Item::ItemIdentifier item;
            item.Family = "Resource";
            item.Order = "Wood";
            item.Type = "Maple";
            item.Form = "Tree";
            Item::ResourceFactory factory;
            auto tree = factory.Create(item);
            tile.InventoryContents->AddItem(tree);
            
            /*Inventory::Content content;
            content.Family = "Resource";
            content.Order = "Wood";
            tile.InventoryContents->AddContent(content);*/
            tile.isWood = true;
          }
          

          tileRow.push_back(tile);
          tileX = tileX + 1;
        }
        
        TileMap.push_back(tileRow);
        tileY = tileY + 1;
      };
      
    };

    Tile* Grid::FindNearest(int startX, int startY, Item::ItemIdentifier item) {
        //start from top left, go right, then down, then left, then up
        bool found = false;
        bool exceedMap = false;
        int distance = 1;

        std::list<Tile> tilesFound;
        std::vector<int> bounds; 
        tie(bounds, exceedMap) = expandSearch(startX, startY, distance);

        while (!found && !exceedMap) {
          //Might be able to do this with 1 for loop 
          for(int x = startX; x <= bounds[3]; x++) {
            if (TileMap[bounds[0]][x].InventoryContents->HasContent(item)) {
              tilesFound.push_back(TileMap[bounds[0]][x]);
              found = true;
            }
            if (TileMap[bounds[1]][x].InventoryContents->HasContent(item)) {
              tilesFound.push_back(TileMap[bounds[1]][x]);
              found = true;
            }
          }
          for (int y = startY; y <= bounds[1]; y++) {
            if (TileMap[y][bounds[3]].InventoryContents->HasContent(item)) {
              tilesFound.push_back(TileMap[y][bounds[3]]);
              found = true;
            }
            if (TileMap[y][bounds[2]].InventoryContents->HasContent(item)) {
              tilesFound.push_back(TileMap[y][bounds[2]]);
              found = true;
            }
          }

          if (!found) {
            distance = distance + 1;
            tie(bounds, exceedMap) = expandSearch(startX, startY, distance);
          }
          
        }

        if(!found) {
          return NULL;
        } else {
          auto res = tilesFound.front();
          return &TileMap[res.positionVector.y][res.positionVector.x];
        }
      };

      void Grid::UpdateMouseTracking(std::shared_ptr<Controller::Mouse> mouse) {
        MouseXIndex = mouse->MouseX / TileSize; 
        MouseYIndex = mouse->MouseY / TileSize;

        if (mouse->IsMouseLeftPressed) {
          if (!GameState->ActiveInterfaceClicked(mouse)) {
            unselectTiles();
          }
          
          
          if (*GameState->_Mode == game::Mode::EDIT 
          && *GameState->_AreaMode == game::AreaMode::SELECT 
          && !GameState->ActiveInterfaceClicked(mouse)) {
            for (auto& area : *Areas) {
              if(area->LookupTile(MouseXIndex, MouseYIndex)) {
                SelectedArea = area;
                break;
              }
              SelectedArea = nullptr;
                          
            }
          }
          else if (*GameState->_Mode == game::Mode::DESIGNATION && !GameState->ActiveInterfaceClicked(mouse)) {
            Item::ItemIdentifier itemIdentifier; 
            itemIdentifier.Family = "Resource";
            itemIdentifier.Order = "Wood";
            itemIdentifier.Form = "Tree";
            auto gridptr = std::make_shared<map::Grid>(*this);
            auto tile = std::make_shared<map::Tile>(TileMap[MouseYIndex][MouseXIndex]);
            for (auto& item : *tile->InventoryContents->Items) {
              if (item->Match(itemIdentifier, Item::MatchDegree::FORM)){
                game::Designation des(gridptr, game::DesignationType::CHOPTREE, tile);
           
                GameState->Designations->push_back(des);  
              }
            }
          }
          
          SelectedTileXIndex = MouseXIndex;
          SelectedTileYIndex = MouseYIndex;
        }

        if (mouse->IsMouseLeftDown) {
          detectClickAndDrag(mouse);
        }

        if (mouse->IsMouseLeftReleased) {
          if (IsClickAndDragActive) {
            selectTiles();
          }
          MouseDragXIndex = -1;
          MouseDragYIndex = -1;
          IsClickAndDragActive = false;
        }
      };

      void Grid::selectTiles() {
        for(int i = StartX; i <= EndX; i++) {
          for(int j = StartY; j <= EndY; j++) {
            if (i < 0 || i > TileMap.size() || j < 0 || j > TileMap[i].size()) {
              continue;
            } 
            auto tilePtr = std::make_shared<map::Tile>(TileMap[j][i]);
            SelectedTiles->push_back(tilePtr);

          }
        }
        //Make Area

        //TODO:: Block addition of tile to multiple rooms
        if (*GameState->_Mode == game::Mode::EDIT){ 
          if(*GameState->_AreaMode == game::AreaMode::NEW) {
            if(*GameState->_AreaType == game::AreaType::ROOM) {
              //TODO: Make ROoms
              auto area = std::shared_ptr<area::BaseArea>(new area::Storage());
              area->AddTiles(*SelectedTiles);
              Areas->push_back(area);

            } else if (*GameState->_AreaType == game::AreaType::STORAGE) {
              auto area = std::shared_ptr<area::Storage>(new area::Storage());
              area->AddTiles(*SelectedTiles);
              Areas->push_back(area);
            }
            *GameState->_AreaMode = game::AreaMode::SELECT;
          }
          if(*GameState->_AreaMode == game::AreaMode::EDIT && SelectedArea) {
            if(*GameState->_AreaEditMode == game::AreaEditMode::ADD) {
              SelectedArea->AddTiles(*SelectedTiles);
            } else if (*GameState->_AreaEditMode == game::AreaEditMode::REMOVE) {
              SelectedArea->RemoveTiles(*SelectedTiles);
              if (SelectedArea->Tiles->size() == 0) {
                //TODO:: Remove Area by ID
              }
            }
            unselectTiles();
          }
        }
      }

      void Grid::unselectTiles() {
        SelectedTiles->clear();
      }

      void Grid::detectClickAndDrag(std::shared_ptr<Controller::Mouse> mouse) {
        if (MouseXIndex != SelectedTileXIndex || MouseYIndex != SelectedTileYIndex ) {
          IsClickAndDragActive = true;
          MouseDragXIndex = MouseXIndex;
          MouseDragYIndex = MouseYIndex;
          
          if (MouseDragXIndex < SelectedTileXIndex) {
            StartX = MouseDragXIndex;
            EndX = SelectedTileXIndex;
          } else {
            StartX = SelectedTileXIndex;
            EndX = MouseDragXIndex;
          }

          if (MouseDragYIndex < SelectedTileYIndex) {
            StartY = MouseDragYIndex;
            EndY = SelectedTileYIndex;
          } else {
            StartY = SelectedTileYIndex;
            EndY = MouseDragYIndex;
          }
        }
      };

      std::tuple<std::vector<int>, bool> Grid::expandSearch(int startX, int startY, int distance) {
        std::vector<int> results;

        int mapIndexLimitY = TileMap.size() - 1;
        int mapIndexLimitX = TileMap[0].size() - 1;
        int top = startX - distance;
        bool exceedTop = false;
        bool exceedBottom = false;
        bool exceedLeft = false;
        bool exceedRight = false;
        if (top < 0) {
          top = 0;
          exceedTop = true;
        }
        results.push_back(top);

        int bottom = startX + distance;
        if (bottom > mapIndexLimitY) {
          bottom = mapIndexLimitY;
          exceedBottom = true;
        }
        results.push_back(bottom);

        int left = startY - distance;
        if (left < 0) {
          left = 0;
          exceedLeft = true;
        }
        results.push_back(left);

        int right = startY + distance;
        if (right > mapIndexLimitX) {
          right = mapIndexLimitX;
          exceedRight = true;
        }
        results.push_back(right);

        bool exceedMap = false;
        if (exceedTop && exceedBottom && exceedRight && exceedLeft) {
          exceedMap = true;
        }
        return {results, exceedMap};
      } 
}