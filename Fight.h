#include "utility.h"

void DecreaseHealth_Enemy(enemy*shooted, double TP);					//Decreasing The Enemy Health When Shot

void checkperiority(enemy*&head,enemy*&last, double C1, double C2, double C3,int N);		//Change The Priority Of The High Priority Enemies

void DecreaseHealth_Tower(Tower&shooted_tower, enemy*shooter);			//Decreasing The Health Of The Tower

void Fight_Enemy_Tower(castle&ct, double, double, double);				//The Enemy Shoot The Tower

void Fight_Tower_Enemy(castle&ct, double, double, double, int);			//The Tower Shoot The Enemy

void Splitter_Split(castle&ct, enemy*e);								//function create new enemy and inserts in list of active high priority enemies

void heal(enemy*Head, int index, enemy *Healer);						//is called only for enemy Healer .. if its Remaining Time = 0 it will provide other enemies with health