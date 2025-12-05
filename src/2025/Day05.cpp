#include "common/aoc.h"

namespace y2025::day05
{
  using Range = std::pair<int64_t, int64_t>;

  struct Input
  {
    std::vector<Range> ranges;
    std::vector<int64_t> ingredients;
  };

  using InputType = Input;
  REGISTER_DAY(2025, Day05, InputType, int64_t);

  REGISTER_TEST_EXAMPLE(2025, Day05, ExampleInput, 1, 3);
  REGISTER_TEST(2025, Day05, Input, 1, 848);
  REGISTER_TEST_EXAMPLE(2025, Day05, ExampleInput, 2, 14);
  REGISTER_TEST(2025, Day05, Input, 2, 334714395325710);

  READ_INPUT(input)
  {
    Input i;
    std::string str;
    while (std::getline(input, str))
    {
      if (str.empty())
        break;
      std::stringstream ss{str};
      int64_t n1, n2;
      ss >> n1 >> "-" >> n2;
      i.ranges.emplace_back(n1, n2);
    }

    while (std::getline(input, str))
    {
      std::stringstream ss{str};
      int64_t n;
      ss >> n;
      i.ingredients.emplace_back(n);
    }

    return i;
  }

  int64_t CalcNonOverlap(const Range& range,
                         const std::vector<Range>& overlaps,
                         int overlapLowerLimit,
                         int overlapUpperLimit)
  {
    if (range.second < range.first)
      return 0;

    for (int i = overlapLowerLimit; i <= overlapUpperLimit; i++)
    {
      const Range& overlap = overlaps[i];
      if (range.second >= overlap.first && range.first <= overlap.second)
      {
        Range leftRange{range.first, std::min(overlap.first - 1, range.second)};
        Range rightRangne{std::max(overlap.second + 1, range.first), range.second};
        return CalcNonOverlap(leftRange, overlaps, i + 1, overlapUpperLimit) +
               CalcNonOverlap(rightRangne, overlaps, i + 1, overlapUpperLimit);
      }
    }

    // No overlap, return entire range
    return range.second - range.first + 1;
  }

  OUTPUT1(input)
  {
    int fresh = 0;
    for (auto ing : input.ingredients)
    {
      for (auto& range : input.ranges)
      {
        if (ing >= range.first && ing <= range.second)
        {
          fresh++;
          break;
        }
      }
    }
    return fresh;
  }

  OUTPUT2(input)
  {
    int64_t sum = 0;
    for (int i = 0; i < input.ranges.size(); i++)
    {
      sum += CalcNonOverlap(input.ranges[i], input.ranges, 0, i - 1);
    }

    return sum;
  }
}
