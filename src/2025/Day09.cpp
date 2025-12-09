#include "common/aoc.h"

namespace y2025::day09
{
  using InputType = std::vector<Index2D>;
  REGISTER_DAY(2025, Day09, InputType, int64_t);

  REGISTER_TEST_EXAMPLE(2025, Day09, ExampleInput, 1, 50);
  REGISTER_TEST(2025, Day09, Input, 1, 4773451098);
  REGISTER_TEST_EXAMPLE(2025, Day09, ExampleInput, 2, 24);
  REGISTER_TEST(2025, Day09, Input, 2, 1429075575);

  READ_INPUT(input)
  {
    std::vector<Index2D> vec;
    std::string str;
    while (std::getline(input, str))
    {
      std::stringstream ss{str};
      Index2D index;
      ss >> index.x >> "," >> index.y;
      vec.emplace_back(index);
    }
    return vec;
  }

  bool ValidArea(const Array2D<char>& grid, Index2D from, Index2D to)
  {
    for (int y = from.y; y <= to.y; y++)
    {
      for (int x = from.x; x <= to.x; x++)
      {
        if (grid.Get(x, y) == 'O')
          return false;
      }
    }
    return true;
  }

  Index2D GetMappedIndex(Index2D index, const std::map<int, int>& xMap, const std::map<int, int>& yMap)
  {
    index.x = xMap.at(index.x);
    index.y = yMap.at(index.y);
    return index;
  }

  void ConvertToTopLeftAndBottomRight(Index2D& v1, Index2D& v2)
  {
    Index2D tl = Index2D{std::min(v1.x, v2.x), std::min(v1.y, v2.y)};
    Index2D br = Index2D{std::max(v1.x, v2.x), std::max(v1.y, v2.y)};
    v1 = tl;
    v2 = br;
  }

  void DrawEdges(Array2D<char>& grid,
                 const std::vector<Index2D>& vertices,
                 const std::map<int, int>& xMap,
                 const std::map<int, int>& yMap)
  {
    for (int i = 0; i < vertices.size(); i++)
    {
      Index2D tl = GetMappedIndex(vertices[i], xMap, yMap);
      Index2D br = GetMappedIndex(vertices[(i + 1) % vertices.size()], xMap, yMap);
      ConvertToTopLeftAndBottomRight(tl, br);

      Index2D diff = Index2D{tl.y == br.y, tl.x == br.x};
      for (Index2D index = tl; index.x <= br.x && index.y <= br.y; index = index + diff)
      {
        grid[index] = 'x';
      }
    }
  }

  void FloodFill(Array2D<char>& grid)
  {
    std::stack<Index2D> fill{{Index2D{0, 0}}};
    while (!fill.empty())
    {
      Index2D top = fill.top();
      fill.pop();

      std::vector<Index2D> neighbors = grid.GetNeighbors(top, false);
      for (auto neighbor : neighbors)
      {
        if (grid.Get(neighbor) == '.')
        {
          grid[neighbor] = 'O';
          fill.emplace(neighbor);
        }
      }
    }
  }

  void CalculateMaps(std::vector<Index2D> vertices, std::map<int, int>& xMap, std::map<int, int>& yMap)
  {
    std::sort(vertices.begin(), vertices.end(), [](const Index2D& i1, const Index2D& i2) { return i1.x < i2.x; });
    xMap[vertices[0].x] = 1;
    int count = 2;
    for (int i = 1; i < vertices.size(); i++)
    {
      if (vertices[i - 1].x == vertices[i].x)
        continue;

      xMap[vertices[i].x] = count;
      count++;
    }

    std::sort(vertices.begin(), vertices.end(), [](const Index2D& i1, const Index2D& i2) { return i1.y < i2.y; });
    yMap[vertices[0].y] = 1;
    count = 2;
    for (int i = 1; i < vertices.size(); i++)
    {
      if (vertices[i - 1].y == vertices[i].y)
        continue;

      yMap[vertices[i].y] = count;
      count++;
    }
  }

  int64_t CalculateArea(Index2D v1, Index2D v2)
  {
    Index2D diff = v2 - v1;
    return (std::abs(static_cast<int64_t>(diff.x)) + 1) * (std::abs(static_cast<int64_t>(diff.y)) + 1);
  }

  OUTPUT1(input)
  {
    int64_t maxArea = 0;
    for (int i = 0; i < input.size(); i++)
    {
      for (int j = i + 1; j < input.size(); j++)
      {
        maxArea = std::max(maxArea, CalculateArea(input[i], input[j]));
      }
    }
    return maxArea;
  }

  OUTPUT2(input)
  {
    std::map<int, int> xMap;
    std::map<int, int> yMap;
    CalculateMaps(input, xMap, yMap);

    Array2D<char> grid{static_cast<int>(xMap.size()) + 2, static_cast<int>(yMap.size()) + 2, '.'};

    DrawEdges(grid, input, xMap, yMap);
    FloodFill(grid);

    int64_t maxArea = 0;
    for (int i = 0; i < input.size(); i++)
    {
      for (int j = i + 1; j < input.size(); j++)
      {
        Index2D tl = input[i];
        Index2D br = input[j];

        ConvertToTopLeftAndBottomRight(tl, br);
        int64_t area = CalculateArea(tl, br);
        if (area > maxArea)
        {
          Index2D mapTl = GetMappedIndex(tl, xMap, yMap);
          Index2D mapBr = GetMappedIndex(br, xMap, yMap);
          if (ValidArea(grid, mapTl, mapBr))
          {
            maxArea = area;
          }
        }
      }
    }

    return maxArea;
  }
}
