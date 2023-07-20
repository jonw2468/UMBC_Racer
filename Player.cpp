/*******
 ** File:    Player.cpp
 ** Project: Project 2 - UMBC Racer
 ** Author:  Jon Woods
 ** Date:    10/13/2022
 ** Section: 20/22
 ** Email: jwoods6@umbc.edu
 **
 ** This file contains the syntax for all functions involving Player objects. These functions can
 ** initialize a Player, receive and update the values of its components, and display those values
 ** as a racer summary.
*******/

#include "Player.h" // function headers for Player namespace

#include <iostream>
#include <string>
#include <cstdlib>
#include <iomanip>
using namespace std;

// Player()
// Creates a new Player object with a default racer name of Beannie.
Player::Player() {
  SetName("Beannie");
  // reset every element in array
  for (int i = 0; i < NUM_STATS; i++) {
    m_stat[i] = START_STAT;
  }
  m_races = 0;
  m_wins = 0;
  m_falls = 0;
}

// Player() overload
// Given a string, creates a new Player object with that string as the racer name.
Player::Player(string name) {
  SetName(name);
  // reset every element in array
  for (int i = 0; i < NUM_STATS; i++) {
    m_stat[i] =	START_STAT;
  }
  m_races = 0;
  m_wins = 0;
  m_falls = 0;
}

// GetName()
// Returns the racer name of a Player object as a string.
string Player::GetName() {
  return m_name;
}

// SetName()
// Given a string, return the racer name of a Player object with that string.
void Player::SetName(string name) {
  m_name = name;
}

// GetSpeed()
// Returns the first-index value of a Player object's stats array, which denotes speed.
int Player::GetSpeed() {
  return m_stat[0];
}

// GetAgility()
// Returns the second-index value of a Player object's stats array, which denotes agility.
int Player::GetAgility() {
  return m_stat[1];
}

// Returns the third-index value of a Player object's stats array, which denotes jump.
int Player::GetJump() {
  return m_stat[2];
}

// GetRaces()
// Returns the race count of a Player object.
int Player::GetRaces() {
  return m_races;
}

// GetFalls()
// Returns the fall count of a Player object.
int Player::GetFalls() {
  return m_falls;
}

// SetRacess()
// Given an integer, replaces the race count of a Player object with that integer.
void Player::SetRaces(int races) {
  m_races = races;
}

// SetFalls()
// Given an integer, replaces the fall count of a Player object with that integer.
void Player::SetFalls(int falls) {
  m_falls = falls;
}

// DisplayStatus()
// Calls the previous functions to display the value of every component in a Player object.
void Player::DisplayStatus() {
  cout << "***** The Mighty Racer " << GetName() << " *****" << endl;
  cout << "Races: " << GetRaces() << endl;
  cout << "Wins: " << m_wins << endl;
  cout << "Falls: " << GetFalls() << endl;
  cout << "\nStats\nSpeed: " << GetSpeed() << endl;
  cout << "Agility: " << GetAgility() << endl;
  cout << "Jump: " << GetJump() << endl;
}

// IncreaseStat()
// Receives an input between 1 and 3 inclusive and returns a corresponding stat value for a
// Player object.
void Player::IncreaseStat() {
  int stat;
  cout << "Which stat would you like to increase?\n1. Speed\n2. Agility\n3. Jump" << endl;
  cin >> stat;
  // input validation to maintain value between 1 & 3
  while (stat < 1 || stat > 3) {
    cout << "Please enter a number between 1 and 3." << endl;
    cin >> stat;
  }
  stat--; // subtract input value by 1 for an index between 1 and 2
  if (m_stat[stat] < MAX_STAT) {
    m_stat[stat]++;
  }
}

// IncreaseWins()
// Increments the win count of a Player object by 1.
void Player::IncreaseWins() {
  m_wins++;
}

// GetStat()
// Given an integer between 0 and 2 inclusive, returns that respective index value in a Player
// object's stats array.
int Player::GetStat(int stat) {
  return m_stat[stat];
}
