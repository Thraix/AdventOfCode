#include "common/aoc.h"

namespace y2025::day01
{
  using InputType = std::vector<int>;
  REGISTER_DAY(2025, Day01, InputType, int);

  REGISTER_TEST_EXAMPLE(2025, Day01, ExampleInput, 1, 3);
  REGISTER_TEST(2025, Day01, Input, 1, 1152);
  REGISTER_TEST_EXAMPLE(2025, Day01, ExampleInput, 2, 6);
  REGISTER_TEST(2025, Day01, Input, 2, 6671);

  void test(int i)
  {
  }

  READ_INPUT(input)
  {
    std::vector<int> vec;
    std::string str;
    while (std::getline(input, str))
    {
      std::stringstream ss{str};
      char c;
      int n;
      ss >> c >> n;
      if (c == 'L')
        n = -n;
      vec.emplace_back(n);
    }
    return vec;
  }

  OUTPUT1(input)
  {
    int dial = 50;
    int zeros = 0;
    for (int n : input)
    {
      dial += n;
      dial %= 100;
      dial = (dial + 100) % 100;
      if (dial == 0)
        zeros++;
    }
    return zeros;
  }

  OUTPUT2(input)
  {
    int dial = 50;
    int zeros = 0;
    for (int n : input)
    {
      for (int i = 0; i < std::abs(n); i++)
      {
        dial += Helper::Sign(n);
        dial = ((dial % 100) + 100) % 100;
        if (dial == 0)
        {
          zeros++;
        }
      }
    }
    return zeros;
  }

}
