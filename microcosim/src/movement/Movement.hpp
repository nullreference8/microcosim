#ifndef MOVEMENT_HPP
#define MOVEMENT_HPP
#include <vector>
namespace Units {
  class Unit;
}
namespace Movement {
  using UnitsToUpdate = std::vector<Units::Unit*>;
  class Generator { 
    private:
      UnitsToUpdate unitsToUpdate = UnitsToUpdate{};
    public: 
      void AddUnit(Units::Unit* unit);
      void MoveAllAndClear(double gameTime);
  };
}
#endif