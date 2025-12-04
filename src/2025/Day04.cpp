#include "common/aoc.h"

namespace y2025::day04
{
  using InputType = Array2D<char>;
  REGISTER_DAY(2025, Day04, InputType, int);

  REGISTER_TEST_EXAMPLE(2025, Day04, ExampleInput, 1, 13);
  REGISTER_TEST(2025, Day04, Input, 1, 1502);
  REGISTER_TEST_EXAMPLE(2025, Day04, ExampleInput, 2, 43);
  REGISTER_TEST(2025, Day04, Input, 2, 9083);

  READ_INPUT(input)
  {
    return Input::ReadArray2D(input);
  }

  OUTPUT1(input)
  {
    std::set<Index2D> toiletPapers;
    for (auto it = input.begin(); it != input.end(); it++)
    {
      if (input[it.index] != '@' || input.GetNeighbors('@', it.index.x, it.index.y, 1) >= 4)
        continue;

      toiletPapers.emplace(it.index);
    }
    return toiletPapers.size();
  }

  OUTPUT2(input)
  {
    Array2D<char> cpy = input;

    std::stack<Index2D> toCheck;
    for (auto it = cpy.begin(); it != cpy.end(); it++)
    {
      if (cpy[it.index] == '.' || cpy.GetNeighbors('@', it.index.x, it.index.y, 1) >= 4)
        continue;

      toCheck.emplace(it.index);
    }

    int removedToiletPapers = 0;
    while (!toCheck.empty())
    {
      Index2D top = toCheck.top();
      toCheck.pop();
      if (cpy[top] == '.' || cpy.GetNeighbors('@', top.x, top.y, 1) >= 4)
        continue;

      cpy[top] = '.';
      removedToiletPapers++;
      std::vector<Index2D> neighbors = cpy.GetNeighbors(top, true);
      for (auto neighbor : neighbors)
      {
        if (cpy[neighbor] == '@')
          toCheck.emplace(neighbor);
      }
    }
    return removedToiletPapers;
  }
}
