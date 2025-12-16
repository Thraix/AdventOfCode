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

  bool IsGoal(const std::vector<int>& joltageTarget)
  {
    for (auto joltage : joltageTarget)
    {
      if (joltage != 0)
        return false;
    }
    return true;
  }

  bool IsValid(const std::vector<int>& joltageTarget)
  {
    for (auto joltage : joltageTarget)
    {
      if (joltage < 0)
        return false;
    }
    return true;
  }

  std::vector<std::vector<int>> GetButtonsList(const Machine& machine,
                                               uint64_t parity,
                                               int button,
                                               const std::vector<int>& buttons)
  {
    std::vector<std::vector<int>> result;
    if (parity == 0)
    {
      result.emplace_back(buttons);
    }

    for (int i = button; i < machine.buttons.size(); i++)
    {
      uint64_t newParity = parity;
      for (auto b : machine.buttons[i])
      {
        newParity ^= 1 << b;
      }
      std::vector<int> newButtons = buttons;
      newButtons.emplace_back(i);
      std::vector<std::vector<int>> buttonsList = GetButtonsList(machine, newParity, i + 1, newButtons);
      for (const auto& validButtons : buttonsList)
      {
        result.emplace_back(validButtons);
      }
    }
    return result;
  }

  std::vector<std::vector<int>> GetButtonsList(const Machine& machine,
                                               uint64_t parity,
                                               std::map<uint64_t, std::vector<std::vector<int>>>& memoizationButtons)
  {
    auto it = memoizationButtons.find(parity);
    if (it != memoizationButtons.end())
      return it->second;

    auto paths = GetButtonsList(machine, parity, 0, {});

    memoizationButtons[parity] = paths;
    return paths;
  }

  std::vector<int> GetNewJoltage(const Machine& machine,
                                 const std::vector<int>& buttons,
                                 const std::vector<int>& joltage)
  {
    std::vector<int> newJoltage = joltage;
    for (auto b : buttons)
    {
      for (int index : machine.buttons[b])
      {
        newJoltage[index]--;
      }
    }
    for (auto& j : newJoltage)
    {
      j /= 2;
    }
    return newJoltage;
  }

  uint64_t GetParity(const std::vector<int>& joltage)
  {
    uint64_t parity{0};
    for (int i = 0; i < joltage.size(); i++)
    {
      parity |= (joltage[i] % 2 == 1) << i;
    }
    return parity;
  }

  int64_t Minimum(const Machine& machine,
                  const std::vector<int>& targetJoltage,
                  std::map<std::vector<int>, int64_t>& memoization,
                  std::map<uint64_t, std::vector<std::vector<int>>>& memoizationButtons)
  {
    if (IsGoal(targetJoltage))
      return 0;

    auto it = memoization.find(targetJoltage);
    if (it != memoization.end())
      return it->second;

    uint64_t parity = GetParity(targetJoltage);
    auto buttonsList = GetButtonsList(machine, parity, memoizationButtons);

    int64_t minimum = std::numeric_limits<int>::max();
    for (const auto& buttons : buttonsList)
    {
      std::vector<int> newJoltage = GetNewJoltage(machine, buttons, targetJoltage);
      if (!IsValid(newJoltage))
        continue;
      int64_t result = Minimum(machine, newJoltage, memoization, memoizationButtons);
      minimum = std::min(minimum, 2 * result + (int64_t)buttons.size());
    }
    memoization[targetJoltage] = minimum;
    return minimum;
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
    int64_t total = 0;
    for (auto machine : input)
    {
      std::map<std::vector<int>, int64_t> memoization;
      std::map<uint64_t, std::vector<std::vector<int>>> memoizationButtons;
      total += Minimum(machine, machine.joltage, memoization, memoizationButtons);
    }
    return total;
  }
}
