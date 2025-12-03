#include "common/aoc.h"

namespace y2025::day03
{
  using InputType = std::vector<std::string>;
  REGISTER_DAY(2025, Day03, InputType, int64_t);

  REGISTER_TEST_EXAMPLE(2025, Day03, ExampleInput, 1, 357);
  REGISTER_TEST(2025, Day03, Input, 1, 17430);
  REGISTER_TEST_EXAMPLE(2025, Day03, ExampleInput, 2, 3121910778619);
  REGISTER_TEST(2025, Day03, Input, 2, 171975854269367);

  READ_INPUT(input)
  {
    std::vector<std::string> vec;
    std::string str;
    while (std::getline(input, str))
    {
      vec.emplace_back(str);
    }
    return vec;
  }

  template <size_t N>
  int64_t Joltage(const std::vector<std::string>& input)
  {
    int64_t sum = 0;

    for (const auto& line : input)
    {
      std::array<int, N> max{};
      std::array<int, N + 1> index{};
      for (int i = 0; i < max.size(); i++)
      {
        for (int j = index[i]; j <= line.size() - (max.size() - i); j++)
        {
          int num = line[j] - '0';
          if (num > max[i])
          {
            max[i] = num;
            index[i + 1] = j + 1;
          }
        }
      }

      int64_t val = 0;
      for (int i = 0; i < max.size(); i++)
      {
        val = val * 10 + max[i];
      }
      sum += val;
    }
    return sum;
  }

  OUTPUT1(input)
  {
    return Joltage<2>(input);
  }

  OUTPUT2(input)
  {
    return Joltage<12>(input);
  }
}
