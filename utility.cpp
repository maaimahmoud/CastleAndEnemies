#include "utility.h"
#include <cstdlib>
#include <ctime>

/*A function to set the position of cursor on the screen*/
void gotoxy(int x, int y)
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

	_COORD pos;
	pos.X = x;
	pos.Y = y;

	SetConsoleCursorPosition(hConsole, pos);
}
///////////////////////////////////////////////////////////////////////////////////////

/*A function to set the command window lenght and height for the game specification*/
void SetWindow()
{
	system("mode 150,50");   //Set mode to ensure window does not exceed buffer size
	SMALL_RECT WinRect = { 0, 0, CmdWidth, CmdHeight };   //New dimensions for window in 8x12 pixel chars
	SMALL_RECT* WinSize = &WinRect;
	SetConsoleWindowInfo(GetStdHandle(STD_OUTPUT_HANDLE), true, WinSize);   //Set new size for window
}
///////////////////////////////////////////////////////////////////////////////////////

/*A function to color the cmd text*/
void color(int thecolor)
{
	HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hStdout,
		thecolor | FOREGROUND_INTENSITY);
}
///////////////////////////////////////////////////////////////////////////////////////

/*A function to partition the castle into regions (A,B,C,D)*/
void DrawRegions(const castle & C)
{
	color(FOREGROUND_RED | FOREGROUND_BLUE);
	//system("Color 5E");
	gotoxy(0, C.Ystrt + C.L / 2);
	for (int i = 0; i<C.W + 2 * C.Xstrt; i++)
		cout << "=";
	for (int j = 0; j<C.L + 2 * C.Ystrt; j++)
	{
		gotoxy(C.Xstrt + C.W / 2, j);
		cout << "||";
	}
	color(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
}
///////////////////////////////////////////////////////////////////////////////////////

/*A function to draw the castle and the towers*/
void DrawCastle(const castle & C, int SimulationTime)
{
	system("CLS");
	//Draw the castle
	//cout << endl;
	gotoxy(C.Xstrt, C.Ystrt);
	for (int i = 0; i<C.W; i++)
		cout << "=";
	for (int j = 1; j<C.L; j++)
	{
		gotoxy(C.Xstrt, C.Ystrt + j);
		cout << "|";
		gotoxy(C.Xstrt + C.W - 1, C.Ystrt + j);
		cout << "|";
	}
	gotoxy(C.Xstrt, C.Ystrt + C.L - 1);
	for (int i = 0; i<C.W; i++)
		cout << "=";

	//Draw towers
	int T1X, T2X, T3X, T4X, T1Y, T2Y, T3Y, T4Y;
	for (int i = 0; i<4; i++)
	{

		if (i == 0)
		{
			if (C.towers[0].Health == 0)
				for (int i = 1; i < C.L / 2; i++)
				{
					color(FOREGROUND_RED);
					for (int j = 1; j < C.W / 2; j++)
					{
						gotoxy(C.Xstrt + j, C.Ystrt + i);
						cout << (char)EnemyShape;
					}
					color(FOREGROUND_GREY);
				}
			for (int i = 1; i < C.L / 2; i++)
			{
				for (int j = 1; j < 60 - C.towers[0].TPaved; j++)
				{
					gotoxy(C.Xstrt - j, C.Ystrt + i);
					cout << (char)EnemyShape;
				}
			}
			T1X = C.Xstrt + 1;
			T1Y = C.Ystrt + TowerLength;
			gotoxy(T1X, T1Y);
			for (int i = 0; i<TowerWidth; i++)
				cout << "=";
			gotoxy(T1X + 1, T1Y - 1);
			cout << "T1" << "(" << C.towers[0].Health << ")";

			gotoxy(C.Xstrt + C.W / 4, C.Ystrt + C.L / 4);
			cout << "(A)";
		}
		else if (i == 1)
		{
			if (C.towers[1].Health == 0)

				for (int i = 1; i < C.L / 2; i++)
				{
					color(FOREGROUND_RED);
					for (int j = C.W / 2 + 1; j < C.W - 1; j++)
					{
						gotoxy(C.Xstrt + j, C.Ystrt + i);
						cout << (char)EnemyShape;
					}
					color(FOREGROUND_GREY);
				}
			for (int i = 1; i < C.L / 2; i++)
			{
				for (int j = 0; j <60 - C.towers[1].TPaved; j++)
				{
					gotoxy(C.Xstrt + C.W + j, C.Ystrt + i);
					cout << (char)EnemyShape;
				}
			}
			T2X = C.Xstrt + C.W - 2 - TowerWidth;
			T2Y = T1Y;
			gotoxy(T2X, T2Y);
			for (int i = 0; i<TowerWidth + 1; i++)
				cout << "=";
			gotoxy(T2X + 1, T2Y - 1);
			cout << "T2" << "(" << C.towers[1].Health << ")";
			gotoxy(C.Xstrt + (3 * C.W / 4), C.Ystrt + C.L / 4);
			cout << "(B)";
		}
		else if (i == 2)
		{
			if (C.towers[2].Health == 0)
				for (int i = C.L / 2; i < C.L - 1; i++)
				{
					color(FOREGROUND_RED);
					for (int j = C.W / 2 + 1; j < C.W - 1; j++)
					{
						gotoxy(C.Xstrt + j, C.Ystrt + i);
						cout << (char)EnemyShape;
					}
					color(FOREGROUND_GREY);
				}
			for (int i = C.L / 2; i < C.L - 1; i++)
			{
				for (int j = 0; j <60 - C.towers[2].TPaved; j++)
				{
					gotoxy(C.Xstrt + C.W + j, C.Ystrt + i);

					cout << (char)EnemyShape;

				}
			}

			T3X = T2X;
			T3Y = C.Ystrt + C.L - TowerLength - 1;;
			gotoxy(T3X, T3Y);
			for (int i = 0; i<TowerWidth + 1; i++)
				cout << "=";
			gotoxy(T3X + 1, T3Y + 1);
			cout << "T3" << "(" << C.towers[2].Health << ")";
			gotoxy(C.Xstrt + (3 * C.W / 4), C.Ystrt + (3 * C.L / 4) - 1);
			cout << "(C)";

		}
		else
		{
			if (C.towers[3].Health == 0)
				for (int i = C.L / 2; i < C.L - 1; i++)
				{
					color(FOREGROUND_RED);
					for (int j = 1; j < C.W / 2; j++)
					{
						gotoxy(C.Xstrt + j, C.Ystrt + i);
						cout << (char)EnemyShape;
					}
					color(FOREGROUND_GREY);
				}
			for (int i = C.L / 2; i < C.L - 1; i++)
			{
				for (int j = 1; j < 60 - C.towers[3].TPaved; j++)
				{
					gotoxy(C.Xstrt - j, C.Ystrt + i);
					cout << (char)EnemyShape;
				}
			}
			T4X = T1X;
			T4Y = C.Ystrt + C.L - TowerLength - 1;
			gotoxy(T4X, T4Y);
			for (int i = 0; i<TowerWidth; i++)
				cout << "=";
			gotoxy(T4X + 1, T4Y + 1);
			cout << "T4" << "(" << C.towers[3].Health << ")";
			gotoxy(C.Xstrt + (C.W / 4), C.Ystrt + (3 * C.L / 4) - 1);
			cout << "(D)";
		}
	}
	DrawRegions(C);

	//****************************
	gotoxy(CmdWidth / 2 - 10, CmdHeight - 1);
	cout << "Simulation Time : " << SimulationTime << endl;
}

//////////////////////////////////////////////////////////////////////////////////////

/*A function to draw a single enemy using its distance from the castle*/
void DrawEnemy(enemy *E, int Ypos)
{
	int x, y;
	//First calcuale x,y position of the enemy on the output screen
	//It depends on the region and the enemy distance
	REGION EnemyRegion = E->Region;
	switch (EnemyRegion)
	{
	case A_REG:
		x = CastleXStrt - E->Distance + 1;
		y = (CmdHeight / 2) - (CastleLength / 4) - Ypos;
		break;
	case B_REG:
		x = CastleXStrt + CastleWidth + E->Distance - 1;
		y = (CmdHeight / 2) - (CastleLength / 4) - Ypos;
		break;
	case C_REG:
		x = CastleXStrt + CastleWidth + E->Distance - 1;
		y = (CmdHeight / 2) + (CastleLength / 4) + Ypos;
		break;
	default:
		x = CastleXStrt - E->Distance + 1;
		y = (CmdHeight / 2) + (CastleLength / 4) + Ypos;

	}

	gotoxy(x, y);

	//set enemy color according to it type
	Etype EnemyType = E->Type;
	switch (EnemyType)
	{
	case PVR:
		color(FOREGROUND_GREEN);
		break;
	case FITR:
		color(FOREGROUND_RED | FOREGROUND_GREEN);//Yellow
		break;
	case SNIPER:
		color(FOREGROUND_BLUE);
		break;
	case SPLIT:
		color(FOREGROUND_LIGHTBLUE);
		break;
	case HEALER:
		color(FOREGROUND_WHITE);
		break;
	default:
		color(FOREGROUND_RED);
	}


	cout << (char)EnemyShape; //Draw the enemy

	color(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
}
///////////////////////////////////////////////////////////////////////////////////////

/*A function to draw a list of enemies and ensure there is no overflow in the drawing*/
//To use this function, you must prepare its input parameters as specified
//Input Parameters:
// enemies [ ] : array of enemy pointers (ALL enemies from all regions in one array)
// size : the size of the array (total no. of enemies)
void DrawEnemies(enemy* enemies, enemy*enemiesHigh, int timeStep, int x)
{
	/*enemy*temp = enemiesLast;
	if (temp!=NULL)temp->next = enemiesHigh;
	else temp = enemiesHigh;*/
	//draw enemies at each region 
	int region = x;
	{
		int CountEnemies = 0;	//count Enemies at the same distance to draw them vertically if they are <= 15 enemy else print number of enemy in the region
		bool draw = true;
		enemy *temp, *temp2;
		for (int distance = ((CmdWidth / 2) - (CastleWidth / 2)); distance>1; distance--)
		{
			temp = enemies;
			temp2 = enemiesHigh;
			CountEnemies = 0;

			while (temp != NULL)
			{
				if (temp->Distance == distance && temp->Region == region /*&& temp->timeArrival == timeStep*/)
				{
					CountEnemies++;
				}
				temp = temp->next;
			}
			while (temp2 != NULL)
			{
				if (temp2->Distance == distance && temp2->Region == region /*&& temp2->timeArrival == timeStep*/)
				{
					CountEnemies++;
				}
				temp2 = temp2->next;
			}
			if (CountEnemies>15)
			{
				draw = false;
				break;
			}

		}
		if (draw)
		{
			for (int distance = ((CmdWidth / 2) - (CastleWidth / 2)); distance>1; distance--)
			{
				temp = enemies;
				temp2 = enemiesHigh;
				CountEnemies = 0;

				while (temp != NULL)
				{
					if (temp->Distance == distance && temp->Region == region)
					{
						DrawEnemy(temp, CountEnemies);
						CountEnemies++;
					}
					temp = temp->next;
				}
				while (temp2 != NULL)
				{
					if (temp2->Distance == distance && temp2->Region == region)
					{
						DrawEnemy(temp2, CountEnemies);
						CountEnemies++;
					}
					temp2 = temp2->next;
				}

			}


		}
		else // print message maximum reached in this region
		{
			int x; int y;
			if (region == A_REG)
			{
				x = CastleXStrt - 30;
				y = (CmdHeight / 2) - (CastleLength / 4);
			}
			else if (region == B_REG)
			{
				x = CastleXStrt + CastleWidth + 30;
				y = (CmdHeight / 2) - (CastleLength / 4);


			}
			else if (region == C_REG)
			{
				x = CastleXStrt + CastleWidth + 30;
				y = (CmdHeight / 2) + (CastleLength / 4);

			}
			else
			{
				x = CastleXStrt - 30;
				y = (CmdHeight / 2) + (CastleLength / 4);

			}
			gotoxy(x, y);
			cout << "Maximum limit";
		}

	}
	gotoxy(0, CmdHeight - 1);
}
///////////////////////////////////////////////////////////////////////////////////////

/*Use this function to print a message, statistics to the user*/
void PrintMsg(char*msg)
{
	cout << msg;
}