#include "listOperations.h"
#include "Simulation.h"
#include "Fight.h"
#include "Lists.h"
#include "Enemy motion.h"

bool GameOver(castle ct, enemy*head)							//Check If The Castle Or The Enemies Are Killed
{
	return ((head != NULL || ct.towers[0].active != NULL || ct.towers[0].high != NULL || ct.towers[1].active != NULL || ct.towers[1].high != NULL || ct.towers[2].active != NULL || ct.towers[2].high != NULL || ct.towers[3].active != NULL || ct.towers[3].high != NULL) && (ct.towers[0].Health > 0 || ct.towers[1].Health > 0 || ct.towers[2].Health > 0 || ct.towers[3].Health > 0));
}

void Simulation(char Number)
{
	int TH, N, TP;												//Tower Parameters

	double C1, C2, C3;											//Enemy Priority Parameters

	enemy *inactiveHead, *inactiveLast, *killedHead, *killedLast;				//Inactive List And Killed List
	inactiveHead = inactiveLast = killedHead = killedLast = NULL;

	inputfromfile(inactiveHead, inactiveLast, C1, C2, C3, TH, N, TP);			//Take Input From File

	SetWindow();						//adjust game window settings

	castle ct;							// define a castle 

	ct.Xstrt = CastleXStrt;
	ct.Ystrt = CastleYStrt;
	ct.W = CastleWidth;
	ct.L = CastleLength;
	for (int i = 0; i < 4; i++)			//intialize all parametars of towers
	{
		ct.towers[i].TL = TowerLength;
		ct.towers[i].TW = TowerWidth;
		ct.towers[i].Health = TH;
		ct.towers[i].N = N;
		ct.towers[i].towerPower = TP;
		ct.towers[i].active = ct.towers[i].activelast = ct.towers[i].high = ct.towers[i].highlast = NULL;
		ct.towers[i].Numberofkilled = 0;
		ct.towers[i].TPaved = 30;
	}

	if (inactiveHead != NULL )
	ct.totalNumberofEnemies = inactiveLast->ID;  //Detect Total Number of enemies from last element in inActive list


	int TimeStep = 0;		//Set The Time Step To 0
	cin.get();

	///Now a Simulation
	while (GameOver(ct, inactiveHead))											//While Loop until All towers are killed or all enemies
	{
		TimeStep++;																//Increment The Time Step

		CheckTowers(ct, inactiveHead);											// If tower health = 0  move enemies to next region clock wise

		DecreseDistance(ct);											//Decrease The Distance Of The Enemies

		activeList(inactiveHead, inactiveLast, ct, TimeStep);							//Add The Enemies Whose Time Step = Current Time Step To The Active List According To His Region		
																		
		if (Number == '1' || Number == '2')								//If The Mode Of Program is Step By Step Or Interactive Mode Draw The Castle And The Enemies
		{
			DrawCastle(ct, TimeStep);									//Draw The Castle

			for (int i = 0; i < 4; i++)	DrawEnemies(ct.towers[i].active, ct.towers[i].high, TimeStep, i);		//Draw both activeList and high for same region
			
			//If The Mode Of The Program Is The Interactive Mode Print Data for each timestep
			if (Number == '1')
			{
				gotoxy(CmdWidth / 2 - 35 , CmdHeight - 1);
				cout << "active enemies : ";
				gotoxy(CmdWidth / 2-5 , CmdHeight - 1);
				for (int i = 0; i < 4; i++)
				{
					if (i == 0) cout << "A = ";
					else if (i == 1) cout << "B = ";
					else if (i == 2) cout << "C = ";
					else cout << "D = ";
					cout << countList(ct.towers[i].active) + countList(ct.towers[i].high) << " \t";
				}
				cout << endl;
				gotoxy(CmdWidth / 2 - 35, CmdHeight - 1);
				cout << "killed at last time step :";
				gotoxy(CmdWidth / 2-5 , CmdHeight - 1);
				
				for (int i = 0; i < 4; i++)
				{
					if (i == 0) cout << "A = ";
					else if (i == 1) cout << "B = ";
					else if (i == 2) cout << "C = ";
					else cout << "D = ";
					cout << ct.towers[i].Numberofkilled << " \t";
				}
				cout << endl;
				gotoxy(CmdWidth / 2 - 35, CmdHeight - 1);
				cout << "Total killed enemies :";
				gotoxy(CmdWidth / 2-5, CmdHeight - 1);
				
				for (int i = 0; i < 4; i++)
				{
					if (i == 0) cout << "A = ";
					else if (i == 1) cout << "B = ";
					else if (i == 2) cout << "C = ";
					else cout << "D = ";
					cout << countList_byregion(killedHead, i) << " \t";
				}
				cout << endl;
				gotoxy(CmdWidth / 2 - 35, CmdHeight - 1);
				cout << "Unpaved distance:";
				gotoxy(CmdWidth / 2-5, CmdHeight - 1);
				
					for (int i = 0; i < 4; i++)
					{
						if (i == 0) cout << "A = ";
						else if (i == 1) cout << "B = ";
						else if (i == 2) cout << "C = ";
						else cout << "D = ";
						cout << 60 - ct.towers[i].TPaved << " \t";
					}
			}

		}

		Fight_Tower_Enemy(ct, C1, C2, C3, TimeStep);					//The Tower Shoot The Enemies

		Fight_Enemy_Tower(ct, C1, C2, C3);								//The Enemies Shoot The Tower

		enemy_killed(ct, TimeStep, killedHead, killedLast);

		if (Number == '1') cin.get();			//Interactive Mode
		else if (Number == '2') Sleep(1000);	//Delay 1 sec to notice the animation (Step by Step Mode)
	}

	DrawCastle(ct, TimeStep);

	for (int i = 0; i < 4; i++) DrawEnemies(ct.towers[i].active, ct.towers[i].high, TimeStep, i);

	gotoxy(CmdWidth / 2 -5 , CmdHeight - 1);	cout << "Game over" << endl;	//to notice that game is over

	Out(ct, killedHead, inactiveHead, TH);				//Make The Output File

	destroy(killedHead, killedLast);			//Remove all killed enemies from killed list

	destroy(inactiveHead, inactiveLast);

}
