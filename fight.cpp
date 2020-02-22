#include "Fight.h"
#include "Lists.h"
#include "listOperations.h"

void checkperiority(enemy*&head, enemy*&last, double C1, double C2, double C3,int N)	//Calculate The priority Of The High Priority Enemies
{
	enemy*temp = head;
	while (temp != NULL)						// calculate priority for each enemy
	{
		temp->Priority = ((temp->power / temp->Distance)*C1 + C2 / (temp->RemainingTime + 1) + temp->Health * C3);
		temp = temp->next;
	}
		enemy*arrangedlast = NULL; enemy*arranged = NULL;

		while (head != NULL)					//Arrange list decending by priority by searching each time for greatest enemy of priority and insert it at the end of the arranged list
		{
			temp = head;
			double Priority = 0;				//set smaller priority to 0 and search for the greatest and then insert it in arranged list

			while (temp != NULL)
			{
				if (temp->Priority > Priority) Priority = temp->Priority;
				temp = temp->next;
			}

			temp = head;

			if (Priority == temp->Priority)		//if the greatest enemy of priority is the head of list -> insert it to arragned list /remove it from beginning
			{
				insert(arranged, arrangedlast, temp);
				remove_from_beg(head, last);
			}
			else
				while (temp != NULL)			//if the greatest enemy of priority is at the middle of the list -> insert it to arranged list / remove it from the middle
				{
					if (temp->next != NULL)

						if (temp->next->Priority == Priority)
						{
							enemy*high_Priority = temp->next;
							insert(arranged, arrangedlast, high_Priority);
							temp->next = high_Priority->next;
							delete high_Priority;
							break;
						}
						else
							temp = temp->next;
				}
			if (countList(arranged) == N)			//if arranged list is now contains N (number of enemies tower can shot) -> sorting is over
			{
				arrangedlast->next = head;			//link the rest of unarranged list at the end of the arranged list
				arrangedlast = last;
				break;
			}
		}
		head = arranged;						//at the end the original list will be empty and head will point to the frist element of the arranged list
		last = arrangedlast;					//and so the last will point to the last element in arranged list
}

void DecreaseHealth_Enemy(enemy*shooted, double TP)			//Dectrease The Health Of The Enemy
{
	double k;
	if (shooted->Type == 2) k = 2;
	else k = 1;
	double DH = ((1/k) * (TP / shooted->Distance));
	if (DH >= shooted->Health)								//IF The Enemy Health < The Value That He Will Loss He Dies
		shooted->Health = 0;
	else
		shooted->Health = shooted->Health - DH;
}

void DecreaseHealth_Tower(Tower&shooted_tower ,enemy*shooter)	//Decrease The Health Of the Tower
{
	double k;
	if (shooter->Type == 2) k = 2;
	else k = 1;
	double DH = (k * shooter->power / shooter->Distance);
	if (DH >= shooted_tower.Health)								//IF The Tower Health < THe Value That It Will Loss It Damaged
		shooted_tower.Health = 0;
	else
		shooted_tower.Health = shooted_tower.Health - DH;
}

void Fight_Tower_Enemy(castle&ct, double C1, double C2, double C3, int TimeStep)	//The Tower Shoot The Enemies
{
	int count;
	for (int i = 0; i < 4; i++)			//Loop On The 4 Towers
	{
		if (ct.towers[i].active == NULL && ct.towers[i].high == NULL) continue;		//If The Lists Are Empty Move To Continue To The Next Tower

		count = 0;

		int NumberofHighPriority = countList(ct.towers[i].high);

		if (NumberofHighPriority > ct.towers[i].N)						//if number of Highpriority enemies is greater than the number of enemies that time shoot
			checkperiority(ct.towers[i].high, ct.towers[i].highlast, C1, C2, C3,ct.towers[i].N);	//Calculate The Priority Of The High Priority Enemies and arrange list descending

		enemy*temp = ct.towers[i].high;
		while (count < ct.towers[i].N && temp != NULL)		// While Loop until The Number Of The Enemies That The Tower Can Shoot At One Time Step Is Complete Or The List Is End
		{
			DecreaseHealth_Enemy(temp, ct.towers[i].towerPower);
			if (temp->fightDelay == -1) temp->fightDelay = TimeStep - temp->timeArrival;
			temp = temp->next;
			count++;
		}
		temp = ct.towers[i].active;
		while (count < ct.towers[i].N && temp != NULL)	//While Loop until The Number Of The Enemies That The Tower Can Shoot At One Time Step Is Complete
		{
			DecreaseHealth_Enemy(temp, ct.towers[i].towerPower);
			if (temp->fightDelay == -1) temp->fightDelay = TimeStep - temp->timeArrival;
			temp = temp->next;
			count++;
		}
	}
}

