/*******
 ** File:    Race.cpp
 ** Project: Project 2 - UMBC Racer
 ** Author:  Jon Woods
 ** Date:    10/13/2022
 ** Section: 20/22
 ** Email: jwoods6@umbc.edu
 **
 ** This file contains the syntax for all functions involving Race objects. These functions
 ** incorporate functions from Player.cpp and Track.cpp in order establish the framework for
 ** the UMBC Racer as a program.
*******/

#include "Player.h" //User defined class required by Race
#include "Track.h" //User defined class required by Race
#include "Race.h"

#include <iostream>
#include <string>
#include <cstdlib>
#include <iomanip>
#include <ctime>

using namespace std;

// Race()
// Initializes a Race object with no changes.
Race::Race() {
}

// StartRace()
// Sets up a Track, calls race progression functions, and displays the winner.
void Race::StartRace() {
  // reset the length, obstacles, and locations of the Track object
  m_track = Track();
  m_track.ResetLocation();
  m_myPlayer.SetRaces(m_myPlayer.GetRaces() + 1); // increment race count
  int length; // number of obstacles in the race (m_track.m_length)
  cout << "How long would you like the race?" << endl;
  cin >> length;
  // input validation
  while (length < 0 || length > MAX_LENGTH) {
    cout << "Length must be between 1 and 100 obstacles." << endl;
    cin >> length;
  }
  // set up the Track object for a new race
  m_track.SetLength(length);
  m_track.PopulateObstacles();
  int winner = -1; // index of the winning racer, nonexistent at the start
  do {
    int choice = RaceOptions();
    switch (choice) {
    case 1: // user chooses to view the race status
      m_track.GetStatus();
      break;
    default: // user chooses to apply a skill
      ProgressRace(choice);
      break;
    }
    winner = m_track.CheckWin();
  } while (winner == -1); // repeat until an existing player index is returned by CheckWin()
  switch (winner) {
  case 0: // user wins the race and gets to increase a stat
    cout << "You won the race!" << endl;
    m_myPlayer.IncreaseStat();
    m_myPlayer.IncreaseWins();
    break;
  default: // user loses the race and nothing happens
    cout << "Player " << winner << " won the race!" << endl;
    break;
  }
}

// GetRacerInfo()
// Initializes a Player object with a name value optionally given by the user.
void Race::GetRacerInfo() {
  string name; // racer name of the Player object (m_myPlayer.m_name)
  cout << "What is your racer's name?" << endl;
  getline(cin, name);
  if (name == "") {
    m_myPlayer = Player(); // instantiate the Player object as the default Beannie
  } else {
    m_myPlayer = Player(name); // instantiate the Player oject using the overloaded function
  }
}

// MainMenu()
// Displays the main menu using inputs. Calls StartRace() or DisplayStatus() and returns whether
// to show the main menu again.
bool Race::MainMenu() {
  int m; // value of the user's choice on menu
  cout << "What would you like to do?\n1. Start New Race\n2. View Racer History\n3. Quit" << endl;
  cin >> m;
  // input validation
  while ((m < 1) || (m > 3)) {
    cout << "Please enter an integer between 1 and 3." << endl;
    cin >> m;
  }
  switch (m) {
  case 1: // user chooses to begin a new race
    StartRace();
    break;
  case 2: // user chooses to view their current stats
    m_myPlayer.DisplayStatus();
    break;
  case 3: // user chooses to quit application
    return false;
  }
  return true; // for case 1 or 2, ManageGame() below returns to the main menu
}

// ManageGame()
// Displays main menu between races and thanks the user when they quit the program.
void Race::ManageGame() {
  RaceTitle();
  GetRacerInfo();
  // menu input is in the MainMenu() function, so loop is empty
  while (MainMenu()) {
  }
  cout << "Thanks for playing UMBC Racer!" << endl; // display thank-you message, terminate program
}

// ProgressRace()
// Given an integer for a type of move (sprint, dodge, or jump) at an obstacle, displays whether
// the user has enough skill to pass that obstacle and moves them to the next obstacle if so.
void Race::ProgressRace(int move) {
  srand(time(NULL));
  move -= 2; //convert move input value to an index in OBSTACLE_TYPE
  int difficulty = rand() % (COMP_MAX - COMP_MIN + 1) + COMP_MIN; // random int between 40 and 100
  string obstacle = m_track.ConvertObstacle(0);
  int skill = BASE_SKILL;
  // user gets a boost to their skill if their move correspends with the correct obstacle type
  if (obstacle == OBSTACLE_TYPE[move]) { 
    skill += m_myPlayer.GetStat(move)*5;
  }
  cout << "You are trying to progress the race!" << endl;
  if (skill >= difficulty) {
    cout << "You made it through the " << obstacle << " obstacle!" << endl;
    m_track.IncrementLocation(0); // move user forward one obstacle
  } else {
    cout << "You fell!" << endl;
    m_myPlayer.SetFalls(m_myPlayer.GetFalls() + 1); // increment fall count
  }
  ProgressComputer(difficulty);
}

// ProgressComputer()
// Given a random difficulty value between 40 and 100 inclusive, randomizes skill value for each
// computer player. Displays whether the user has enough skill to pass their current obstacle and
// moves them to the next obstacle if so.
void Race::ProgressComputer(int obstacleDifficulty) {
  // check the last 3 indexes in array
  for (int i = 1; i < NUM_RACERS; i++) {
    int skill = rand() % (COMP_MAX - COMP_MIN + 1) + COMP_MIN;
    string obstacle = m_track.ConvertObstacle(i);
    if (skill >= obstacleDifficulty) {
      cout << "Player " << i << "  made it through the " << obstacle << " obstacle!" << endl;
      m_track.IncrementLocation(i); //move computer player forward one obstacle
    } else {
      cout << "Player " << i << " fell!" << endl;
    }
  }
}

// RaceOptions()
// Returns a number between 1 and 4 as chosen by the user, which indicates their next move
// in a race.
int Race::RaceOptions() {
  int choice; // value of the user's next move
  cout << "What would you like to do?\n1. Get Race Status\n2. Try to Sprint (Speed)\n3. Try to Dodge (ability)\n4. Try to Jump (Jump)"  << endl;
  cin >> choice;
  // input validation
  while ((choice < 1) || (choice > 4)) {
    cout << "Please enter an integer between 1 and 4." << endl;
    cin >> choice;
  }
  return choice;
}
