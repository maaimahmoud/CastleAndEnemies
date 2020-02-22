#include "listOperations.h"
#include"Simulation.h"

void inputfromfile(enemy *&inactiveHead, enemy *&inactiveLast, double &c1, double &c2, double &c3, int &TH, int &N, int &TP)		//Take Data From File
{
	int region, type;
	enemy data;
	ifstream infile("input.txt");
	infile >> TH >> N >> TP;		//Take Tower Parameter
	infile >> c1 >> c2 >> c3;		//Take Enemy Priority
	while (infile >> data.ID >> type >> data.timeArrival >> data.Health >> data.power >> data.reloadPriod >> region >> data.speed)
	{
		data.Type = (Etype)type;
		data.Region = (REGION)region;
		data.NumberofSplits = 0;	//Set Number of Splits to 0
		data.Distance = 60;			//Set The Distance Of Each Enemy To 60
		data.RemainingTime = 0;		//Set The Remaining Time For The Enemy To Shoot To 0
		data.fightDelay = -1;		//Set fightDelay to -1 to recognize first shot
		data.killDelay = 0;			//Set KillDelay To 0
		data.Priority = 0;			//Set Priority for all enemies to 0
		insert(inactiveHead, inactiveLast, &data);	//Insert The Enemy To The Inavctive List
	}
}

void Out(castle ct, enemy *Killed, enemy *inactiveHead, double TH)
{
	ofstream outfile("output7.txt");
	outfile << "\tKTS\tS\tFD\tKD\tFT\n";
	enemy *k = Killed; int i = 1;

	//Print The Data Of The Killed Enemies
	while (k)
	{
		outfile <<i<<"\t"<< k->killDelay+k->fightDelay+k->timeArrival << "\t" << k->ID << "\t" << k->fightDelay << "\t" << k->killDelay << "\t" << k->fightDelay+k->killDelay << "\n";
		k = k->next; i++;
	}

	//Print The Damage In All Towers
	outfile << "T1_Total_Damage\tT2_Total_Damage\tT3_Total_Damage\tT4_Total_Damage\n";
	for (int i = 0; i < 4; i++)
	{
		outfile << TH - ct.towers[i].Health << "  \t";
	}

	//Print The Unpaved Distance In The Castle
	outfile <<"\nR1_Distance\tR2_Distance\tR3_Distance\tR4_Distanc\n";
	for (int i = 0; i < 4; i++)
	{
		outfile << 60 - ct.towers[i].TPaved << "\t\t";
	}

	//Check If The Game Is Win Or Lose
	if (ct.towers[0].Health > 0 || ct.towers[1].Health > 0 || ct.towers[2].Health > 0 || ct.towers[3].Health > 0)
	{
		outfile << "\nGame Is Win\n";
		outfile << "Total Enemies\t= " << countList(Killed) << "\n";			//Print The Total Number Of Killed Enemies
		outfile << "Average Fight Delay\t= " << Avarage(Killed, 'f') << "\n";	//Print The Avarage Fight Deley
		outfile << "Average Kill Delay\t= " << Avarage(Killed, 'k') << "\n";	//Print The Avarage Kill Delay
	}
	else
	{
		outfile<< "\nGame Is Loss\n";
		outfile << "Total Killed Enemies\t= " << countList(Killed) << "\n";
		int counter = 0;

		//Count The Number Of The Alive Enemies
		for (int i = 0; i < 4; i++)
		{
			counter += countList(ct.towers[i].active) + countList(ct.towers[i].high);
		}
		outfile << "Total Alive Enemies\t= " << counter + countList(inactiveHead) << "\n";		//Print The Number Of Alive Enemies
		outfile << "Average Fight Delay\t= " << Avarage(Killed, 'f') << "\n";
		outfile << "Average Kill Delay\t= " << Avarage(Killed, 'k') << "\n";
	}
}

double Avarage(enemy *head, char ch)
{
	double count = 0;
	double sum = 0;
	if (head == NULL) return 0;
	if (ch == 'f')
	{
		while (head)
		{
			sum += head->fightDelay;
			count ++;
			head = head->next;
		}
		return sum  / count;
	}
	else if (ch == 'k')
	{
		while (head)
		{
			sum += head->killDelay;
			count ++;
			head = head->next;
		}
		if (count != 0) return (sum  / count);
	}
	return 0 ;
}