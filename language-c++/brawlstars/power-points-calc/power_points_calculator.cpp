#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include "brawler.hpp"
using namespace std;

/* forward declaration(s) */
int AvgLevel(vector<Brawler>);

int main(void) {
  vector<Brawler> brawlers;

  cout << "To stop adding additional brawlers, input 'q' "
       << "as the name of the brawler or when prompted." << endl;

  // user prompt(s)
  while(true) {
    // prompt user for information
    string brawler_name;
    string response;
    int brawler_level;
    int brawler_power_points;

    cout << "Please enter Brawler's Name (i.e. Spike, Nita)." << endl << ">> ";
    cin >> brawler_name;
    if(brawler_name == "q" || brawler_name == "quit") {
      break;
    }

    cout << "Please enter " << brawler_name << "'s level." << endl << ">> ";
    cin >> brawler_level;

    cout << "Please enter " << brawler_name << "'s current power points "
         << "achieved towards the next level." << endl << ">> ";
    cin >> brawler_power_points;

    // break
    cout << "---" << endl;

    // create a brawler
    Brawler new_brawler(brawler_name, brawler_level, brawler_power_points);

    // add brawler to list of brawlers
    brawlers.push_back(new_brawler);

    cout << "Would you like to add another brawler? (y/n): ";
    cin >> response;

    if(response == "n" || response == "no") {
      break;
    }
  }

  // break
  cout << "-------------------------" << endl;

  // display brawler information
  for(int i = 0; i < brawlers.size(); i++) {
    brawlers.at(i).PrintBrawler();
  }

  cout << "-- AVERAGE RESULTS --" << endl;
  cout << "Average level of all Brawlers added: Level " << AvgLevel(brawlers) << endl;
  cout << "Total Power Points of all Brawlers to Level 9: ";
  return 0;
}

int AvgLevel(vector<Brawler> temp_brawlers) {
  /**
   * AvgLevel calculates the average level of
   * all brawlers added
   *
   * @param temp_brawlers: Represents the list of
   * all brawlers added.
   * @return: Represents the truncated average
   * to correctly depict the nearest level.
   */

  int level_sum = 0;

  for(int i = 0; i < temp_brawlers.size(); i++) {
    level_sum += temp_brawlers.at(i).get_level();
  }

  level_sum /= temp_brawlers.size();

  return round(level_sum);
}
