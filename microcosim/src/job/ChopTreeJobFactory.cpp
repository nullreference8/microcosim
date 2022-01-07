#include "src/job/ChopTreeJobFactory.hpp"
#include "src/job/Jobs.hpp";
#include "src/item/ItemIdentifier.hpp"
#include "src/item/Item.hpp"
#include "src/job/DeconstructItemTask.hpp"
#include "src/job/FindPathTask.hpp"
#include "src/job/UnitSetTargetTileTask.hpp"
#include "src/map/Tile.hpp"
#include "src/map/Map.hpp"
#include "src/game/Request/Designation.hpp"
#include "src/units/Units.hpp"
namespace job {
  std::shared_ptr<job::Job> ChopTreeJobFactory::Create(std::shared_ptr<Map::Grid> grid, std::shared_ptr<std::list<std::shared_ptr<Units::Unit>>> units, std::shared_ptr<game::Designation> designation) {

    auto job = std::shared_ptr<job::Job>(new job::Job);
    auto identifier = std::shared_ptr<Item::ItemIdentifier>(new Item::ItemIdentifier);
    identifier->Family = "Resource";
    identifier->Order = "Wood";
    job::DeconstructItemTaskFactory dfact;
    auto task3 = dfact.Create(identifier, std::make_shared<Item::MatchDegree>(Item::MatchDegree::ORDER), grid, designation->AssignedUnit);
    job->Tasks.push_back(task3);
    job::FindPathTaskFactory ffact;
    auto task2 = ffact.Create(grid, designation->AssignedUnit);
    job->Tasks.push_back(task2);
    job::UnitSetTargetTileTaskFactory ufact;
    auto task = ufact.Create(designation->Tile, designation->AssignedUnit);
    job->Tasks.push_back(task);

    return job;
  }
}