#include "utility.h"

bool isEmpty(enemy *&head);												//Check If The Linked List Is Empty

void insert(enemy *&head, enemy *&last, enemy *data);					//Insert In The Linked List at the end

int countList_byregion(enemy*head, int x);								//count elements in list for a certain region

int countList(enemy*head);												//Counting The Number Of The Enemies In The List

void destroy(enemy *&head, enemy *&last);								//Dlelting All The Enemies In The List

void remove_from_beg(enemy*&head,enemy*&last);							//Remove first element in Linkedlist

void MergeSorted(enemy*&head, enemy*&last, enemy*&appended, enemy*&appendedlast);  //Merge 2 sorted lists (sorted by timearrival)