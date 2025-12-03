/*
 * AoC Day 2 : Gift Shop
 * Notes: String manipulation, large numbers, patterns
 */

#include <cmath>
#include <fstream>
#include <iostream>
#include <set>
#include <sstream>
#include <string>
#include <vector>

struct Range {
  std::string start;
  std::string end;
};

unsigned long long calculateSumOfInvalidIds(std::string filepath) {
  std::ifstream input(filepath);
  if (!input)
    return 0;

  std::vector<Range> ranges;
  std::string line;

  std::getline(input, line);

  std::stringstream ss(line);
  std::string rangeStr;

  while (std::getline(ss, rangeStr, ',')) {
    size_t dashPos = rangeStr.find('-');
    std::string start = (rangeStr.substr(0, dashPos));
    std::string end = (rangeStr.substr(dashPos + 1));
    ranges.push_back({start, end});
  }

  unsigned long long sum = 0;

  for (const auto &r : ranges) {
    int numDigitsStart = r.start.length();
    int numDigitsEnd = r.end.length();
    for (int i = 2; i <= numDigitsEnd; i += 2) {
      int patternLength = i / 2;

      long long minPattern = (long long)std::pow(10, patternLength - 1);
      long long maxPattern = (long long)std::pow(10, patternLength) - 1;

      for (long long pattern = minPattern; pattern <= maxPattern; pattern++) {
        std::string patternStr = std::to_string(pattern);
        std::string invalidIdStr = patternStr + patternStr;

        bool exceedsEnd =
            (invalidIdStr.length() > numDigitsEnd) ||
            (invalidIdStr.length() == numDigitsEnd && invalidIdStr > r.end);

        if (exceedsEnd)
          break;

        bool withinStart = (invalidIdStr.length() > numDigitsStart) ||
                           (invalidIdStr.length() == numDigitsStart &&
                            invalidIdStr >= r.start);

        if (withinStart)
          sum += std::stoull(invalidIdStr);
      }
    }
  }

  return sum;
}

unsigned long long calculateSumOfInvalidIdsPart2(std::string filepath) {
  std::ifstream input(filepath);
  if (!input)
    return 0;

  std::vector<Range> ranges;
  std::string line;

  std::getline(input, line);

  std::stringstream ss(line);
  std::string rangeStr;

  while (std::getline(ss, rangeStr, ',')) {
    size_t dashPos = rangeStr.find('-');
    std::string start = (rangeStr.substr(0, dashPos));
    std::string end = (rangeStr.substr(dashPos + 1));
    ranges.push_back({start, end});
  }

  unsigned long long sum = 0;

  for (const auto &r : ranges) {
    std::set<unsigned long long> invalidIds;

    int numDigitsStart = r.start.length();
    int numDigitsEnd = r.end.length();

    for (int i = 2; i <= numDigitsEnd; i++) {
      for (int patternLength = 1; patternLength <= i / 2; patternLength++) {
        if (i % patternLength != 0) {
          continue;
        }

        int rep = i / patternLength;
        long long minPattern = (long long)std::pow(10, patternLength - 1);
        long long maxPattern = (long long)std::pow(10, patternLength) - 1;

        for (long long pattern = minPattern; pattern <= maxPattern; pattern++) {
          std::string patternStr = std::to_string(pattern);
          std::string invalidIdStr = "";
          for (int i = 0; i < rep; i++) {
            invalidIdStr += patternStr;
          }

          bool exceedsEnd =
              (invalidIdStr.length() > numDigitsEnd) ||
              (invalidIdStr.length() == numDigitsEnd && invalidIdStr > r.end);

          if (exceedsEnd)
            break;

          bool withinStart = (invalidIdStr.length() > numDigitsStart ||
                              (invalidIdStr.length() == numDigitsStart &&
                               invalidIdStr >= r.start));

          if (withinStart) {
            unsigned long long invalidId = std::stoull(invalidIdStr);
            invalidIds.insert(invalidId);
          }
        }
      }
    }

    for (unsigned long long id : invalidIds)
      sum += id;
  }

  return sum;
}

int main(int argc, char *argv[]) {
  std::cout << "AoC Day 2 : Gift Shop\n";

  unsigned long long sum = calculateSumOfInvalidIds("example.txt");
  std::cout << "Part 1: For Example: " << sum << "\n";

  sum = calculateSumOfInvalidIds("input.txt");
  std::cout << "Part 1: For Input: " << sum << "\n";

  sum = calculateSumOfInvalidIdsPart2("example.txt");
  std::cout << "Part 2: For Example: " << sum << "\n";

  sum = calculateSumOfInvalidIdsPart2("input.txt");
  std::cout << "Part 2: For Input: " << sum << "\n";

  return 0;
}
