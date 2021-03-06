#include "src/pathing/AStar.hpp"
#include "src/movement/Movement.hpp"
#include "src/units/Units.hpp"
#include "src/threading/ThreadManager.hpp"
#include "src/inventory/Inventory.hpp"
#include "src/map/Map.hpp"
#include "src/map/Generator.hpp"
#include "src/job/Jobs.hpp"
#include "src/job/JobManager.hpp"
#include "src/item/ItemIdentifier.hpp"
#include "src/item/Repository.hpp"
#include "src/item/Item.hpp"
#include "src/controller/Mouse.hpp"
#include "src/controller/Keyboard.hpp"
#include "src/debug/Text.hpp"
#include "src/area/Area.hpp"
#include "src/gui/ToggleButton.hpp"
#include "src/gui/EnumButton.hpp"
#include "src/gui/Button.hpp"
#include "src/gui/interface/GameInterface.hpp"
#include "src/game/Camera.hpp"
#include "src/game/State.hpp"
#include "src/database/Context.hpp"
#include "src/job/DeconstructItemTask.hpp"
#include "src/job/FindPathTask.hpp"
#include "src/job/FindItemMapTask.hpp"
#include "src/job/ITask.hpp"
#include "src/game/Request/Designation.hpp"
#include "src/game/Request/DesignationType.hpp"

#include <iostream>
#include <list>
#include <memory>

