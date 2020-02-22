#include <iostream>
#include <fstream>
#include "Simulation.h"
using namespace std;

int main()
{

	char Number;			//Mode Of The Program

	cout << "Select mode to simulate" << endl << "1- interactive mode" << endl << "2- step-by-step mode" << endl << "3- Silent mode" << endl;

	cin >> Number;			//Choosing The Mode

	Simulation(Number);		//Simulation Function That takes input file-Draw-Make Output File

	return 0;
}