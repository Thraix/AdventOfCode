#include "common/aoc.h"

namespace y2025::day04
{
  using InputType = std::vector<int>;
  REGISTER_DAY(2025, Day04, InputType, int);

  REGISTER_TEST_EXAMPLE(2025, Day04, ExampleInput, 1, 0);
  REGISTER_TEST(2025, Day04, Input, 1, 0);
  REGISTER_TEST_EXAMPLE(2025, Day04, ExampleInput, 2, 0);
  REGISTER_TEST(2025, Day04, Input, 2, 0);

  READ_INPUT(input)
  {
    std::vector<int> vec;
    std::string str;
    while (std::getline(input, str))
    {
      std::stringstream ss{str};
      int n;
      ss >> n;
      vec.emplace_back(n);
    }
    return vec;
  }

  OUTPUT1(input)
  {
    return 0;
  }

  OUTPUT2(input)
  {
    return 0;
  }
}
