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
  REGISTER_TEST(2025, Day10, Input, 2, 0);

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

  int Presses(
    const Machine& machine, std::vector<bool>& currentLights, std::vector<bool>& currentPresses, int count, int button)
  {
    if (machine.lights == currentLights)
    {
      return count;
    }

    int minSolution = machine.buttons.size() + 1;
    for (int i = button; i < machine.buttons.size(); i++)
    {
      if (currentPresses[i])
        continue;

      std::vector<bool> cpyPresses = currentPresses;
      cpyPresses[i] = true;
      std::vector<bool> cpyLights = currentLights;
      for (auto b : machine.buttons[i])
      {
        cpyLights[b] = !cpyLights[b];
      }
      int solution = Presses(machine, cpyLights, cpyPresses, count + 1, i + 1);
      minSolution = std::min(minSolution, solution);
    }
    return minSolution;
  }

  bool AnyAbove(const std::vector<int>& target, const std::vector<int>& current)
  {
    for (auto i = 0; i < target.size(); i++)
    {
      if (current[i] > target[i])
        return true;
    }
    return false;
  }

  int Presses2(
    const Machine& machine, std::vector<int>& currentLights, std::vector<int>& currentPresses, int count, int button)
  {
    if (machine.joltage == currentLights)
    {
      std::cout << currentPresses << std::endl;
      std::cout << currentLights << std::endl;
      std::cout << count << std::endl << std::endl;
      return count;
    }

    int minSolution = std::numeric_limits<int>::max();
    for (int i = button; i < machine.buttons.size(); i++)
    {
      std::vector<int> cpyPresses = currentPresses;
      std::vector<int> cpyLights = currentLights;
      int n = 1;
      while (!AnyAbove(machine.joltage, cpyLights))
      {
        for (auto b : machine.buttons[i])
        {
          cpyLights[b]++;
        }
        cpyPresses[i]++;
        int solution = Presses2(machine, cpyLights, cpyPresses, count + n, i + 1);
        minSolution = std::min(minSolution, solution);
        n++;
      }
    }
    return minSolution;
  }

  OUTPUT1(input)
  {
    int total = 0;
    for (auto& machine : input)
    {
      std::vector<bool> lights(machine.lights.size());
      std::vector<bool> presses(machine.buttons.size());
      int press = Presses(machine, lights, presses, 0, 0);
      total += press;
    }
    return total;
  }

  OUTPUT2(input)
  {
    int total = 0;
    for (auto& machine : input)
    {
      std::vector<int> lights(machine.joltage.size());
      std::vector<int> presses(machine.buttons.size());
      int press = Presses2(machine, lights, presses, 0, 0);
      std::cout << std::endl;
      total += press;
    }
    return total;
  }
}
