#include "src/map/Generator.hpp"
#include "src/map/Tile.hpp"
#include <math.h>
#include <vector>

namespace map {
  Generator::Generator(int size_n) {
    if (size_n < 4) {
      size_n = 4;
    }
    Size_n = size_n;
    SquareSideLength = pow(2, size_n) + 1;
    map::Tile tile;
    std::vector<map::Tile> row(SquareSideLength, tile);
    std::vector<std::vector<map::Tile>> mapData(SquareSideLength, row);
    for (int y = 0; y < SquareSideLength; y++) {
      for (int x = 0; x < SquareSideLength; x++) {
        mapData[y][x].positionVector.x = x;
        mapData[y][x].positionVector.y = y;
      }
    }
    MapData = mapData;
    MapData[0][0].Elevation = 1;
    MapData[0][SquareSideLength - 1].Elevation = 10;
    MapData[SquareSideLength - 1][0].Elevation = 5;
    MapData[SquareSideLength - 1][SquareSideLength - 1].Elevation = 10;
  }
  std::vector<std::vector<map::Tile>> Generator::Generate() {
    DiamondSquare(SquareSideLength - 1);
    return MapData;
  }

  void Generator::DiamondSquare(int stepSize) {
    while (stepSize > 1) {
      int half = stepSize / 2;
      if (half < 1) {
        break;
      }
      for (int y = half; y < SquareSideLength; y += stepSize) {
        for (int x = half; x < SquareSideLength; x += stepSize) {
          SquareStep(x % SquareSideLength, y % SquareSideLength, half);
        }
      }
      int col = 0;
      for (int x = 0; x < SquareSideLength; x += half)
      {
        col++;
        //Odd columns
        if (col % 2 == 1) {
          for (int y = half; y < SquareSideLength; y += stepSize) {
            DiamondStep(x % SquareSideLength, y % SquareSideLength, half);
          }
        }
        else {
          for (int y = 0; y < SquareSideLength; y += stepSize) {
            DiamondStep(x % SquareSideLength, y % SquareSideLength, half);
          }
        }
      }
      stepSize = stepSize / 2;
    }
  }

  void Generator::SquareStep(int x, int z, int reach) {
    int count = 0;
    float avg = 0.0f;
    if (x - reach >= 0 && z - reach >= 0)
    {
      avg += MapData[x - reach][z - reach].Elevation;
      count++;
    }
    if (x - reach >= 0 && z + reach < SquareSideLength)
    {
      avg += MapData[x - reach][z + reach].Elevation;
      count++;
    }
    if (x + reach < SquareSideLength && z - reach >= 0)
    {
      avg += MapData[x + reach][z - reach].Elevation;
      count++;
    }
    if (x + reach < SquareSideLength && z + reach < SquareSideLength)
    {
      avg += MapData[x + reach][z + reach].Elevation;
      count++;
    }
    avg += (rand() % (reach * 2)) - reach;
    avg /= count;
    MapData[x][z].Elevation = round(avg);
  }

  void Generator::DiamondStep(int x, int z, int reach) {
    int count = 0;
    float avg = 0.0f;
    if (x - reach >= 0)
    {
      avg += MapData[x - reach][z].Elevation;
      count++;
    }
    if (x + reach < SquareSideLength)
    {
      avg += MapData[x + reach][z].Elevation;
      count++;
    }
    if (z - reach >= 0)
    {
      avg += MapData[x][z - reach].Elevation;
      count++;
    }
    if (z + reach < SquareSideLength)
    {
      avg += MapData[x][z + reach].Elevation;
      count++;
    } 
    avg += (rand() % (reach * 2)) - reach;
    avg /= count;
    MapData[x][z].Elevation = round(avg);
  }
}