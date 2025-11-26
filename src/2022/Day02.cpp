#include "common/aoc.h"

namespace y$1::day02
{
  REGISTER_DAY(2022, Day02, std::vector<std::string>, int);

  REGISTER_TEST_EXAMPLE(2022, Day02, ExampleInput, 1, 15);
  REGISTER_TEST(2022, Day02, Input, 1, 13221);
  REGISTER_TEST_EXAMPLE(2022, Day02, ExampleInput, 2, 12);
  REGISTER_TEST(2022, Day02, Input, 2, 13131);

  READ_INPUT(input)
  {
    std::string str;
    std::vector<std::string> hands;
    while (std::getline(input, str))
    {
      hands.emplace_back(str);
    }
    return hands;
  }

  OUTPUT1(input)
  {
    int sum = 0;
    for (auto hand : input)
    {
      int handPoints = hand[2] - 'X' + 1;
      int outcomePoints = (((hand[2] - 'X') - (hand[0] - 'A') + 4) % 3) * 3;
      sum += handPoints + outcomePoints;
    }
    return sum;
  }

  OUTPUT2(input)
  {
    int sum = 0;
    for (auto& hand : input)
    {
      int handPoints = ((hand[2] - 'A') + (hand[0] - 'X' - 1) + 3) % 3 + 1;
      int outcomePoints = (hand[2] - 'X') * 3;
      sum += handPoints + outcomePoints;
    }
    return sum;
  }
}
