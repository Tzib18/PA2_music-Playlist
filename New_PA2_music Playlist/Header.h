#ifndef HEADER_H
#define HEADER_H
#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
#include <ctype.h>
#include <windows.h>
#include <time.h>


typedef struct Duration
{
	int minutes;
	int seconds;
}Duration;

typedef struct Record {
	char title[100];
	char album[100];
	char artist[100];
	char genre[100];
	Duration length;
	int times_played;
	int rating; // 1-5
}Record;


typedef struct Node
{
	Record record;
	struct Node* pNext;
	struct Node* pPrev;

}Node;

// pList is a phead 

void load(Node** pList);
Node* createSong(Record newsong); 
int storeSong(Node** pList);
int edit_song(Node* pList, Record newsong);
int pause();
int Display(Node* pList);
int rate(Node* pList);
int play(Node* pList);
int insert(Node** pList, Record newsong);
void insertsong(Node** pList);
void deleteSong(Node** pList); 
int sort(Node* pList);
int shuffle(Node* pList);
void main_menu(Node** pList);





#endif