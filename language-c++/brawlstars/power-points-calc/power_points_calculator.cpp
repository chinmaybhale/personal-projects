#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include "brawler.hpp"
using namespace std;

/* forward declaration(s) */
int AvgLevel(vector<Brawler>);
int SumPowerPoints(vector<Brawler>);
void PrintMenu(void);
Brawler AddBrawler(void);
int ConvertChoice(string);

int main(void) {
  int active = 0;
  vector<Brawler> brawlers;

  // initial prompt
  string selection;
  PrintMenu();

  while(active == 0) {
    // prompt
    cout << "Please make a selection from the menu." << endl << ">> ";
    cin >> selection;
    int choice = ConvertChoice(selection);

    switch(choice) {
    case 1: {
      brawlers.push_back(AddBrawler());
    }
      break;
    case 2: {
      int found = -1;
      string brawler_name;
      cout << "Please enter your brawlers name (case-sensitive)*";
      cout << endl << "Enter 'all' to view all brawler's indiviual info."
           << endl << ">> ";
      cin >> brawler_name;

      // search for brawler and print information
      if(brawlers.size() > 0) {
        if(brawler_name == "all") {
          cout << "--------------------------------------------------" << endl;
          for(int i = 0; i < brawlers.size(); i++) {
            cout << "BRAWLER #" << i + 1 << ":" << endl;
            brawlers.at(i).PrintBrawler();

            cout << "--------------------------------------------------"
                 << endl;
          }
        }
        else {
          cout << "--------------------------------------------------" << endl;
          for(int i = 0; i < brawlers.size(); i++) {
            if(brawler_name == brawlers.at(i).get_name()) {
              brawlers.at(i).PrintBrawler();
              found = 0;
            }
          }

          if(found == -1) {
            cout << brawler_name << " does not exist." << endl;
          }

          cout << "--------------------------------------------------" << endl;
        }
      }
      else {
        cout << "No brawlers added yet. Tip: Type 'A' to add a new brawler."
             << endl;
      }
    }
      break;
    case 3: {
      cout << "-- AVERAGE RESULTS --" << endl;
      cout << "Average level of all Brawlers added: Level " << AvgLevel(brawlers) << endl;
      cout << "Total Power Points of all Brawlers to Level 9: " << SumPowerPoints(brawlers) << endl;
    }
      break;
    case 4: {
      active = -1;
    }
      break;
    case 5: {
      PrintMenu();
    }
      break;
    case -1: {
      cout << "That is not an option in the menu. Please try another." << endl;
    }
    }
  }

  return 0;
}

void PrintMenu(void) {
  /**
   * PrintMenu displays the context menu for options
   * available to the user.
   */

  cout << "##################################################" << endl;
  cout << "-- POWER POINTS CALCULATOR MENU --" << endl;
  cout << "A: Add a brawler." << endl;
  cout << "B: Display a brawler's information." << endl;
  cout << "D: Display collective results of brawlers added." << endl;
  cout << "Q: Quit program." << endl;
  cout << "?: Display context menu." << endl;
  cout << "##################################################" << endl;

}

int ConvertChoice(string response) {
  /**
   * ConvertChoice converts the string response
   * into an integer equivalent.
   *
   * @param response: Represents a choice (single letter)
   * within the context menu.
   * @return: Represents the integral equivalent of the
   * string choice.
   */

  if(response == "A") {
    return 1;
  }
  else if(response == "B") {
    return 2;
  }
  else if(response == "D") {
    return 3;
  }
  else if(response == "Q") {
    return 4;
  }
  else if(response == "?") {
    return 5;
  }
  else {
    return -1;
  }
}

Brawler AddBrawler(void) {
  /**
   * AddBrawler prompts user through a series of
   * questions to build a new brawler with the correct
   * attributes.
   *
   * @return: Represents a brawler object.
   */

  string brawler_name;
  int brawler_level;
  int brawler_power_points;

  cout << "Please enter Brawler's name w/o spaces (i.e. ElPrimo, Nita)." << endl << ">> ";
  cin >> brawler_name;

  while(true) {
    cout << "Please enter " << brawler_name << "'s power level." << endl << ">> ";
    cin >> brawler_level;

    if(brawler_level > 10 || brawler_level < 1) {
      cout << brawler_level << " is not within the correct range." << endl;
      cout << "The range for a brawler's level is: 1 - 10." << endl;
    }
    else {
      break;
    }
  }

  cout << "Please enter " << brawler_name << "'s current power points "
       << "achieved towards the next level." << endl << ">> ";
  cin >> brawler_power_points;

  // break
  cout << "---" << endl;

  // create a brawler
  Brawler new_brawler(brawler_name, brawler_level, brawler_power_points);

  return new_brawler;
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

int SumPowerPoints(vector<Brawler> temp_brawlers) {
  /**
   * SumPowerPoints traverses the vector of Brawlers
   * and sums the required power points for each brawler
   * to reach level 9.

   * @param temp_brawlers: Represents the list of all
   * brawlers added.
   * @return: Represents the sum of power points between
   * all brawlers to reach level 9.
   */

  int power_sum = 0;

  for(int i = 0; i < temp_brawlers.size(); i++) {
    power_sum += temp_brawlers.at(i).TotalPowerPoints();
  }

  return power_sum;
}
