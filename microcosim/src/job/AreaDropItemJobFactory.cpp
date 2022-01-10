#include "src/job/AreaDropItemJobFactory.hpp"
#include "src/job/Jobs.hpp";
#include "src/item/ItemIdentifier.hpp"
#include "src/item/Item.hpp"
#include "src/job/FindPathTask.hpp"
#include "src/job/UnitSetTargetTileTask.hpp"
#include "src/job/DropItemTask.hpp"
#include "src/map/Tile.hpp"
#include "src/game/State.hpp"
#include "src/area/Storage.hpp"
#include "src/units/Units.hpp"
namespace job {
  std::shared_ptr<job::Job> AreaDropItemJobFactory::Create(std::shared_ptr<game::State> gameState, std::shared_ptr<area::Storage> storage, std::shared_ptr<Units::Unit> unit, std::shared_ptr<Item::ItemIdentifier> item) {

    auto job = std::shared_ptr<job::Job>(new job::Job);
    job::DropItemTaskFactory dfact;
    auto task3 = dfact.Create(gameState, unit, item);
    job->Tasks.push_back(task3);
    job::FindPathTaskFactory ffact;
    auto task2 = ffact.Create(gameState, unit);
    job->Tasks.push_back(task2);
    job::UnitSetTargetTileTaskFactory ufact;
    auto tile = storage->GetOpenTile();
    auto task = ufact.Create(tile, unit);
    job->Tasks.push_back(task);

    return job;
  }
}