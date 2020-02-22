//#include "utility.h"
#include "listOperations.h"

bool isEmpty(enemy *&head)
{
	if(head == NULL)
		return true;
	return false;
}

void insert(enemy *&head, enemy *&last, enemy *data)		//Insert A New Enemy In A List [It Insert As A Queue]
{
	enemy *temp = new enemy;
	*temp = *data;
	temp->next = NULL;
	if(isEmpty(head))
	{
		head = temp;
		last = temp;
	}
	else
	{
		last->next = temp;
		last = temp;
	}
}

int countList_byregion(enemy*head, int x)		//count elements in list for a certain region
{
	int count = 0;
	enemy*temp = head;
	while (temp != NULL)
	{
		if (temp->Region == x) count++;
		temp = temp->next;
	}
	return count;
}

int countList(enemy*head)			//Count The Enemies Of The List
{
	int count = 0;
	enemy*temp = head;
	while (temp != NULL)
	{
		count++;
		temp = temp->next;
	}
	return count;
}

void destroy(enemy *&head, enemy *&last)		//Delete All The Enemies In The List
{
		enemy*temp = head;
		while (temp != NULL)
		{
			head = head->next;
			delete temp;
			temp = head;
		}
		last = NULL;
}

void remove_from_beg(enemy*&head,enemy*&last)	//Remove first enemy in the list
{
	if (isEmpty(head)) return;
	enemy*temp = head;
	head = head->next;
	if (head == NULL) last = NULL;
	delete temp;
}

void MergeSorted(enemy*&head, enemy*&last, enemy*&appended, enemy*&appendedlast)	//Merge 2 sorted lists by arrival time
{
	enemy*temp = head;
	enemy*temp_pre = head;
	enemy*temp2;
	if (head == NULL)
	{
		head = appended;
		while (appended->next != NULL)
			appended = appended->next;
		last = appended;
		appended = NULL;
		return;
	}
	while (temp != NULL && appended != NULL)
	{
		if (appended->timeArrival <= temp->timeArrival)
		{
			temp2 = appended;
			appended = appended->next;
			if (temp == head)
			{
				head = temp2;
				temp2->next = temp;
				temp_pre = head;
			}
			else
			{
				temp_pre->next = temp2;
				temp_pre = temp_pre->next;
				temp2->next = temp;
			}
		}
		else
		{
			temp_pre = temp;
			temp = temp_pre->next;
		}
	}

	if (appended != NULL)
	{
		last->next = appended;
		last = appendedlast;
	}
	appended = appendedlast = NULL;
}