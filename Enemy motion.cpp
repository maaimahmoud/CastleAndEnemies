#include"Enemy motion.h"
#include"listOperations.h"

void DecreseDistance(castle&ct)						//Decreasing The Distance Of The Enemies
{
	enemy *temp;
	for (int i = 0; i < 4; i++)
	{
		int PavedDistance = 0;						//parameter to recognize the paved distance at current timestep so as to other enemies can't enter this recently paved area (except pavers can enter)
													//if there is no paved distance in current tower PavedDistance will remain 0
		temp = ct.towers[i].active;
		while (temp != NULL)
		{
			if (temp->Distance != 3)				//if enemy distance = 3 it can't move anymore
			{
				if (temp->Type == 3)				//if enemy is SNIPER it will move by its speed until distance 45 and shoot tower from its position
				{
					if (temp->Distance - temp->speed >= 45)
						temp->Distance = temp->Distance - temp->speed;
					else
						temp->Distance = 45;
				}
				else if (temp->Type == 0)			//if enemy is PAVER it will move by its speed until reaching unpaved distance and then paving it by its power
				{
					if (temp->Distance - temp->speed > 60 - ct.towers[i].TPaved)
					{
						temp->Distance = temp->Distance - temp->speed;
					}
					else
					{
						temp->Distance = 60 - ct.towers[i].TPaved + 1;

						if (temp->RemainingTime == 0)					//Check if enemy's reload period is over (ready to pave )or not
						{
							if (temp->Distance - temp->power <= 2)		//if PAVER's power is greater than the rest of unpaved distance it will stop at distance 3 and the tower paved distance will be 58
							{
								PavedDistance = 58 - ct.towers[i].TPaved;
								ct.towers[i].TPaved = 58;
							}
							else
							{
								ct.towers[i].TPaved = ct.towers[i].TPaved + temp->power;
								PavedDistance = temp->power;
							}
							temp->RemainingTime = temp->reloadPriod;
						}
						else
							temp->RemainingTime--;
					}
				}
				else
						if (temp->Distance - temp->speed > 60 - ct.towers[i].TPaved + PavedDistance)	//if enemy is FIGHTER it will remove by its speed normally until it reaches unpaved distance or recenetly paved
							temp->Distance = temp->Distance - temp->speed;
						else
							temp->Distance = 60 - ct.towers[i].TPaved + PavedDistance + 1;
			}
			temp = temp->next;
		}
		temp = ct.towers[i].high;
		while (temp != NULL)
		{
			if (temp->Distance != 3)																	//if enemy distance = 3 it can't move anymore
			{
				if (temp->Distance - temp->speed > 60 - ct.towers[i].TPaved + PavedDistance)			//if enemy is SHILDED or SPLITER it will remove by its speed normally until it reaches unpaved distance or recenetly paved
					temp->Distance = temp->Distance - temp->speed;
				else
					temp->Distance = 60 - ct.towers[i].TPaved + PavedDistance + 1;

			}
			temp = temp->next;
		}
	}
}

void CheckTowers(castle&ct, enemy*&head)						//Check If Any Tower Is Damaged -> Move Its Enemies To The Next Tower
{
	for (int i = 0; i < 4; i++)
	{
		if (ct.towers[i].Health <= 0)
		{
			REGION destination;				//destination as data type region -> to get which region in active enemies will be moved to
			if (ct.towers[i].active != NULL)
			{
				ChangeRegion(ct, ct.towers[i].active);			//change region for all enemies in killed region
				destination = ct.towers[i].active->Region;
				MergeSorted(ct.towers[destination].active, ct.towers[destination].activelast, ct.towers[i].active, ct.towers[i].activelast);	//to merge the two active lists sorted by timearrival
			}
			if (ct.towers[i].high != NULL)
			{
				ChangeRegion(ct, ct.towers[i].high);				//change region for all enemies in killed region
				destination = ct.towers[i].high->Region;		
				if (ct.towers[destination].highlast == NULL)		//if the tower we move enemies to has no active enemies
				{ 
					ct.towers[destination].high = ct.towers[i].high;
					ct.towers[destination].highlast = ct.towers[i].highlast;
				}
				else {
					ct.towers[destination].highlast->next = ct.towers[i].high;
					ct.towers[destination].highlast = ct.towers[i].highlast;
				}
				ct.towers[i].high = ct.towers[i].highlast = NULL;
			}
			if (head != NULL)				//Now change region for inactive enemies for dead tower
				ChangeRegion(ct, head);
		}
	}
}

void ChangeRegion(castle&ct, enemy*temp)
{
	while (temp != NULL)
	{
		while (ct.towers[temp->Region].Health <= 0)					//If The Next Tower Is Already Killed Before -> Move The Enemies To The Next Tower
		{
			if (temp->Region == A_REG) temp->Region = B_REG;
			else if (temp->Region == B_REG) temp->Region = C_REG;
			else if (temp->Region == C_REG) temp->Region = D_REG;
			else temp->Region = A_REG;

			if (temp->Distance <= 60 - ct.towers[temp->Region].TPaved && ct.towers[temp->Region].Health > 0)	 //to Move The Enemy To the Paved Ditance Only of new region
				temp->Distance = 60 - ct.towers[temp->Region].TPaved;
		}
		temp = temp->next;
	}
}