int main()
{
  
  auto GameState = std::shared_ptr<game::State>(new game::State);
  game::Camera camera;

  Threading::ManagerFactory threadManagerFactory;
  auto tm = threadManagerFactory.Create();
  std::clock_t start;
  double gameTime;
  start = std::clock();

  Debug::Text debugText;
  auto mouse = std::shared_ptr<Controller::Mouse>(new Controller::Mouse);
  auto keyboard = std::shared_ptr<Controller::Keyboard>(new Controller::Keyboard);

  int screenWidthDefault = 1280;
  int screenHeightDefault = 720;
  int screenWidth = screenWidthDefault;
  int screenHeight = screenHeightDefault;
  int tileSize = 20;
  
  // Default to fullscreen
  InitWindow(screenWidth, screenHeight, "Microcosim");
  
  //TODO: Create database once
  //database::Context db;
  //db.InitDB();
  
  int display = GetCurrentMonitor();
  //ToggleFullscreen();
  //No 4K gaming for nowx
  /*screenWidth = GetMonitorWidth(display);
  if (screenWidth > 1920) {
    screenWidth = 1920;
  }
  screenHeight = GetMonitorHeight(display);
  if (screenHeight > 1080) {
    screenHeight = 1080;
  }
  window.SetSize(screenWidth, screenHeight);*/
  //SetWindowSize(GetMonitorWidth(display), GetMonitorHeight(display));

  SetTargetFPS(60);

  map::Grid grid(GameState);
  map::Generator gen(8);
  grid.TileMap = gen.Generate();
  std::shared_ptr<map::Grid> gridPtr = std::make_shared<map::Grid>(grid);
  GameState->Grid = gridPtr;
  //game::Designation designation(gridPtr, game::DesignationType::CHOPTREE, std::make_shared<map::Tile>(gridPtr->TileMap[11][16]));
  //GameState->Designations->push_back(designation);

  Item::ItemIdentifier searchTargetObj;
  searchTargetObj.Family = "Resource";
  searchTargetObj.Order = "Wood";
  searchTargetObj.Type = "Maple";
  searchTargetObj.Form = "Tree";
  auto searchTarget = std::make_shared<Item::ItemIdentifier>(searchTargetObj);
  
  auto repo = Item::Repository(GameState);
  //auto res = repo.SelectOrders(searchTargetObj);

  std::list<std::shared_ptr<Units::Unit>> unitList;
  for (int i = 0; i < 1; i++)
  {
    auto unit = std::shared_ptr<Units::Unit>(new Units::Unit);
    unit->currentVector.x = 6;
    unit->currentVector.y = 10;
    unit->travelSpeedMPS = 1.00;
    unit->currentPathIndex = 0;
    unit->inventory = std::shared_ptr<Inventory::InventoryContents>(new Inventory::InventoryContents);
    
    unitList.push_back(unit);
  };
  GameState->Units = std::make_shared<std::list<std::shared_ptr<Units::Unit>>>(unitList);

  auto mov = std::shared_ptr<Movement::Generator>(new Movement::Generator);

  job::Manager jm(tm);

  // Main game loop
  std::string keysPressed = "";

  //GUI Elements
  gui::GameInterface gameInterface(GameState, gridPtr, screenWidth, screenHeight);

  while (!WindowShouldClose())
  { // Detect window close button or ESC key
    if (IsKeyPressed(KEY_F1)) {
      ToggleFullscreen();
      if (IsWindowFullscreen()) {
        //No 4K gaming for nowx
        screenWidth = GetMonitorWidth(display);
        if (screenWidth > 1920) {
          screenWidth = 1920;
        }
        screenHeight = GetMonitorHeight(display);
        if (screenHeight > 1080) {
          screenHeight = 1080;
        }
        SetWindowSize(screenWidth, screenHeight);

      } else {
        screenWidth = screenWidthDefault;
        screenHeight = screenHeightDefault;
        SetWindowSize(screenWidth, screenHeight);
      }
    }
    gameTime = (std::clock() - start) / (double)CLOCKS_PER_SEC;
    gameInterface.Draw(mouse);
    // Update
    //----------------------------------------------------------------------------------
    // Update your variables here
    //----------------------------------------------------------------------------------
    // Controller
    mouse->UpdateMouse();
    keyboard->Update();
    GameState->RunDesignations();
    
    // Grid
    gridPtr->UpdateMouseTracking(mouse);
    // Debug
    auto mouseDebugText = mouse->GetDebugText();
    debugText.AppendDebugList(mouseDebugText);

    // Check unit jobs
    for (auto &unit : unitList)
    {
      jm.RunJobTasks(unit);
      unit->check_and_move(mov, gameTime);
      //unit->CheckDropItem(GameState);
    }
    //TODO:: This is bad, should handle in unit loop
    GameState->CheckAreaItemDrop();
    mov->MoveAllAndClear(gameTime);


    if (keyboard->IsCameraLeftPressed) {
      camera.MoveLeft(1);
    }

    if (keyboard->IsCameraRightPressed) {
      camera.MoveRight(1);
    }

    if (keyboard->IsCameraUpPressed) {
      camera.MoveUp(1);
    }

    if (keyboard->IsCameraDownPressed) {
      camera.MoveDown(1);
    }

    // Draw
    //----------------------------------------------------------------------------------

    BeginDrawing();
    {
      ClearBackground(GRAY);
      // Map Loop
      //BeginMode2D(camera.Camera2D);
      int screenTileWidth = GetScreenWidth() / tileSize;
      int screenTileHeight = GetScreenHeight() / tileSize;
      for (int x = 0; x < screenTileWidth; x++) {
        for (int y = 0; y < screenTileHeight; y++) {
          int yIndex = y + camera.GameCamera->target.y;
          int xIndex = x + camera.GameCamera->target.x;
          if (yIndex < static_cast<int>(gridPtr->TileMap.size()) && xIndex < static_cast<int>(gridPtr->TileMap[y].size())){
            auto &tile = gridPtr->TileMap[yIndex][xIndex];

            if (tile.IsSelected)
            {
              DrawRectangle(x * tileSize, y * tileSize, tileSize, tileSize, LIME);
            }
            else if (tile.isStorage)
            {
              DrawRectangle(x * tileSize, y * tileSize, tileSize, tileSize, BLUE);
            }
            else if (tile.isWall)
            {
              DrawRectangle(x * tileSize, y * tileSize, tileSize, tileSize, BLACK);
            }
            else if (tile.InventoryContents->HasContent(searchTargetObj))
            {
              DrawRectangle(x * tileSize, y * tileSize, tileSize, tileSize, GREEN);
            }
            else
            {
              if (tile.Elevation > 255) {
                tile.Elevation = 255;
              }
              else if (tile.Elevation < 0) {
                tile.Elevation = 0;
              }
              auto co = Color{
                0, 0, (unsigned char)(tile.Elevation * 20), 255
              };
              DrawRectangle(x * tileSize, y * tileSize, tileSize, tileSize, co);
            }
            
          }

        }
      }


      // Unit Loop
      for (auto &unit : unitList)
      {
        if (unit->currentVector.y >= camera.GameCamera->target.y && unit->currentVector.x >= camera.GameCamera->target.x && unit->currentVector.y <= screenTileHeight && unit->currentVector.x <= screenTileWidth) {
          for (auto &pathVector : unit->path)
          {
            DrawRectangle(pathVector.x * tileSize, pathVector.y * tileSize, tileSize, tileSize, GRAY);
          }
          DrawRectangle(unit->currentVector.x * tileSize, unit->currentVector.y * tileSize, tileSize, tileSize, ORANGE);
          DrawRectangle(unit->targetVector.x * tileSize, unit->targetVector.y * tileSize, tileSize, tileSize, RED);
        }
      }

      for (auto area : *gridPtr->Areas)
      {
        for (auto tile : *area->Tiles)
        {
          if (tile.second->positionVector.y <= screenTileHeight && tile.second->positionVector.x <= screenTileWidth){
            DrawRectangle(tile.second->positionVector.x * gridPtr->TileSize, tile.second->positionVector.y * tileSize, gridPtr->TileSize, gridPtr->TileSize, PINK);
          }
        }
        if (gridPtr->SelectedArea) {
          for (auto tile : *gridPtr->SelectedArea->Tiles)
          {
            DrawRectangle(tile.second->positionVector.x * gridPtr->TileSize, tile.second->positionVector.y * tileSize, gridPtr->TileSize, gridPtr->TileSize, RED);
          }
        }
      }
      
      

      // UI Elements

      DrawRectangleLines(gridPtr->MouseXIndex * tileSize, gridPtr->MouseYIndex * tileSize, tileSize, tileSize, BLACK);

      /*if (grid.IsATileSelected) {
        DrawRectangle(grid.SelectedTileXIndex * grid.TileSize, grid.SelectedTileYIndex * grid.TileSize, grid.TileSize, grid.TileSize, YELLOW);
      }*/

      if (!gridPtr->SelectedTiles->empty())
      {
        for (auto tile : *gridPtr->SelectedTiles)
        {
          DrawRectangle(tile->positionVector.x * gridPtr->TileSize, tile->positionVector.y * tileSize, gridPtr->TileSize, gridPtr->TileSize, ORANGE);
        }
      }

      // Draw selection box
      if (gridPtr->IsClickAndDragActive)
      {
        for (int i = gridPtr->StartX; i <= gridPtr->EndX; i++)
        {
          DrawRectangle(i * gridPtr->TileSize, gridPtr->StartY * gridPtr->TileSize, gridPtr->TileSize, gridPtr->TileSize, LIGHTGRAY);
          if (gridPtr->StartY != gridPtr->EndY)
          {
            for (int j = gridPtr->StartY; j <= gridPtr->EndY; j++)
            {
              DrawRectangle(gridPtr->StartX * gridPtr->TileSize, j * tileSize, gridPtr->TileSize, gridPtr->TileSize, LIGHTGRAY);
              DrawRectangle(gridPtr->EndX * gridPtr->TileSize, j * tileSize, gridPtr->TileSize, gridPtr->TileSize, LIGHTGRAY);
            }
            DrawRectangle(i * gridPtr->TileSize, gridPtr->EndY * gridPtr->TileSize, gridPtr->TileSize, gridPtr->TileSize, LIGHTGRAY);
          }
        }
      }

      //EndMode2D();

      //Menu items

      gameInterface.Clear();


      debugText.PrintAndClear();
    }
    EndDrawing();
    //----------------------------------------------------------------------------------
  }

  return 0;
}