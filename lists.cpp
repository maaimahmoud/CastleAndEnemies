#include "listOperations.h"
#include "Lists.h"

void activeList(enemy *&inactiveHead, enemy*&inactiveLast, castle&ct, int timeStep)		//Make The Active List each timestep
{
	enemy *temp = inactiveHead;
	while (temp != NULL && temp->timeArrival == timeStep)
	{
		if (temp->Type != 2 && temp->Type != 4)
			insert(ct.towers[temp->Region].active, ct.towers[temp->Region].activelast, temp);		//Insert The Enemy In The Active List If Have Low Priority
		else
			insert(ct.towers[temp->Region].high, ct.towers[temp->Region].highlast, temp);			//Insert The Enemy In The Active List for high If Have High Priority															
		temp = temp->next;
		remove_from_beg(inactiveHead,inactiveLast);																	//Removing This Enemy From The Inactive List
	}
}

void enemy_killed(castle&ct, int timestep, enemy*&killedHead, enemy*&killedLast)	//Make the killed List each timestep
{
	enemy*deleted = NULL;
	enemy*deletedlast = NULL;
	for (int i = 0; i < 4; i++)
	{
		ct.towers[i].Numberofkilled = 0;
		enemy*temp = ct.towers[i].active;
		enemy*temp_pre = ct.towers[i].active;
		enemy*temp2 = ct.towers[i].high;
		enemy*temp2_pre = ct.towers[i].high;
		while (temp != NULL || temp2 != NULL)		//travrse on both active and high priority lists and check if enemy is dead to insert it to deleted list
		{
			if (temp != NULL)
			{
				if (temp->Health <= 0)
				{
					if (temp == ct.towers[i].active)
					{
						ct.towers[i].active = temp->next;
						temp->killDelay = timestep - (temp->fightDelay + temp->timeArrival);
						insert(deleted, deletedlast, temp);
						delete temp;
						temp = temp_pre = ct.towers[i].active;
					}
					else
					{
						temp_pre->next = temp->next;
						temp->killDelay = timestep - (temp->fightDelay + temp->timeArrival);
						insert(deleted, deletedlast, temp);
						delete temp;
						temp = temp_pre->next;
					}
					ct.towers[i].Numberofkilled++;
				}
				else
				{
					temp_pre = temp;
					temp = temp_pre->next;
				}
			}
			if (temp2 != NULL)
			{
				if (temp2->Health <= 0)
				{
					if (temp2 == ct.towers[i].high)
					{
						ct.towers[i].high = temp2->next;
						temp2->killDelay = timestep - (temp2->fightDelay + temp2->timeArrival);
						insert(deleted, deletedlast, temp2);
						delete temp2;
						temp2 = temp2_pre = ct.towers[i].high;
					}
					else
					{
						temp2_pre->next = temp2->next;
						temp2->killDelay = timestep - (temp2->fightDelay + temp2->timeArrival);
						insert(deleted, deletedlast, temp2);
						delete temp2;
						temp2 = temp2_pre->next;
					}
					ct.towers[i].Numberofkilled++;
				}
				else
				{
					temp2_pre = temp2;
					temp2 = temp2_pre->next;
				}
			}

		}
		temp = ct.towers[i].active;
		
		if (temp != NULL)				//get access to the last element of list if it's deleted before
		{
			while (temp->next != NULL)
				temp = temp->next;
		}
		ct.towers[i].activelast = temp;
		temp = ct.towers[i].high;
		if (temp != NULL)
		{
			while (temp->next != NULL)
				temp = temp->next;
		}
		ct.towers[i].highlast = temp;
	}
	if ((ct.towers[0].Numberofkilled+ct.towers[1].Numberofkilled+ ct.towers[2].Numberofkilled+ ct.towers[3].Numberofkilled) == 1) // if 1 enemy is killed it will be inserted directly to the killed list
		insert(killedHead, killedLast, deleted);
	else
		if ((ct.towers[0].Numberofkilled + ct.towers[1].Numberofkilled + ct.towers[2].Numberofkilled + ct.towers[3].Numberofkilled) > 1) //if more than 1 enemy is killed in current timestep they will by sorted by FightDelay -> then inserted to killedlist
		{
			{
				while (deleted != NULL)
				{
					enemy*temp = deleted;
					int FD = temp->fightDelay;
					while (temp != NULL)
					{
						if (temp->fightDelay < FD) FD = temp->fightDelay;
						temp = temp->next;
					}
					temp = deleted;
					if (FD == temp->fightDelay)
					{
						insert(killedHead, killedLast, temp);
						remove_from_beg(deleted, deletedlast);
					}
					else
						while (temp != NULL && temp->next != NULL)
						{
							if (temp->next->fightDelay == FD)
							{
								enemy*Less_FD = temp->next;
								temp->next = Less_FD->next;
								insert(killedHead, killedLast, Less_FD);
								delete Less_FD;
							}
							else
								temp = temp->next;
						}
				}
			}
			destroy(deleted, deletedlast);
		}
}