#include "common/aoc.h"

namespace y2025::day12
{
  struct Area
  {
    int width;
    int height;
    std::vector<int> presents;
  };

  struct Input2
  {
    std::vector<Array2D<char>> boxes;
    std::vector<Area> areas;
  };

  using InputType = Input2;
  REGISTER_DAY(2025, Day12, InputType, int);

  // REGISTER_TEST_EXAMPLE(2025, Day12, ExampleInput, 1, 2);
  REGISTER_TEST(2025, Day12, Input, 1, 422);
  REGISTER_TEST_EXAMPLE(2025, Day12, ExampleInput, 2, 0);
  REGISTER_TEST(2025, Day12, Input, 2, 0);

  READ_INPUT(input)
  {
    Input2 i;
    std::string str;
    while (std::getline(input, str))
    {
      if (str.empty())
        continue;
      if (str[1] == ':')
      {
        i.boxes.emplace_back(Input::ReadArray2D(input));
      }
      else
      {
        Area area;
        std::stringstream ss{str};
        ss >> area.width >> "x" >> area.height >> ":";
        int n;
        while (ss >> n)
        {
          area.presents.emplace_back(n);
        }
        i.areas.emplace_back(area);
      }
    }
    return i;
  }

  OUTPUT1(input)
  {
    int total = 0;
    for (auto& area : input.areas)
    {
      int a = area.width * area.height;
      int sum = 0;
      for (int i = 0; i < input.boxes.size(); i++)
      {
        sum += input.boxes[i].Count('#') * area.presents[i];
      }
      if (sum <= a)
        total++;
    }
    return total;
  }

  OUTPUT2(input)
  {
    return 0;
  }
}
