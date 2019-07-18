#include <string>

using namespace std;

#ifndef BRAWLER_H
#define BRAWLER_H

class Brawler {
private:
  string name;
  int level;
  int star_power_count;
  int power_points;
  int power_levels[10] = {0, 20, 30, 50, 80, 130, 210, 340, 550, 0};

public:
  Brawler(void);
  Brawler(string, int, int, int);
  int get_level(void);
  string get_name(void);
  int get_power(void);
  int get_star_count(void);
  int CalcPowerPoints(void);
  int TotalPowerPoints(void);
  void PrintBrawler(void);
};

#endif
