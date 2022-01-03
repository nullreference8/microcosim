#include "src/pathing/AStar.hpp"
#include "src/movement/Movement.hpp"
#include "src/units/Units.hpp"
#include "src/threading/ThreadManager.hpp"
#include "src/inventory/Inventory.hpp"
#include "src/map/Map.hpp"
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

  Map::Grid grid(GameState);
  std::shared_ptr<Map::Grid> gridPtr = std::make_shared<Map::Grid>(grid);

  Item::ItemIdentifier searchTargetObj;
  searchTargetObj.Family = "Resource";
  searchTargetObj.Order = "Wood";
  searchTargetObj.Type = "Maple";
  auto searchTarget = std::make_shared<Item::ItemIdentifier>(searchTargetObj);
  
  auto repo = Item::Repository(GameState);
  auto res = repo.SelectOrders(searchTargetObj);

  auto unitList = std::shared_ptr<Units::UnitList>(new Units::UnitList);
  for (int i = 0; i < 1; i++)
  {
    auto unit = std::shared_ptr<Units::Unit>(new Units::Unit);
    unit->currentVector.x = 6;
    unit->currentVector.y = 10;
    unit->travelSpeedMPS = 1.00;
    unit->currentPathIndex = 0;
    unit->inventory = std::shared_ptr<Inventory::InventoryContents>(new Inventory::InventoryContents);
    auto job = std::shared_ptr<job::Job>(new job::Job);
    job::TaskRequest taskRequest3;
    taskRequest3.Name = "RemoveItem";
    taskRequest3.Grid = gridPtr;
    taskRequest3.Identifier = searchTarget;
    taskRequest3.Degree = std::make_shared<Item::MatchDegree>(Item::MatchDegree::ORDER);
    auto identifier = std::shared_ptr<Item::ItemIdentifier>(new Item::ItemIdentifier);
    identifier->Family = "Resource";
    identifier->Order = "Wood";
    taskRequest3.Identifier = identifier;
    job->TaskRequests.push_back(taskRequest3);
    job::TaskRequest taskRequest2;
    taskRequest2.Name = "FindPath";
    taskRequest2.Grid = gridPtr;
    job->TaskRequests.push_back(taskRequest2);
    job::TaskRequest taskRequest;
    taskRequest.Name = "FindContent";
    taskRequest.Identifier = searchTarget;
    taskRequest.Grid = gridPtr;
    job->TaskRequests.push_back(taskRequest);
    unit->jobs.push_back(job);
    unitList->push_back(unit);
  };

  auto mov = std::shared_ptr<Movement::Generator>(new Movement::Generator);

  job::ManagerFactory factory;
  auto jm = factory.Create(tm);

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
    
    // Grid
    gridPtr->UpdateMouseTracking(mouse);
    // Debug
    auto mouseDebugText = mouse->GetDebugText();
    debugText.AppendDebugList(mouseDebugText);

    // Check unit jobs
    for (auto &unit : *unitList)
    {
      jm->RunJobTasks(unit);
      unit->check_and_move(mov, gameTime);
    }
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
      for (int x = camera.GameCamera->target.x; x < screenTileWidth; x++) {
        for (int y = camera.GameCamera->target.y; y < screenTileHeight; y++) {
          if (y < static_cast<int>(gridPtr->tileMap.size()) && x < static_cast<int>(gridPtr->tileMap[y].size())){
            auto &tile = gridPtr->tileMap[y][x];
            if (tile.IsSelected)
            {
              DrawRectangle(tile.positionVector.x * tileSize, tile.positionVector.y * tileSize, tileSize, tileSize, LIME);
            }
            else if (tile.isStorage)
            {
              DrawRectangle(tile.positionVector.x * tileSize, tile.positionVector.y * tileSize, tileSize, tileSize, BLUE);
            }
            else if (tile.isWall)
            {
              DrawRectangle(tile.positionVector.x * tileSize, tile.positionVector.y * tileSize, tileSize, tileSize, BLACK);
            }
            else if (tile.InventoryContents->HasContent(searchTargetObj))
            {
              DrawRectangle(tile.positionVector.x * tileSize, tile.positionVector.y * tileSize, tileSize, tileSize, GREEN);
            }
            else
            {
              DrawRectangle(tile.positionVector.x * tileSize, tile.positionVector.y * tileSize, tileSize, tileSize, RAYWHITE);
            }
            
          }

        }
      }


      // Unit Loop
      for (auto &unit : *unitList)
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