void Fight_Enemy_Tower(castle&ct, double C1, double C2, double C3)		//The Enemy Shoot The Tower
{
	for (int i = 0; i < 4; i++)
	{
		if (ct.towers[i].active == NULL && ct.towers[i].high == NULL) continue;
		enemy*temp = ct.towers[i].active;
		int count = 0;
		while (temp != NULL)			
		{			
				if (temp->Type != 0 && temp->Type!=5)			//Any Active Enemy Can Shoot The Tower Except The Paver/Spliter
				{
					if (temp->RemainingTime == 0)   //If The Remaining Time For The Enemy = 0 -> The Enemy Can Shoot
					{
						DecreaseHealth_Tower(ct.towers[i], temp);
						temp->RemainingTime = temp->reloadPriod;
					}
					else
						temp->RemainingTime--;
				}
				if (temp->Type == 5) {
					heal(ct.towers[i].active , count, temp);
				}
			temp = temp->next;
			count++;
		}
		temp = ct.towers[i].high;
		while (temp != NULL)
		{
			if (temp->RemainingTime == 0)			//if enemy's reload period is over and can shoot tower(SHILDER) or split (SPLITER)
			{
				if (temp->Type == 4)				//if SPLITER's reload period is over it will split into 2 enemies
				{
					if (temp->NumberofSplits < 3)	//SPLITER is not allowed to Split more than 3 times //Maximum Number of enemies from one SPLITER=8
					{
						temp->NumberofSplits++;
						temp->RemainingTime = temp->reloadPriod;
						Splitter_Split(ct, temp);
					}
				}
					else
					{												//if enemy is SHILDED it will shoot tower
						DecreaseHealth_Tower(ct.towers[i], temp);
						temp->RemainingTime = temp->reloadPriod;
					}
			}
			else
				temp->RemainingTime--;
			temp = temp->next;
		}	
	}
}

void Splitter_Split(castle&ct , enemy*e)		//this function will be called whin SPLITER's reload period is over and can split now->function creates enemy has the same data of SPLITER and get his ID
{
	enemy*splited_enemy = new enemy;
	*splited_enemy = *e;
	splited_enemy->ID = ct.totalNumberofEnemies+1;	//the new ID will be total enemies + 1 ->> so as to there can not be 2 enemies with the same ID
	ct.totalNumberofEnemies++;																//increment total number of active enemies
	insert(ct.towers[e->Region].high, ct.towers[e->Region].highlast, splited_enemy);		//insert enemy in active high priority list
}

void heal(enemy*Head, int index, enemy *Healer)
{
	if (Healer->RemainingTime == 0)
	{
		enemy* temp = Head;
		if (Healer->power > 1) Healer->power = 1;
		if (index != 0)
		{
			if (index == 1)
			{
				if (temp->Type != 5)
					temp->Health = temp->Health + Healer->power;
			}
			else
			{
				int counter = 0;
				while (counter != index - 2) {
					temp = temp->next;
					counter++;
				}
				for (int k = 0; k < 2; k++)
				{
					if (temp->Type != 5)
						temp->Health = temp->Health + Healer->power;
					temp = temp->next;
				}
			}
			Healer->RemainingTime = Healer->reloadPriod;
		}
	}
}