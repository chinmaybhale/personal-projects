#include <iostream>
#include <string>
#include "brawler.hpp"

/* function definition(s) */

Brawler::Brawler(void) {
  /**
   * Brawler initializes the brawler to
   * no name, sets level to 1, and sets the initial
   * power points to 0.
   */

  name = "NoName";
  level = 1;
  power_points = 0;
}

Brawler::Brawler(string temp_name, int temp_level, int temp_power) {
  /**
   * Brawler initializes the brawler to the
   * specified passed attributes.
   */

  name = temp_name;
  level = temp_level;
  power_points = temp_power;
}

int Brawler::get_level(void) {
  /**
   * get_level returns the level of the
   * brawler.
   */

  return level;
}

string Brawler::get_name(void) {
  /**
   * get_name returns the name of the
   * brawler.
   */

  return name;
}

int Brawler::CalcPowerPoints(void) {
  /**
   * CalcPowerPoints calculates the required
   * number of power points until the next level
   * of the brawler.
   *
   * @return: Represents the difference of power points
   * required to the next level and the current power
   * points of a brawler.
   */

  return power_levels[level] - power_points;
}

int Brawler::TotalPowerPoints(void) {
  /**
   * TotalPowerPoints calculates the required number
   * of power points until the brawler reaches level 9.
   *
   * @return: Represents the difference of the remaining
   * power points required to level 9 of the current level's
   * power points.
   */

  int acquired_power_points = 0;

  for(int i = 0; i < level; i++) {
    acquired_power_points += power_levels[i];
  }

  // add additional earned power points
  acquired_power_points += power_points;

  return 1410 - acquired_power_points;
}

void Brawler::PrintBrawler(void) {
  /**
   * PrintBrawler displays the attributes
   * of the brawler including name, level, power points,
   * and relevant details.
   */

  // basic information
  cout << "Brawler: " << name << endl;
  cout << "Level: " << level << endl;

  // power point calculation(s) displays
  if(level < 9) {
    cout << "Current Power Points: " << power_points << endl;

    if(CalcPowerPoints() <= 0) {
      cout << "No additional Power Points required to reach level " << level + 1
           << "." << endl;
    }
    else {
      cout << "Power Points required to reach level " << level + 1
           << ": " << CalcPowerPoints() << endl;
    }

    // always calculate when under-level
    cout << "Total Power Points required to Level 9: " << TotalPowerPoints()
         << endl;
  }
  else {
    // brawlers that have reached level 9 or above receive a special message
    if(level == 9) {
      cout << name << " has not acquired a Star Power." << endl;
    }
    else if(level == 10) {
      cout << name << " has reached the maximum level and has a Star Power."
           << endl;
    }
    else {
      cout << "That level is impossible to achieve in the "
           << "current state of the game." << endl;
    }
  }
}
