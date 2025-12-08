#include "common/aoc.h"

namespace y2025::day08
{
  using InputType = std::vector<Index3D>;
  REGISTER_DAY(2025, Day08, InputType, int64_t);

  REGISTER_TEST_EXAMPLE(2025, Day08, ExampleInput, 1, 40);
  REGISTER_TEST(2025, Day08, Input, 1, 122636);
  REGISTER_TEST_EXAMPLE(2025, Day08, ExampleInput, 2, 25272);
  REGISTER_TEST(2025, Day08, Input, 2, 9271575747);

  READ_INPUT(input)
  {
    std::vector<Index3D> vec;
    std::string str;
    while (std::getline(input, str))
    {
      std::stringstream ss{str};
      int n;
      Index3D index;
      ss >> index.x >> "," >> index.y >> "," >> index.z;
      vec.emplace_back(index);
    }
    return vec;
  }

  std::multimap<int64_t, std::pair<Index3D, Index3D>> CalculateDistances(const std::vector<Index3D>& indices)
  {
    std::multimap<int64_t, std::pair<Index3D, Index3D>> distances;
    for (int i = 0; i < indices.size(); i++)
    {
      for (int j = i + 1; j < indices.size(); j++)
      {
        Index3D offset = indices[i] - indices[j];
        int64_t distance = (int64_t)offset.x * (int64_t)offset.x + (int64_t)offset.y * (int64_t)offset.y +
                           (int64_t)offset.z * (int64_t)offset.z;
        distances.emplace(distance, std::pair{indices[i], indices[j]});
      }
    }
    return distances;
  }

  void Connect(Index3D i1, Index3D i2, std::vector<std::set<Index3D>>& circuits)
  {
    int n1 = -1;
    int n2 = -1;
    for (int j = 0; j < circuits.size(); j++)
    {
      if (circuits[j].count(i1) != 0)
        n1 = j;
      if (circuits[j].count(i2) != 0)
        n2 = j;
      if (n1 != -1 && n2 != -1)
        break;
    }

    if (n1 == -1 && n2 == -1)
    {
      circuits.emplace_back(std::set{i1, i2});
    }
    else if (n1 != -1 && n2 == -1)
    {
      circuits[n1].emplace(i2);
    }
    else if (n1 == -1 && n2 != -1)
    {
      circuits[n2].emplace(i1);
    }
    else if (n1 != -1 && n2 != -1 && n1 != n2)
    {
      std::set<Index3D> cpy = circuits[n2];
      circuits[n1].insert(cpy.begin(), cpy.end());
      circuits.erase(circuits.begin() + n2);
    }
  }

  OUTPUT1(input)
  {
    std::multimap<int64_t, std::pair<Index3D, Index3D>> distances = CalculateDistances(input);
    std::vector<std::set<Index3D>> circuits;
    auto it = distances.begin();
    int count = isExample ? 10 : 1000;
    for (int i = 0; i < count; i++, it++)
    {
      Connect(it->second.first, it->second.second, circuits);
    }
    std::sort(circuits.begin(),
              circuits.end(),
              [](const std::set<Index3D>& set1, const std::set<Index3D>& set2) { return set1.size() > set2.size(); });
    int64_t product = 1;
    for (int i = 0; i < 3; i++)
    {
      product *= circuits[i].size();
    }
    return product;
  }

  OUTPUT2(input)
  {
    std::multimap<int64_t, std::pair<Index3D, Index3D>> distances = CalculateDistances(input);
    std::vector<std::set<Index3D>> circuits;
    for (int i = 0; i < input.size(); i++)
    {
      circuits.emplace_back(std::set{input[i]});
    }
    auto it = distances.begin();
    for (; circuits.size() != 1; it++)
    {
      Connect(it->second.first, it->second.second, circuits);
    }
    it--;
    return (int64_t)it->second.first.x * (int64_t)it->second.second.x;
  }
}
