#include "common/aoc.h"

namespace y$1::day12
{
  REGISTER_DAY(2022, Day12, Array2D<char>, int);

  REGISTER_TEST_EXAMPLE(2022, Day12, ExampleInput, 1, 31);
  REGISTER_TEST(2022, Day12, Input, 1, 380);
  REGISTER_TEST_EXAMPLE(2022, Day12, ExampleInput, 2, 29);
  REGISTER_TEST(2022, Day12, Input, 2, 375);

  int GetElevation(const Array2D<char>& arr, const Index2D& index)
  {
    int elevation = 0;
    char value = arr.Get(index.x, index.y);
    if (value == 'S')
      elevation = 'a' - 'a';
    else if (value == 'E')
      elevation = 'z' - 'a';
    else
      elevation = value - 'a';
    return elevation;
  }

  std::vector<std::pair<int, Index2D>> Branch(const Array2D<char>& arr, Index2D index)
  {
    std::vector<std::pair<int, Index2D>> branches;
    int elevation = GetElevation(arr, index);
    std::vector<Index2D> neighbors = arr.GetNeighbors(index, false);
    for (auto& neighbor : neighbors)
    {
      int neighElevation = GetElevation(arr, neighbor);
      if ((neighElevation - 1 <= elevation))
        branches.emplace_back(1, neighbor);
    }
    return branches;
  }

  std::vector<std::pair<int, Index2D>> Branch2(const Array2D<char>& arr, Index2D index)
  {
    std::vector<std::pair<int, Index2D>> branches;
    int elevation = GetElevation(arr, index);
    std::vector<Index2D> neighbors = arr.GetNeighbors(index, false);
    for (auto& neighbor : neighbors)
    {
      int neighElevation = GetElevation(arr, neighbor);
      if (elevation - 1 <= neighElevation)
        branches.emplace_back(1, neighbor);
    }
    return branches;
  }

  bool Goal(const Array2D<char>& arr, Index2D index)
  {
    return arr.Get(index.x, index.y) == 'E';
  }

  bool Goal2(const Array2D<char>& arr, Index2D index)
  {
    return arr.Get(index.x, index.y) == 'a';
  }

  READ_INPUT(input)
  {
    return Input::ReadArray2D(input);
  }

  OUTPUT1(input)
  {
    Index2D pos;
    for (auto it = input.begin(); it != input.end(); it++)
    {
      if (*it == 'S')
        pos = it.index;
    }

    return Helper::Dijkstras(input, pos, Branch, Goal);
  }

  OUTPUT2(input)
  {
    Index2D pos;
    for (auto it = input.begin(); it != input.end(); it++)
    {
      if (*it == 'E')
        pos = it.index;
    }

    return Helper::Dijkstras(input, pos, Branch2, Goal2);
  }
}
