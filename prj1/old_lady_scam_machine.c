#include<stdio.h>
#include<string.h>
#include<stdlib.h>

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
        int totCost = 0;
	int newCost = 0;
	int sntl = 0;
	int steal = 0;
        int numCards = bits;
	//printf("%d\n", numCards);
	cardList items[numCards];
        //cardList optimal[numCards];
        for(int i = 0; i < numCards; i++){
                totCost = totCost + cards[i].listVal;
        }
	//printf("%d\n", totCost);
        if(totCost <= cash){
		for(int i = 0; i < numCards; i++){
                	maxSteal = maxSteal + cards[i].markVal;
        	}
		//printf("%d\n", maxSteal);
		int r = maxSteal - totCost;
                return r;
        }
	else totCost = 0;
        for(int i = 0; i < subsets; i++){
		//printf("first loop");
		for(int j = 0; j < bits; j++){
			if((i >> j) & 1){
				//printf("hit\n");
				items[sntl].name = cards[j].name;
				items[sntl].listVal = cards[j].listVal;
				items[sntl].markVal = cards[j].markVal;
				sntl++;
			}
		}
		sntl = 0;
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
				//for(int r = 0; r < sizeof(items)/sizeof(items[0]); r++){
                        		//optimal[r] = items[r];
					//items[r].listVal = 0;
					//items[r].markVal = 0;
                		//}
			}
		}
		newCost = 0;
		steal = 0;
	}
	return maxSteal;
}

int main(int argc, char* argv[]){
	FILE *fpm;
	FILE *fpl;
	char buffer[255];
	int numCards;
	int cash;
	//char* test1;
	//int test2;
	//inputCards markList[2];
	for(int i = 1; i < argc; i++){
		if(strcmp(argv[i], "-m") == 0) fpm = fopen(argv[i+1], "r");
		if(strcmp(argv[i], "-p") == 0) fpl = fopen(argv[i+1], "r");
	}
	fgets(buffer, 255, (FILE*)fpm);
	numCards = atoi(buffer);
	inputCards markList[numCards];
	for(int i = 0; i < numCards; i++){
		fscanf(fpm, "%s", buffer);
		markList[i].name = buffer;
		//printf("%s\n", markList[i].name);
		fgets(buffer, 255,(FILE*)fpm);
		markList[i].val = atoi(buffer);
		//printf("%d\n", markList[i].val);
		//sntl++;
	}
	for(int i = 0; i < 2; i ++){
		fscanf(fpl, "%d", &numCards);
		//printf("%d\n", numCards);
		inputCards priceList[numCards];
		fgets(buffer, 255, (FILE*)fpl);
		cash = atoi(buffer);
		//printf("%d\n", numCards);
		//printf("%d\n", cash);
		for(int i = 0; i < numCards; i++){
			fscanf(fpl, "%s", buffer);
                	priceList[i].name = buffer;
                	//printf("%s\n", priceList[i].name);
                	fgets(buffer, 255,(FILE*)fpl);
                	priceList[i].val = atoi(buffer);
                	//printf("%d\n", priceList[i].val);
		}
	}
	cardList list[3];
	list[0].name = "JimRice1975";
	list[0].markVal = 1000;
	list[0].listVal = 80;
	list[1].name = "HonusWagner1933";
        list[1].markVal = 2000;
        list[1].listVal = 202;
	list[1].name = "DerekJeter1996";
        list[1].markVal = 300;
        list[1].listVal = 120;
	printf("%d\n", ComputeMaxSteal(list, 200, 9, 3));
	//printf("%d\n", numCards);
	//printf("%d\n", atoi(buffer));
	fclose(fpm);
	fclose(fpl);
	return 0;
}
