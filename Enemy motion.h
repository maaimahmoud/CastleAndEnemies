#include "Simulation.h"

void DecreseDistance(castle&ct);						//Decreasing The Distance Of The Enemies

void CheckTowers(castle&ct, enemy*&head);				//Check If Any Tower Is Dead and merge lists of dead tower and next tower is not dead/clock wise

void ChangeRegion(castle&ct, enemy*temp);				//Check If Any Tower Is Dead -> Check towers will call this function to change region of every enemy in active list or inactive