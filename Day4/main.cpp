/*
 * AoC Day 4 : Printing Department
 */

#include <fstream>
#include <iostream>
#include <vector>

int rollsOfPaper(std::string filename) {
  std::ifstream input(filename);
  if (!input)
    return 0;

  std::vector<std::vector<bool>> rack;

  std::string line;
  while (std::getline(input, line)) {
    std::vector<bool> row;
    for (char ch : line)
      row.push_back(ch == '@');
    rack.push_back(row);
  }

  int total = 0;

  for (int i = 0; i < rack.size(); i++) {
    for (int j = 0; j < rack[i].size(); j++) {

      if (!rack[i][j])
        continue;

      int adjacentCount = 0;

      int directions[8][2] = {{-1, -1}, {-1, 0}, {-1, 1}, {0, -1},
                              {0, 1},   {1, -1}, {1, 0},  {1, 1}};

      for (int d = 0; d < 8; d++) {
        int newi = i + directions[d][0];
        int newj = j + directions[d][1];

        if (newi >= 0 && newi < rack.size() && newj >= 0 &&
            newj < rack[newi].size() && rack[newi][newj])
          adjacentCount++;
      }

      if (adjacentCount < 4)
        total++;
    }
  }

  return total;
}

int rollsOfPaperPart2(std::string filename) {
  std::ifstream input(filename);
  if (!input)
    return 0;

  std::vector<std::vector<int>> rack;

  std::string line;
  while (std::getline(input, line)) {
    std::vector<int> row;
    for (char ch : line)
      if (ch == 'x')
        row.push_back(2);
      else if (ch == '@')
        row.push_back(1);
      else if (ch == '.')
        row.push_back(0);
    rack.push_back(row);
  }

  int total = 0;

  int directions[8][2] = {{-1, -1}, {-1, 0}, {-1, 1}, {0, -1},
                          {0, 1},   {1, -1}, {1, 0},  {1, 1}};

  bool changed = true;
  while (changed) {
    changed = false;
    std::vector<std::pair<int, int>> toRem;

    for (int i = 0; i < rack.size(); i++) {
      for (int j = 0; j < rack[i].size(); j++) {
        if (rack[i][j] != 1)
          continue;

        int adjacentCount = 0;
        for (int d = 0; d < 8; d++) {
          int newi = i + directions[d][0];
          int newj = j + directions[d][1];

          if (newi >= 0 && newi < rack.size() && newj >= 0 &&
              newj < rack[newi].size() && rack[newi][newj] == 1)
            adjacentCount++;
        }

        if (adjacentCount < 4)
          toRem.push_back({i, j});
      }
    }

    if (!toRem.empty()) {
      for (auto [i, j] : toRem) {
        rack[i][j] = 0;
        total++;
      }
      changed = true;
    }
  }

  return total;
}

int main(int argc, char *argv[]) {
  std::cout << "AoC Day 4 : Printing Department\n";

  int total = rollsOfPaper("example.txt");
  std::cout << "Part 1: For Example: " << total << " (13 Expected)\n";

  total = rollsOfPaper("input.txt");
  std::cout << "Part 1: For Input: " << total << "\n";

  total = rollsOfPaperPart2("example.txt");
  std::cout << "Part 2: For Example: " << total << " (43 Expected)\n";

  total = rollsOfPaperPart2("input.txt");
  std::cout << "Part 2: For Input: " << total << "\n";

  return 0;
}
