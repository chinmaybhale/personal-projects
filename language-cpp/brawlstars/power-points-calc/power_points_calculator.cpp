#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <cmath>
#include "brawler.hpp"
using namespace std;

/* forward declaration(s) */
int AvgLevel(vector<Brawler>);
int SumPowerPoints(vector<Brawler>);
void PrintMenu(void);
void AddBrawler(vector<Brawler> *);
int ConvertChoice(string);
void RemoveBrawler(string, vector<Brawler> *);
void PrintPretty(vector<Brawler> *);
void printBrawlerInfo(vector<Brawler> *);
int findBrawler(vector<Brawler> *, string);

int main(void) {
  int active = 0;
  vector<Brawler> brawlers;

  // initial prompt
  string selection;
  PrintMenu();

  while(active == 0) {
    // repeating prompt
    cout << "Please make a selection from the menu." << endl << ">> ";
    cin >> selection;
    int choice = ConvertChoice(selection);

    switch(choice) {
    case 1: {
      AddBrawler(&brawlers);
    }
      break;
    case 2: {
      printBrawlerInfo(&brawlers);
    }
      break;
    case 3: {
      cout << "============================================" << endl;
      cout << "              AVERAGE STATS                 " << endl;
      cout << "============================================" << endl;

      cout << "AVERAGE LEVEL: " << AvgLevel(brawlers) << endl;
      cout << "============================================" << endl;
      cout << "TOTAL REMAINING POWER POINTS TO EARN: " << SumPowerPoints(brawlers) << endl;
      cout << "============================================" << endl;

      cout << "Brawlers applicable for/have Star Power(s): " << endl;
      int count = 1;

      for(int i = 0; i < brawlers.size(); i++) {
        if(brawlers.at(i).TotalPowerPoints() == 0) {
          if(brawlers.at(i).get_level() == 10) {
            cout << count << ". " << brawlers.at(i).get_name() << " ";

            for(int ii = 1; ii <= brawlers.at(i).get_star_count(); ii++) {
              cout << "*";
            }

            cout << endl;
          }
          else {
            cout << count << ". " << brawlers.at(i).get_name() << endl;
          }

          count++;
        }
      }
    }
      break;
    case 4: {
      // prompt for brawler to remove
      cout << "Please enter the brawler to remove." << endl << ">> ";
      string rm_brawler;
      cin >> rm_brawler;

      RemoveBrawler(rm_brawler, &brawlers);
    }
      break;
    case 5: {
      PrintPretty(&brawlers);
    }
      break;
    case 6: {
      active = -1;
    }
      break;
    case 7: {
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
  cout << "A: Add a brawler." << endl;                                 // 1
  cout << "B: Display a brawler's information." << endl;               // 2
  cout << "D: Display collective results of brawlers added." << endl;  // 3
  cout << "R: Removes a brawler by name (case-sensitive)." << endl;    // 4
  cout << "T: Displays a table of all brawlers added." << endl;        // 5
  cout << "Q: Quit program." << endl;                                  // 6
  cout << "?: Display context menu." << endl;                          // 7
  cout << "##################################################" << endl;

}

void PrintPretty(vector<Brawler> * brawlers_ptr) {
  /**
   * PrintPretty displays a table of all brawlers added with
   * relevant information added.
   *
   * @param brawlers_ptr: Represents the address of the brawlers
   * vector.
   */

  cout << "============================================" << endl;
  cout << "BRAWLER\t\tLEVEL\t\tPOWER POINTS" << endl;
  cout << "============================================" << endl;
  for(int i = 0; i < brawlers_ptr->size(); i++) {
    cout << left << setw(18) << setfill(' ') << brawlers_ptr->at(i).get_name();
    cout << left << setw(18) << setfill(' ') << brawlers_ptr->at(i).get_level();
    cout << left << setw(10) << setfill(' ') << brawlers_ptr->at(i).get_power() << endl;
  }
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
  else if(response == "R") {
    return 4;
  }
  else if(response == "T") {
    return 5;
  }
  else if(response == "Q" || response == "q" || response == "quit"
          || response == "QUIT" || response == "exit" || response == "EXIT") {
    return 6;
  }
  else if(response == "?") {
    return 7;
  }
  else {
    return -1;
  }
}

void AddBrawler(vector<Brawler> * brawlers_ptr) {
  /**
   * AddBrawler prompts user through a series of
   * questions to build a new brawler with the correct
   * attributes.
   *
   * @return: Represents a brawler object.
   */

  string brawler_name;

  // init default value(s)
  int brawler_level = 1;
  int brawler_power_points = 0;
  int brawler_star_count = 0;

  /* NAME */
  cout << "Please enter Brawler's name w/o spaces (i.e. ElPrimo, Nita)." << endl << ">> ";
  cin >> brawler_name;

  /* POWER LEVEL */
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

  /* STAR POWER(S) */
  if(brawler_level == 10) {
    cout << "How many Star Powers does " << brawler_name << " have?" << endl;
    cout << ">> ";
    cin >> brawler_star_count;
  }

  /* POWER POINTS */
  if(brawler_level < 9) {
    cout << "Please enter " << brawler_name << "'s current power points "
         << "achieved towards the next level." << endl << ">> ";
    cin >> brawler_power_points;
  }

  // break
  cout << "---" << endl;

  // create the brawler
  Brawler new_brawler(brawler_name, brawler_level, brawler_power_points, brawler_star_count);

  // add the brawler
  brawlers_ptr->push_back(new_brawler);
}

void RemoveBrawler(string brawler, vector<Brawler> * brawlers_ptr) {
  /**
   * RemoveBrawler traverses the vector and searches for the brawler
   * with the given name and removes it from the vector.
   *
   * @param brawler: Represents the brawler to be removed.
   * @param temp_brawlers: Represents the list of brawlers.
   */

  for(int i = 0; i < brawlers_ptr->size(); i++) {
    if(brawler == brawlers_ptr->at(i).get_name()) {
      brawlers_ptr->erase(brawlers_ptr->begin() + i);
    }
  }
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

void printBrawlerInfo(vector<Brawler> * brawler_ptr) {
  /**
   * printBrawlerInfo displays the appropriate info of an individual
   * brawler.
   *
   * @param brawler_ptr: Represents a pointer to the base address of the
   * brawler vector.
   */

  string brawler_name;

  // prompt for name
  cout << "Please enter your brawlers name (case-sensitive)*";
  cout << endl << "Enter 'all' to view all brawler's indiviual info."
       << endl << ">> ";
  cin >> brawler_name;

  // check if any brawlers have been added
  if(brawler_ptr->size() < 1) {
    cout << "No brawlers added. Tip: Type 'A' to add a new brawler." << endl;
  }
  else {
    // check if every brawler info is to be printed
    if(brawler_name == "all") {
      cout << "-------------------------------------------------------" << endl;
      for(int brawlerIndex = 0; brawlerIndex < brawler_ptr->size();
          brawlerIndex++) {
        cout << "BRAWLER #" << brawlerIndex + 1 << ":" << endl;
        brawler_ptr->at(brawlerIndex).PrintBrawler();

        cout << "--------------------------------------------------------"
             << endl;
      }
    }
    else {
      // single brawler to be printed
      cout << "-------------------------------------------------------" << endl;
      if(findBrawler(brawler_ptr, brawler_name) != -1) {
        // brawler exists
        brawler_ptr->at(findBrawler(brawler_ptr, brawler_name)).PrintBrawler();
      }
      else {
        // brawler does NOT exist
        cout << brawler_name << " does not exist.\n" << endl;
      }

      cout << "-------------------------------------------------------" << endl;
    }
  }
}

int findBrawler(vector<Brawler> * brawler_ptr, string brawler_name) {
  /**
   * findBrawler traverses a vector of brawlers and searches
   * for the a brawler with the matching name. The index of the brawler
   * is then returned.
   *
   * @param brawler_ptr: Represents a pointer to the base address of the
   * brawler vector.
   * @param brawler_name: Represents the brawler to be searched for.
   * @return: Represents the index of the located brawler - returns -1
   * when no brawler matching the name is found.
   */

  int i = -1;

  for(i = 0; i < brawler_ptr->size(); i++) {
    if(brawler_ptr->at(i).get_name() == brawler_name) {
      return i;
    }
  }

  return -1;
}
