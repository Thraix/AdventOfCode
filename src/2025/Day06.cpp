#include "common/aoc.h"

namespace y2025::day06
{
  struct Table
  {
    std::vector<std::string> lines;
    std::vector<char> operators;
  };

  using InputType = Table;
  REGISTER_DAY(2025, Day06, InputType, int64_t);

  REGISTER_TEST_EXAMPLE(2025, Day06, ExampleInput, 1, 4277556);
  REGISTER_TEST(2025, Day06, Input, 1, 6343365546996);
  REGISTER_TEST_EXAMPLE(2025, Day06, ExampleInput, 2, 3263827);
  REGISTER_TEST(2025, Day06, Input, 2, 11136895955912);

  READ_INPUT(input)
  {
    Table table;
    std::string str;
    while (std::getline(input, str))
    {
      if (str[0] == '*' || str[0] == '+')
      {
        std::stringstream ss{str};
        char c;
        while (ss >> c)
        {
          table.operators.emplace_back(c);
        }
      }
      else
        table.lines.emplace_back(str);
    }
    return table;
  }

  int64_t Calculate(const std::vector<std::vector<int64_t>>& numbers, const std::vector<char>& operators)
  {
    int64_t sum = 0;
    for (int i = 0; i < numbers.size(); i++)
    {
      int64_t total = numbers[i][0];
      for (int j = 1; j < numbers[i].size(); j++)
      {
        if (operators[i] == '+')
          total += numbers[i][j];
        else if (operators[i] == '*')
          total *= numbers[i][j];
      }
      sum += total;
    }
    return sum;
  }

  bool EmptyColumn(const std::vector<std::string>& lines, int col)
  {
    for (int row = 0; row < lines.size(); row++)
    {
      if (lines[row][col] != ' ')
        return false;
    }
    return true;
  }

  OUTPUT1(input)
  {
    std::vector<std::vector<int64_t>> numbers;
    numbers.resize(input.operators.size());
    for (int i = 0; i < input.lines.size(); i++)
    {
      std::stringstream ss{input.lines[i]};
      int n;
      int col = 0;
      while (ss >> n)
      {
        numbers[col].emplace_back(n);
        col++;
      }
    }
    return Calculate(numbers, input.operators);
  }

  OUTPUT2(input)
  {
    std::vector<std::vector<int64_t>> numbers;
    numbers.emplace_back();
    for (int col = 0; col < input.lines.front().size(); col++)
    {
      if (EmptyColumn(input.lines, col))
      {
        numbers.emplace_back();
        continue;
      }

      int number = 0;
      for (int row = 0; row < input.lines.size(); row++)
      {
        if (input.lines[row][col] != ' ')
        {
          number = number * 10 + input.lines[row][col] - '0';
        }
      }
      numbers.back().emplace_back(number);
    }
    return Calculate(numbers, input.operators);
  }
}
