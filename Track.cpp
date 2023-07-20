/*******
 ** File:    Track.cpp
 ** Project: Project 2 - UMBC Racer
 ** Author:  Jon Woods
 ** Date:    10/13/2022
 ** Section: 20/22
 ** Email: jwoods6@umbc.edu
 **
 ** This file contains the syntax for all functions involving Track objects. These functions can
 ** initialize a default track, change its length, create and store its obstacles and display where
 ** the user and their opponents are, eventually determining a winner.
*******/

#include "Track.h"

#include <iostream>
#include <string>
#include <cstdlib>
#include <iomanip>
#include <ctime>
using namespace std;

// Track()
// Creates a new Track object with a default length of 4 obstacles. 
Track::Track() {
  m_length = DEFAULT_LENGTH;
  // reset every element in array
  for (int i = 0; i < NUM_RACERS; i++) {
    m_track[i] = 0;
  }
  //reset every element in array
  for (int i = 0; i < MAX_LENGTH; i++) {
    m_obstacle[i] = -1; // nonexistent index, indicating no obstacle present
  }
}

// SetLength()
// Given an integer between 1 and MAX_LENGTH inclusive, sets the number of obstacles to
// be that integer.
void Track::SetLength(int length) {
  m_length = length;
}

// PopulateObstacles()
// Randomizes the type for each obstacle in the track.
void Track::PopulateObstacles() {
  srand(time(NULL));
  for (int i = 0; i < m_length; i++) {
    m_obstacle[i] = rand() % 3;
  }
}

// GetStatus()
// Displays the position and obstacle type of the user and each computer player.
void Track::GetStatus() {
  // check user separately since user's output is different
  cout << "You are on a " << ConvertObstacle(0) << " obstacle. (obstacle " << m_track[0]+1 << " of " << m_length <<  ")" << endl;
  // check every REMAINING element in the array to show the 3 COM racers
  for (int i = 1; i < NUM_RACERS; i++) {
    cout << "Player " << i << " is on a " << ConvertObstacle(i) << " obstacle. (obstacle " << m_track[i]+1 << " of " << m_length << ")" << endl;
  }
}

// CheckWin()
// Returns the m_track[] index of the leftmost winning racer, or -1 if no one has won yet.
int Track::CheckWin() {
  // check every element in array left to right, prioritizing the user
  for (int i = 0; i < NUM_RACERS; i++) {
    if (m_track[i] >= m_length) {
      return i; // indicate to end the race
    }
  }
  return -1; // nonexistent player index, indicate to continue the race
}

// GetObstacle()
// Given an index of m_obstacle, returns the corresponding obstacle integer at that index.
int Track::GetObstacle(int location) {
  return m_obstacle[location];
}

// IncrementLocation()
// Given a player index, increases that player's location value in the race by 1.
void Track::IncrementLocation(int player) {
  m_track[player]++;
}

// ResetLocation()
// Returns every player's location value to 0 (the starting line).
void Track::ResetLocation() {
  // reset every element in array
  for (int i = 0; i < NUM_RACERS; i++) {
    m_track[i] = 0;
  }
}

// ConvertObstacle()
// Given a player index, returns a string determined by the obstacle value at that
// player's location.
string Track::ConvertObstacle(int player) {
  int obstacle = GetObstacle(m_track[player]);
  return OBSTACLE_TYPE[obstacle];
}
