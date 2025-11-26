#include "common/aoc.h"

namespace y2021::day15
{

  int Heuristic(const Array2D<int>& array, const Index2D& index)
  {
    return std::abs(index.x - array.width + 1) && std::abs(index.y - array.height + 1);
  }

  std::vector<std::pair<int, Index2D>> Branch(const Array2D<int>& array, const Index2D& index)
  {
    Index2D indices[4]{{index.x - 1, index.y}, {index.x, index.y - 1}, {index.x + 1, index.y}, {index.x, index.y + 1}};
    std::vector<std::pair<int, Index2D>> moves;
    for (auto& index : indices)
    {
      if (array.IsInside(index))
        moves.emplace_back(std::pair<int, Index2D>{array[index], index});
    }
    return moves;
  }

  int Goal(const Array2D<int>& array, const Index2D& index)
  {
    return index.x == array.width - 1 && index.y == array.height - 1;
  }

  int Pathfinder(const Array2D<int>& array)
  {
    return Helper::AStar(array, Index2D{0, 0}, Heuristic, Branch, Goal);
  }

  REGISTER_DAY(2021, Day15, Array2D<int>, int);

  REGISTER_TEST_EXAMPLE(2021, Day15, ExampleInput, 1, 40);
  REGISTER_TEST(2021, Day15, Input, 1, 714);
  REGISTER_TEST_EXAMPLE(2021, Day15, ExampleInput, 2, 315);
  REGISTER_TEST(2021, Day15, Input, 2, 2948);

  READ_INPUT(input)
  {
    return Input::ReadDigitsAsArray2D(input);
  }

  OUTPUT1(input)
  {
    return Pathfinder(input);
  }

  OUTPUT2(input)
  {
    Array2D<int> array{input.width * 5, input.height * 5};
    Index2D index{0, 0};
    for (auto& val : array)
    {
      val = input.GetMod(index.x, index.y) + index.x / input.width + index.y / input.height;
      if (val >= 10)
        val = val % 10 + 1;
      array.Increment(index);
    }
    return Pathfinder(array);
  }
}
