#include<stdio.h>
#include<string.h>

typedef struct{
char* name;
int val;
}inputCards;

typedef struct{
char* name;
int listVal;
int markVal;
}cardList;

int ComputeMaxSteal(cardList* cards, int cash, int subsets, int bits){
        int maxSteal = 0;
        cardList* items;
        cardList* optimal;
        int totCost = 0;
	int newCost = 0;
	int sntl = 0;
	int steal = 0;
        int numCards = sizeof(cards)/sizeof(cards[0]);
        for(int i = 0; i < numCards; i++){
                totCost = totCost + cards[i].listVal;
        }
        if(totCost <= cash){
                return totCost;
        }
	else totCost = 0;
        for(int i = 0; i < subsets; i++){
		for(int j = 0; j < bits; j++){
			if((i >> j) & 1){
				items[sntl].name = cards[j].name;
				items[sntl].listVal = cards[j].listVal;
				items[sntl].markVal = cards[j].markVal;
				sntl++;
			}
		}
		for(int r = 0; r < sizeof(items)/sizeof(items[0]); r++){
			newCost = newCost + items[r].listVal;
		}
		for(int r = 0; r < sizeof(items)/sizeof(items[0]); r++){
                        steal = steal + items[r].markVal;
                }
		steal = steal - newCost;
		if(newCost < cash){
			if(steal > maxSteal){
				maxSteal = steal;
				for(int r = 0; r < sizeof(items)/sizeof(items[0]); r++){
                        		optimal[r] = items[r];
					items[r].listVal = 0;
					items[r].markVal = 0;
                		}
			}
		}
		newCost = 0;
		steal = 0;
	}
	return maxSteal;
}

int main(int argc, char* argv[]){
	return 0;
}
