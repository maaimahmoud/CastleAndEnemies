#include <iostream>
#include <fstream>
using namespace std;
#include "utility.h"

void inputfromfile(enemy *&head, enemy *&last, double &c1, double &c2, double &c3, int &TH, int &N, int &TP);	//Take The Input From File

void Simulation(char Number);								//Simulation Function

void Out(castle c, enemy *Killed, enemy *head, double);		//Make The Output File

double Avarage(enemy *head, char ch);						//Calculate The Average Of The KillDelay And FightDelay

bool GameOver(castle ct, enemy*head);						//Check If The Towers Or The Enemies Are Killed

void DecreseDistance(castle&ct);							//Decreasing The Destance Of The Enemies