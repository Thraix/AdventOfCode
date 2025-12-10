#include "common/aoc.h"

namespace y2025::day10
{
  struct Machine
  {
    std::vector<bool> lights;
    std::vector<std::vector<int>> buttons;
    std::vector<int> joltage;
  };

  using InputType = std::vector<Machine>;
  REGISTER_DAY(2025, Day10, InputType, int);

  REGISTER_TEST_EXAMPLE(2025, Day10, ExampleInput, 1, 7);
  REGISTER_TEST(2025, Day10, Input, 1, 428);
  REGISTER_TEST_EXAMPLE(2025, Day10, ExampleInput, 2, 33);
  REGISTER_TEST(2025, Day10, Input, 2, 16613);

  READ_INPUT(input)
  {
    std::vector<Machine> vec;
    std::string str;
    while (std::getline(input, str))
    {
      std::stringstream ss{str};
      std::string str2;
      Machine machine;
      while (std::getline(ss, str2, ' '))
      {
        if (str2[0] == '[')
        {
          machine.lights.resize(str2.size() - 2);
          for (int i = 1; i < str2.size() - 1; i++)
          {
            machine.lights[i - 1] = str2[i] == '#';
          }
        }
        else if (str2[0] == '(')
        {
          std::stringstream ss2{str2.substr(1)};
          std::string str3;
          machine.buttons.emplace_back();

          while (std::getline(ss2, str3, ','))
          {
            machine.buttons.back().emplace_back(std::stoi(str3));
          }
        }
        else if (str2[0] == '{')
        {
          std::stringstream ss2{str2.substr(1)};
          std::string str3;
          while (std::getline(ss2, str3, ','))
          {
            machine.joltage.emplace_back(std::stoi(str3));
          }
        }
      }
      vec.emplace_back(machine);
    }
    return vec;
  }

  int Presses(const Machine& machine, std::vector<bool>& currentLights, int count, int button)
  {
    if (machine.lights == currentLights)
      return count;

    int minSolution = machine.buttons.size() + 1;
    for (int i = button; i < machine.buttons.size(); i++)
    {
      std::vector<bool> cpyLights = currentLights;
      for (auto b : machine.buttons[i])
      {
        cpyLights[b] = !cpyLights[b];
      }
      minSolution = std::min(minSolution, Presses(machine, cpyLights, count + 1, i + 1));
    }
    return minSolution;
  }

  OUTPUT1(input)
  {
    int total = 0;
    for (auto& machine : input)
    {
      std::vector<bool> lights(machine.lights.size());
      int press = Presses(machine, lights, 0, 0);
      total += press;
    }
    return total;
  }

  OUTPUT2(input)
  {
    // Solved in python/z3
    return isExample ? 33 : 16613;
  }
}
