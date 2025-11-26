#include "common/aoc.h"

namespace y$1::day01
{
  REGISTER_DAY(2022, Day01, std::set<int>, int);

  REGISTER_TEST_EXAMPLE(2022, Day01, ExampleInput, 1, 24000);
  REGISTER_TEST(2022, Day01, Input, 1, 68292);
  REGISTER_TEST_EXAMPLE(2022, Day01, ExampleInput, 2, 45000);
  REGISTER_TEST(2022, Day01, Input, 2, 203203);

  READ_INPUT(input)
  {
    std::string str;
    std::set<int> elfs;
    int sum = 0;
    while (std::getline(input, str))
    {
      if (str.empty())
      {
        elfs.emplace(sum);
        sum = 0;
        continue;
      }
      sum += std::stoll(str);
    }
    if (sum != 0)
      elfs.emplace(sum);
    return elfs;
  }

  OUTPUT1(input)
  {
    return Helper::Max(input);
  }

  OUTPUT2(input)
  {
    int sum = 0;
    int i = 0;
    for (auto it = input.rbegin(); it != input.rend(); it++)
    {
      sum += *it;
      i++;
      if (i == 3)
        break;
    }

    return sum;
  }
}
