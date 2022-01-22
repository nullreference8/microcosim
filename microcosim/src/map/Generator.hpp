#ifndef MAP_GENERATOR_HPP
#define MAP_GENERATOR_HPP
#include <vector>

namespace map {
  class Tile;
  class Generator {
  public:
    Generator(int size_n);
    int SquareSideLength;
    int Size_n;
    std::vector<std::vector<map::Tile>> MapData;
    std::vector<std::vector<map::Tile>> Generate();
    void DiamondSquare(int size);
    void SquareStep(int x, int z, int reach);
    void DiamondStep(int x, int z, int reach);
  };
}
#endif