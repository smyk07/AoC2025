/*
 * AoC Day 5 : Cafeteria
 */

#include <algorithm>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

struct RangeMap {
  std::vector<std::pair<unsigned long long, unsigned long long>> ranges;

  void addRange(unsigned long long start, unsigned long long end) {
    ranges.emplace_back(start, end);
  }

  bool contains(unsigned long long value) const {
    for (const auto &[start, end] : ranges) {
      if (value >= start && value <= end) {
        return true;
      }
    }
    return false;
  }

  unsigned long long totalidx() {
    std::sort(ranges.begin(), ranges.end());

    std::vector<std::pair<unsigned long long, unsigned long long>> mergedRanges;
    unsigned long long currentStart = ranges[0].first;
    unsigned long long currentEnd = ranges[0].second;

    for (size_t i = 1; i < ranges.size(); ++i) {
      const auto &nextRange = ranges[i];

      if (nextRange.first <= currentEnd + 1) {
        currentEnd = std::max(currentEnd, nextRange.second);
      } else {
        mergedRanges.emplace_back(currentStart, currentEnd);
        currentStart = nextRange.first;
        currentEnd = nextRange.second;
      }
    }

    mergedRanges.emplace_back(currentStart, currentEnd);

    unsigned long long total = 0;
    for (const auto &[start, end] : mergedRanges) {
      total += (end - start + 1);
    }

    return total;
  }
};

unsigned long long getFreshIngredients(std::string filename) {
  std::ifstream input(filename);
  if (!input)
    return 0;

  std::string line;

  std::stringstream ss(line);
  RangeMap freshMap;

  while (std::getline(input, line) && !line.empty()) {
    size_t dashPos = line.find('-');
    std::string start = (line.substr(0, dashPos));
    std::string end = (line.substr(dashPos + 1));
    freshMap.addRange(std::stoull(start), std::stoull(end));
  }

  std::vector<unsigned long long> available;

  while (std::getline(input, line)) {
    available.push_back(std::stoull(line));
  }

  unsigned long long totalFresh = 0;

  for (unsigned long long i : available)
    if (freshMap.contains(i))
      totalFresh++;

  return totalFresh;
}

unsigned long long getFreshIngredientsPart2(std::string filename) {
  std::ifstream input(filename);
  if (!input)
    return 0;

  std::string line;

  std::stringstream ss(line);
  RangeMap freshMap;

  while (std::getline(input, line) && !line.empty()) {
    size_t dashPos = line.find('-');
    std::string start = (line.substr(0, dashPos));
    std::string end = (line.substr(dashPos + 1));
    freshMap.addRange(std::stoull(start), std::stoull(end));
  }

  return freshMap.totalidx();
}

int main(int argc, char *argv[]) {
  std::cout << "AoC Day 5 : Cafeteria\n";

  unsigned long long total = getFreshIngredients("example.txt");
  std::cout << "Part 1: For Example: " << total << " (3 expected) \n";

  total = getFreshIngredients("input.txt");
  std::cout << "Part 1: For Input: " << total << "\n";

  total = getFreshIngredientsPart2("example.txt");
  std::cout << "Part 2: For Example: " << total << " (14 expected) \n";

  total = getFreshIngredientsPart2("input.txt");
  std::cout << "Part 2: For Input: " << total << "\n";

  return 0;
}
