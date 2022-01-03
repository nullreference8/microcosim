#ifndef UNITS_HPP
#define UNITS_HPP

#include "src/pathing/AStar.hpp"
#include "src/job/Jobs.hpp"
#include "src/job/ITask.hpp"
#include <list>
#include <memory>

struct Color;

namespace Jobs {
  class Job;
  class ITask;
}

namespace Inventory {
  class InventoryContents;
}

namespace Movement {
  class Generator;
}

namespace Units {
  class Unit {
    public:
      Unit();
      std::shared_ptr<Color> color; 
      bool isHoldingWood = false;
      std::list<AStar::Vec2i> targetVectorSolutions = std::list<AStar::Vec2i>{};
      AStar::Vec2i targetVector = AStar::Vec2i{};
      AStar::Vec2i currentVector = AStar::Vec2i{};
      double nextMoveTime;
      double travelSpeedMPS;
      AStar::CoordinateList path = AStar::CoordinateList {};
      int currentPathIndex;
      AStar::Generator* generator;
      std::shared_ptr<Inventory::InventoryContents> inventory;
      std::vector<std::shared_ptr<job::Job>> jobs;
      std::shared_ptr<job::ITask> currentTask;
      //Jobs::ITask* currentTask;
      void find_path();
      void set_next_move_time(double gameTime);
      void check_and_move(std::shared_ptr<Movement::Generator> mov, double gameTime);
  };
  using UnitList = std::list<std::shared_ptr<Units::Unit>>;
}
#endif