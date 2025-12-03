/*
 * AoC Day 1 : Secret Entrance
 * Notes: circular range - modulo
 */

#include <fstream>
#include <iostream>
#include <string>

/*
 * I know i couldve used plain functions, but who cares, its doing the same
 * thing. Also im trying to learn C++ so thats that. (im coping)
 */

class DialPart1 {
  unsigned int pointing_at;
  unsigned int count_zero;

  void move_dial(const std::string &arg) {
    char direction = arg[0];
    unsigned int by = std::stoi(arg.substr(1));

    /* Initial implementation
    switch (direction) {
    case 'L': {
      for (int i = 0; i < by; i++) {
        if (pointing_at == 0)
          pointing_at = 99;
        else
          pointing_at--;
      }
      break;
    }

    case 'R': {
      for (int i = 0; i < by; i++) {
        if (pointing_at == 99)
          pointing_at = 0;
        else
          pointing_at++;
      }
      break;
    }
    }
    */

    if (direction == 'L') {
      pointing_at = (pointing_at + 100 - (by % 100)) % 100;
    } else {
      pointing_at = (pointing_at + by) % 100;
    }

    if (pointing_at == 0)
      count_zero++;
  }

public:
  DialPart1(std::string filename) : pointing_at(50), count_zero(0) {
    std::ifstream input(filename);

    if (input.is_open()) {
      std::string line;
      while (std::getline(input, line)) {
        move_dial(line);
      }
    }

    std::cout << "Part 1: For " << filename << ": " << count_zero << "\n";
  }
};

class DialPart2 {
  int pointing_at;
  unsigned int count_zero;

  void move_dial(const std::string &arg) {
    char direction = arg[0];
    int by = std::stoi(arg.substr(1));

    /* Initial implementation
    switch (direction) {
    case 'L': {
      for (int i = 0; i < by; i++) {
        if (pointing_at == 0)
          pointing_at = 99;
        else
          pointing_at--;
        if (pointing_at == 0)
          count_zero++;
      }
      break;
    }

    case 'R': {
      for (int i = 0; i < by; i++) {
        if (pointing_at == 99)
          pointing_at = 0;
        else
          pointing_at++;
        if (pointing_at == 0)
          count_zero++;
      }
      break;
    }
    }
    */

    /* Second try
    if (direction == 'L') {
      for (int i = 0; i < by; i++) {
        pointing_at = (pointing_at + 99) % 100;
        if (pointing_at == 0)
          count_zero++;
      }
    } else {
      for (int i = 0; i < by; i++) {
        pointing_at = (pointing_at + 1) % 100;
        if (pointing_at == 0)
          count_zero++;
      }
    }
    */

    int temp = (direction == 'L') ? 99 : 1;

    for (int i = 0; i < by; i++) {
      pointing_at = (pointing_at + temp) % 100;
      if (pointing_at == 0)
        count_zero++;
    }
  }

public:
  DialPart2(std::string filename) : pointing_at(50), count_zero(0) {
    std::ifstream input(filename);

    if (input.is_open()) {
      std::string line;
      while (std::getline(input, line)) {
        move_dial(line);
      }
      input.close();
    }

    std::cout << "Part 2: For " << filename << ": " << count_zero << "\n";
  }
};

int main(int argc, char *argv[]) {
  std::cout << "AoC Day 1 : Secret Entrance\n\n";

  // Part 1
  DialPart1 example("example.txt");
  DialPart1 input("input.txt");

  // Part 2
  DialPart2 example2("example.txt");
  DialPart2 input2("input.txt");

  return 0;
}
