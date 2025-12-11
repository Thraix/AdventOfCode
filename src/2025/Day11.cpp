#include "common/aoc.h"

namespace y2025::day11
{
  using InputType = std::map<std::string, std::vector<std::string>>;
  REGISTER_DAY(2025, Day11, InputType, int64_t);

  REGISTER_TEST_EXAMPLE(2025, Day11, ExampleInput, 1, 8);
  REGISTER_TEST(2025, Day11, Input, 1, 613);
  REGISTER_TEST_EXAMPLE(2025, Day11, ExampleInput, 2, 2);
  REGISTER_TEST(2025, Day11, Input, 2, 372918445876116);

  READ_INPUT(input)
  {
    std::map<std::string, std::vector<std::string>> vec;
    std::string str;
    while (std::getline(input, str))
    {
      std::stringstream ss{str};
      int n;
      std::string str2;
      ss >> str2;
      str2.pop_back();
      std::string str3;

      std::vector<std::string> paths;
      while (ss >> str3)
      {
        paths.emplace_back(str3);
      }
      vec[str2] = paths;
    }
    return vec;
  }

  struct State
  {
    std::string current;
    bool fft;
    bool dac;

    bool operator<(const State& other) const
    {
      if (fft != other.fft)
        return fft < other.fft;
      if (dac != other.dac)
        return dac < other.dac;
      return current < other.current;
    }
  };

  int PathFind(const std::map<std::string, std::vector<std::string>>& paths, const std::string& current, int count)
  {
    if (current == "out")
      return 1;

    int validPaths = 0;
    for (auto& branch : paths.at(current))
    {
      validPaths += PathFind(paths, branch, count + 1);
    }
    return validPaths;
  }

  int64_t PathFind2(const std::map<std::string, std::vector<std::string>>& paths,
                    const State& currentState,
                    std::map<State, int64_t>& memoization)
  {
    if (currentState.current == "out")
    {
      if (currentState.fft && currentState.dac)
        return 1;
      return 0;
    }

    auto memIt = memoization.find(currentState);
    if (memIt != memoization.end())
      return memIt->second;

    int64_t validPaths = 0;
    for (auto& branch : paths.at(currentState.current))
    {
      bool fft = currentState.fft || branch == "fft";
      bool dac = currentState.dac || branch == "dac";
      validPaths += PathFind2(paths, State{branch, fft, dac}, memoization);
    }
    memoization[currentState] = validPaths;
    return validPaths;
  }

  OUTPUT1(input)
  {
    return PathFind(input, isExample ? "svr" : "you", 0);
  }

  OUTPUT2(input)
  {
    std::map<State, int64_t> memoization{};
    return PathFind2(input, State{"svr", false, false}, memoization);
  }
}
