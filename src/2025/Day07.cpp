#include "common/aoc.h"

namespace y2025::day07
{
  using InputType = Array2D<char>;
  REGISTER_DAY(2025, Day07, InputType, int64_t);

  REGISTER_TEST_EXAMPLE(2025, Day07, ExampleInput, 1, 21);
  REGISTER_TEST(2025, Day07, Input, 1, 1594);
  REGISTER_TEST_EXAMPLE(2025, Day07, ExampleInput, 2, 40);
  REGISTER_TEST(2025, Day07, Input, 2, 15650261281478);

  READ_INPUT(input)
  {
    return Input::ReadArray2D(input);
  }

  std::pair<int64_t, int64_t> Simulate(const Array2D<char>& grid)
  {
    std::pair<int64_t, int64_t> solution{0, 1};

    Index2D startPos = grid.Find('S');

    std::vector<int64_t> beamsRow{};
    beamsRow.resize(grid.width);
    beamsRow[startPos.x] = 1;

    for (int y = startPos.y; y < grid.height - 1; y++)
    {
      std::vector<int64_t> nextBeamRow{};
      nextBeamRow.resize(grid.width);

      for (int x = 0; x < grid.width; x++)
      {
        if (beamsRow[x] == 0)
          continue;

        if (grid.Get(x, y + 1) == '^')
        {
          nextBeamRow[x - 1] += beamsRow[x];
          nextBeamRow[x + 1] += beamsRow[x];
          solution.first++;
          solution.second += beamsRow[x];
        }
        else
        {
          nextBeamRow[x] += beamsRow[x];
        }
      }
      beamsRow = std::move(nextBeamRow);
    }
    return solution;
  }

  OUTPUT1(input)
  {
    return Simulate(input).first;
  }

  OUTPUT2(input)
  {
    return Simulate(input).second;
  }
}
