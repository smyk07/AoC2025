/*
 * AoC Day 3 : Lobby
 * Notes: greedy
 */

#include <cstddef>
#include <fstream>
#include <iostream>
#include <string>

int totalOutputJoltage(std::string filepath) {
  std::ifstream input(filepath);
  if (!input)
    return 0;

  std::string line;

  int sum = 0;

  while (std::getline(input, line)) {
    int max1 = 0;
    size_t max1idx;

    for (size_t i = 0; i < line.size() - 1; i++) {
      int num = line[i] - '0';
      if (num > max1) {
        max1 = num;
        max1idx = i;
      }
    }

    int max2 = 0;

    for (size_t i = max1idx + 1; i < line.size(); ++i) {
      int num = line[i] - '0';
      if (num > max2)
        max2 = num;
    }

    sum += (max1 * 10) + max2;
  }

  return sum;
}

unsigned long long totalOutputJoltagePart2(std::string filepath) {
  std::ifstream input(filepath);
  if (!input)
    return 0;

  std::string line;
  unsigned long long sum = 0;

  while (std::getline(input, line)) {
    int maxcount = 12;

    int n = line.size();

    std::string result;
    int start = 0;

    for (int i = 0; i < maxcount; ++i) {
      char maxChar = '0';
      int maxPos = start;

      int searchEnd = n - (maxcount - i);

      for (int j = start; j <= searchEnd; ++j) {
        if (line[j] > maxChar) {
          maxChar = line[j];
          maxPos = j;
        }
      }

      result += maxChar;
      start = maxPos + 1;
    }

    unsigned long long value = std::stoull(result);
    sum += value;
  }

  return sum;
}

int main(int argc, char *argv[]) {
  std::cout << "AoC Day 3 : Lobby\n";

  int sum = totalOutputJoltage("example.txt");
  std::cout << "Part 1: For Example: " << sum << " (357 Expected)\n";

  sum = totalOutputJoltage("input.txt");
  std::cout << "Part 1: For Input: " << sum << "\n";

  unsigned long long sum2 = totalOutputJoltagePart2("example.txt");
  std::cout << "Part 2: For Example: " << sum2 << " (3121910778619 Expected)\n";

  sum2 = totalOutputJoltagePart2("input.txt");
  std::cout << "Part 2: For Input: " << sum2 << "\n";

  return 0;
}
