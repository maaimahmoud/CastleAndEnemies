#include <iostream>
#include <fstream>
using namespace std;
#include <windows.h>
#include <cstdlib>

#ifndef UTILITY_H
#define UTILITY_H

//The four regions: A, B, C , and D
enum REGION {	
	A_REG,
	B_REG,
	C_REG,
	D_REG
};

//Enemy types: Paver, Fighter, and Shielded Fighter
enum Etype {
	PVR,
	FITR,
	SHLD_FITR,
	SNIPER,
	SPLIT,
	HEALER
};

//constants
#define CmdWidth		150
#define CmdHeight		50
#define CastleWidth		30
#define CastleLength	20
#define CastleXStrt		(CmdWidth/2-(CastleWidth/2))
#define CastleYStrt		(CmdHeight/2-(CastleLength/2))
#define TowerWidth      7
#define TowerLength     3
#define EnemyShape		219  //ASCII code of enemy char shape 
#define FOREGROUND_BLUE 9
#define FOREGROUND_LIGHTBLUE 3
#define FOREGROUND_GREY 15
#define FOREGROUND_WHITE 0x0007

struct enemy
{
	int ID;				//Each enemy has a unique ID (sequence number)
	REGION Region;		//Region of this enemy
	int Distance;		//Distance to the castle
	double Health;		//Enemy health
	Etype Type;			//PVR, FITR, SHLD_FITR
	int timeArrival;	//Time Arrival Of Enemy
	double power;		//Enemy Power
	int reloadPriod;	//Enemy Reload Period
	double Priority;	// Priority for Enemy Shielded / Splitter
	int NumberofSplits; //Number of splits for Splitter
	int fightDelay;		//
	int killDelay;		//
	int RemainingTime;	//
	int speed;			//
	enemy *next;
};
//Tower
struct Tower
{
	int TW;				//Tower width
	int TL;				//Tower Height
	double Health;		//Tower Health
	int N;				//The Number Of Enemies That The Tower Can Attack In The Timestep
	double towerPower;	//Tower Shoot Power
	int TPaved;         //Paved distance of 60
	int Numberofkilled;	//Number Of Killed Enemies In The Tower Region for each timestep
	enemy *active;		//Pointer To The First Enemy In The Active Low Priority List
	enemy *activelast;	//Pointer To The Last Enemy In The Active Low Priority List
	enemy *high;		//Pointer To The First Enemy In The Active High Priority List
	enemy *highlast; 	//Pointer To The Last Enemy In The Active High Priority List

};
struct castle
{
	//starting x,y
	int Xstrt;
	int Ystrt;
	int W;		//width
	int L;		//Height
	int totalNumberofEnemies;	//Total numbr of enemies from the beginning of the game
	Tower towers[4];	//Castle has 4 towers
};

//Functions Prototype

/*A function to set the position of cursor on the screen*/
void gotoxy(int x, int y);

/*A function to set the command window lenght and height for the game specification*/
void SetWindow();

/*A function to color the cmd text*/
void color(int thecolor);

/*A function to partition the castle into regions (A,B,C,D)*/
void DrawRegions(const castle & C);

/*A function to draw the castle and the towers*/
void DrawCastle(const castle & C,int SimulationTime);

/*A function to draw a single enemy using its distance from the castle*/
void DrawEnemy(const enemy& E, int Ypos = 0);

/*A function to draw a list of enemies exist in all regions and ensure there is no overflow in the drawing*/
void DrawEnemies(enemy* enemies,enemy*enemiesHigh, int,int);

/*Student use this function to print his/her message*/
void PrintMsg(char*msg);

/****************************************************************************************************************************************************************************/


#endif // UTILITY_H