#define _CRT_SECURE_NO_WARNINGS
#define BUSSES_NO 5
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
int total = 0;

typedef struct Station
{
	int no; // מספר התחנה
	char name[20]; // שם התחנה
	int avGetOn; // ממוצע העולים לאוטובוס בתחנה זו
	int avGetOff; // ממוצע היורדים מהאוטובוס בתחנה זו
	struct Station* next; // מצביע לתחנה הבאה ברשימת התחנות
}Station;

typedef struct Bus
{
	int no;
	int capacity; //קיבולת הנוסעים של האוטובוס
	Station* line; // קו נסיעה המורכב מרשימה מקושרת של תחנות תחנות
}Bus;
Bus* fleet[BUSSES_NO];

Bus* NewBus(int no, int capacity)
{
	Bus* b = (Bus*)malloc(sizeof(Bus));
	b->line = NULL;
	if (b!=NULL) {
	b->capacity = capacity;
	b->no = no;
	}
	else
		printf("broken bus");
	
	return b;
}

Station* NewStation(int no, char name[], int getOn, int getOff)
{
	Station* st;
	st = (Station*)malloc(sizeof(Station));
	st->next = NULL;
	if (st!=NULL)
	{
		st->no = no;
		strcpy(st->name, name);
		st->avGetOff = getOff;
		st->avGetOn = getOn;
	}
	else
		printf("dead station");
	return st;
}

void AddStation(Station* station, Bus* bus)
{
	
	if (bus->line == NULL) 
		bus->line = station;
	else 
		bus->line->next=station;
		total += station->avGetOn - station->avGetOff;
	
}

void PrintStation(Station* station)
{
	Station* st = &station;
	if (station != NULL) {
		printf("\nStation List:\n");
		while (station != NULL) {
			printf(" \tNo:%d Name: %s  getOn:%d  getOff:%d\n", station->no, station->name, station->avGetOn, station->avGetOff);
			station = station->next;
		}
	}
	else  printf("no station"); 
}

void PrintBus(Bus* bus)
{
	printf("bus NO : %d ", bus->no);
	printf("bus capacity : %d\n ", bus->capacity);
}

bool CheckBus(Bus* bus)
{
	if (total < bus->capacity&&total>=0)
		return true;
	else
		return false;
}

void initData()
{
	int i;
	for (i = 0; i < BUSSES_NO; i++) {
		
		if (fleet[i] != NULL) {
			PrintBus(fleet[i]);
			if (CheckBus(fleet[i]))
				printf("\nbus NO %d fits the line...\n",i+1);
			else
				printf("\nbus NO %d does't fits the line\n",i+1);
			printf("---------------------------------------------\n");
		}else{fleet[i] = NULL;}
	}
}

	void main() {
	
	Bus* bus1 = NewBus(1, 50);
	bus1->line = NULL;
	Bus* bus2 = NewBus(2, 40);
	bus2->line = NULL;
	fleet[0] = bus1;
	fleet[1] = bus2; 
	
	Station* st1 = NewStation(50, "station1", 4, 0);
	Station* st2 = NewStation(40, "station2", 21, 3);
	Station* st3 = NewStation(30, "station3", 20, 4);
	Station* st4 = NewStation(20, "station4", 15, 4);
	Station* st5 = NewStation(10, "station5", 5, 2);

	//this line fits the buses
	/*Station* st1 = NewStation(50, "station1", 10, 2);
	Station* st2 = NewStation(40, "station2", 11, 3);
	Station* st3 = NewStation(30, "station3", 10, 5);
	Station* st4 = NewStation(20, "station4", 5, 0);*/

	/*st1->next = st2;
	st2->next = st3;
	st3->next = st4;
	st4->next = NULL*/

    st1->next = st2;
	st2->next = st3;
	st3->next = st4;
	st4->next = st5;
	st5->next = NULL;
	
	AddStation(st1, bus1);
	AddStation(st2, bus1);
	AddStation(st3, bus1);
	AddStation(st4, bus1);
	AddStation(st5, bus1);

	PrintStation(st1);
	
	initData();

}




