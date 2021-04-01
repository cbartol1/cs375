#include<stdio.h>
#include<string.h>
#include<stdlib.h>


typedef struct{
	int id;
	int points;
} contestant;

typedef struct{
	int size;
	contestant *c;
} heap;

void
findContestant(int id, heap* list){
	if(id > (sizeof(list)/sizeof(list[0])) || list[id].id != id){
		printf("Contestant %d is not in the extended heap");
	}
	else{
		printf("Contestant %d is in the exnended heap with score %d\n", id, list[id].points);
	}
}

void
insertContestant(int id, int score, heap* list){
	
}

void
eliminateWeakest(heap* list){

}

void
earnPoints(int id, int points, heap* list){

}

void
lostPoints(int id, int points, heap* list){

}

void
showContestants(heap* list){

}

void
showHandles(heap* list){

}

void
showLocation(int id, heap* list){

}

void
crownWinner(heap* list){

}
