#include "common/aoc.h"

namespace y2025::day02
{
  using InputType = std::vector<std::pair<int64_t, int64_t>>;
  REGISTER_DAY(2025, Day02, InputType, int64_t);

  REGISTER_TEST_EXAMPLE(2025, Day02, ExampleInput, 1, 1227775554);
  REGISTER_TEST(2025, Day02, Input, 1, 19219508902);
  REGISTER_TEST_EXAMPLE(2025, Day02, ExampleInput, 2, 4174379265);
  REGISTER_TEST(2025, Day02, Input, 2, 27180728081);

  READ_INPUT(input)
  {
    std::vector<std::pair<int64_t, int64_t>> vec;
    std::string str;
    while (std::getline(input, str, ','))
    {
      std::stringstream ss{str};
      int64_t i, j;
      ss >> i >> "-" >> j;
      vec.emplace_back(i, j);
    }
    return vec;
  }

  bool IsRepeating(int64_t n, int digits, int repeats)
  {
    if (digits % repeats != 0)
      return false;

    int64_t val = n;
    int64_t x = Helper::Pow10(digits / repeats);
    int64_t repeat = n % x;
    for (int i = 1; i < repeats; i++)
    {
      val /= x;
      if (val % x != repeat)
        return false;
    }
    return true;
  }

  bool IsInvalidP1(int64_t n)
  {
    return IsRepeating(n, Helper::GetNumberOfDigits(n), 2);
  }

  bool IsInvalidP2(int64_t n)
  {
    int digits = Helper::GetNumberOfDigits(n);
    for (int repeats = 2; repeats <= digits; repeats++)
    {
      if (IsRepeating(n, digits, repeats))
        return true;
    }
    return false;
  }

  OUTPUT1(input)
  {
    int64_t sum{0};
    for (const auto& pair : input)
    {
      for (int64_t i = pair.first; i <= pair.second; i++)
      {
        if (IsInvalidP1(i))
        {
          sum += i;
        }
      }
    }
    return sum;
  }

  OUTPUT2(input)
  {
    int64_t sum{0};
    for (const auto& pair : input)
    {
      for (int64_t i = pair.first; i <= pair.second; i++)
      {
        if (IsInvalidP2(i))
        {
          sum += i;
        }
      }
    }
    return sum;
  }
}
