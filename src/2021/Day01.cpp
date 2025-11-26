#include "common/aoc.h"

namespace y2021::day01
{
  REGISTER_DAY(2021, Day01, std::vector<int>, int);

  REGISTER_TEST_EXAMPLE(2021, Day01, ExampleInput, 1, 7);
  REGISTER_TEST(2021, Day01, Input, 1, 1722);
  REGISTER_TEST_EXAMPLE(2021, Day01, ExampleInput, 2, 5);
  REGISTER_TEST(2021, Day01, Input, 2, 1748);

  READ_INPUT(input)
  {
    return Input::ReadInts(input);
  }

  OUTPUT1(input)
  {
    int count = 0;
    for (size_t i = 0; i < input.size() - 1; i++)
    {
      if (input[i] < input[i + 1])
        count++;
    }
    return count;
  }

  OUTPUT2(input)
  {
    int count = 0;
    for (size_t i = 0; i < input.size() - 3; i++)
    {
      if (input[i] + input[i + 1] + input[i + 2] < input[i + 1] + input[i + 2] + input[i + 3])
        count++;
    }
    return count;
  }
}
