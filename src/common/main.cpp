#include <chrono>
#include <iostream>
#include <vector>

#include "aoc.h"

aoc::Registry* aoc::Registry::GetInstance()
{
  static aoc::Registry* instance = new aoc::Registry();
  return instance;
}

struct Args
{
  std::string testRegex{""};
  bool stopIfFailed{false};

  friend std::ostream& operator<<(std::ostream& os, const Args& args)
  {
    return os << "regex=" << args.testRegex << "\nstopIfFailed=" << (args.stopIfFailed ? "true" : "false");
  }
};

Args ParseArgs(const std::vector<std::string>& arguments)
{
  Args args;
  for (const std::string& argument : arguments)
  {
    if (Helper::StartsWith(argument, "--stop-if-failed"))
    {
      args.stopIfFailed = true;
    }
    else if (Helper::StartsWith(argument, "--filter="))
    {
      args.testRegex = std::string(argument).substr(sizeof("--filter=") - 1);
    }
    else
    {
      std::cout << "Unknown argument: " << argument << std::endl;
    }
  }
  return args;
}

std::vector<std::string> ReadArgs(int argc, char** argv)
{
  std::vector<std::string> arguments;
  for (int i = 1; i < argc; i++)
  {
    arguments.emplace_back(argv[i]);
  }

  if (arguments.empty())
  {
    std::ifstream inputStream{"config.txt"};
    if (inputStream.is_open())
    {
      std::string str;
      while (inputStream >> str)
      {
        arguments.emplace_back(str);
      }
    }
  }
  return arguments;
}

int main(int argc, char** argv)
{
  Args args = ParseArgs(ReadArgs(argc, argv));
  std::regex regex{args.testRegex};
  Timer totalTimer;
  int passed = 0;
  int skipped = 0;
  bool stopped = false;
  for (const auto& day : aoc::Registry::GetDays())
  {
    if (!std::regex_search(day->GetName(), regex) || stopped)
    {
      skipped++;
      continue;
    }

    std::cout << TERM_GREEN << "[ RUN     ] " << TERM_CLEAR << day->GetName() << std::endl;
    Timer timer;
    bool res = day->AocRunTestCases();
    timer.Stop();

    if (res)
    {
      std::cout << TERM_GREEN << "[=========] " << TERM_CLEAR << std::endl;
      std::cout << TERM_GREEN << "[      OK ] " << TERM_CLEAR << day->GetName() << " Took: " << timer.Elapsed() << "s"
                << std::endl;
      passed++;
    }
    else
    {
      std::cout << TERM_RED << "[=========] " << TERM_CLEAR << std::endl;
      std::cout << TERM_RED << "[  FAILED ] " << TERM_CLEAR << day->GetName() << std::endl;
      if (args.stopIfFailed)
      {
        stopped = true;
      }
    }
    std::cout << std::endl;
  }
  totalTimer.Stop();

  if (passed + skipped != aoc::Registry::GetDays().size())
  {
    std::cout << std::endl
              << TERM_RED << "[  FAILED ] " << TERM_CLEAR << passed << "/" << aoc::Registry::GetDays().size() - skipped
              << " days passed (" << skipped << " skipped) in " << totalTimer.Elapsed() << "s" << std::endl;
    return 1;
  }
  else
  {
    std::cout << std::endl
              << TERM_GREEN << "[  PASSED ] " << TERM_CLEAR << "All days passed (" << skipped << " skipped) in "
              << totalTimer.Elapsed() << "s" << std::endl;
    return 0;
  }
}
