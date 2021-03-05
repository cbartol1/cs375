#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>

typedef struct{
char* name;
int val;
}inputCards;

typedef struct{
char* name;
int listVal;
int markVal;
}cardList;

int optimalCards = 0;
inputCards* optimalNames;

int ComputeMaxSteal(cardList* cards, int cash, int subsets, int bits){
        int maxSteal = 0;
        int totCost = 0;
	int newCost = 0;
	int sntl = 0;
	int steal = 0;
        int numCards = bits;
	int bitval;
	//printf("%d\n", numCards);
	cardList items[numCards];
        //cardList optimal[numCards];
        for(int i = 0; i < numCards; i++){
		//printf("%d\n", cards[i].listVal);
		//printf("%d\n", cards[i].markVal);
                totCost = totCost + cards[i].listVal;
        }
	//printf("%d\n", totCost);
        if(totCost <= cash){
		for(int i = 0; i < numCards; i++){
                	maxSteal = maxSteal + cards[i].markVal;
        	}
		//printf("%d\n", maxSteal);
		int r = maxSteal - totCost;
		optimalCards = numCards;
		optimalNames = (inputCards*)malloc(sizeof(inputCards)*optimalCards);
                for(int r = 0; r < optimalCards; r++){
                        //printf("hit\n");
                        optimalNames[r].name = cards[r].name;
                        optimalNames[r].val = cards[r].listVal;
                }
                return r;
        }
	totCost = 0;
        for(int i = 0; i < subsets; i++){
		bitval = 0;
		//printf("%d", i);
		for(int r = 0; r < sizeof(items)/sizeof(items[0]); r++){
                        //optimal[r] = items[r];
			items[r].name = "";
                        items[r].listVal = 0;
                	items[r].markVal = 0;
                }
		for(int j = 0; j < bits; j++){
			if((i >> j) & 1){
				//newCost = newCost + cards[j].listVal;
				//printf("hit\n");
				//items[sntl].name = cards[j].name;
				bitval++;
				items[sntl].name = cards[j].name;
				items[sntl].listVal = cards[j].listVal;
				//printf("%d\n", items[sntl].listVal);
				items[sntl].markVal = cards[j].markVal;
				//printf("%d\n", items[sntl].markVal);
				sntl++;
			}
			//else printf("miss\n");
		}
		sntl = 0;
		for(int r = 0; r < sizeof(items)/sizeof(items[0]); r++){
			//printf("%d\n", items[r].listVal);
			newCost = newCost + items[r].listVal;
			//printf("%d\n", newCost);
		}
		//printf("%d\n", newCost);
		for(int r = 0; r < sizeof(items)/sizeof(items[0]); r++){
			//printf("%d\n", items[r].listVal);
                        steal = steal + items[r].markVal;
			//printf("%d\n", steal);
                }
		steal = steal - newCost;
		//printf("%d\n", steal);
		if(newCost <= cash){
			if(steal > maxSteal){
				maxSteal = steal;
				optimalCards = bitval;
				//free(optimalNames);
				optimalNames = calloc(bitval, sizeof(inputCards));
				for(int r = 0; r < bitval; r++){
                        		optimalNames[r].name = items[r].name;
					optimalNames[r].val = items[r].listVal;
					items[r].listVal = 0;
					items[r].markVal = 0;
                		}
			}
		}
		newCost = 0;
		steal = 0;
	}
	//printf("hit\n");
	//optimalNames = (inputCards*)malloc(sizeof(inputCards)*optimalCards);
		//for(int r = 0; r < optimalCards; r++){
			//printf("hit\n");
                	//optimalNames[r].name = items[r].name;
                        //optimalNames[r].val = items[r].listVal;
                //}
	return maxSteal;
}

int main(int argc, char* argv[]){
	//clock_t t;
	//t = clock();
	FILE *fpm;
	FILE *fpl;
	FILE *fp;
	//char* buff1[255];
	//char* buff2[255];
	int numCards;
	int profit;
	int cash;
	int lines = 0;
	int mLines = 0;
	int sntl1 = 0;
	int sntl2 = 0;
	//char* test1;
	//int test2;
	//inputCards markList[2];
	for(int i = 1; i < argc; i++){
		if(strcmp(argv[i], "-m") == 0){
			fpm = fopen(argv[i+1], "r");
			char b = getc(fpm);
			while(b != EOF){
				if(b == '\n') mLines++;
                                b = getc(fpm);
                        }
                        fclose(fpm);
			fpm = fopen(argv[i+1], "r");
			//char buff1[(mlines*2)-1][255];
		}
		if(strcmp(argv[i], "-p") == 0){
			fpl = fopen(argv[i+1], "r");
			char c = getc(fpl);
			while(c != EOF){
				if(c == '\n') lines++;
				c = getc(fpl);
			}
			fclose(fpl);
			//printf("%d lines\n", lines);
			fpl = fopen(argv[i+1], "r");
			//char buff2[lines*2][255];
		}
	}
	char buff1[(mLines*2)-1][255];
	char buff2[lines*2][255];
	fgets(buff1[0], 255, (FILE*)fpm);
	numCards = atoi(buff1[0]);
	inputCards markList[numCards];
	sntl1++;
	for(int i = 0; i < numCards; i++){
		fscanf(fpm, "%s", buff1[sntl1]);
		markList[i].name = buff1[sntl1];
		sntl1++;
		//printf("%s\n", markList[i].name);
		fgets(buff1[sntl1], 255,(FILE*)fpm);
		markList[i].val = atoi(buff1[sntl1]);
		sntl1++;
		//printf("%d\n", markList[i].val);
		//printf("%s\n", markList[i].name);
		//sntl++;
	}
	//printf("%s\n", markList[0].name);
	//printf("%s\n", markList[1].name);
	//printf("%d\n", markList[0].val);
	//printf("%d\n", markList[1].val);
	int n = 0;
	do{
		fscanf(fpl, "%d", &numCards);
		//printf("%d\n", numCards);
		inputCards priceList[numCards];
		fgets(buff2[sntl2], 255, (FILE*)fpl);
		cash = atoi(buff2[sntl2]);
		sntl2++;
		//printf("%d\n", numCards);
		//printf("%d\n", cash);
		n++;
		for(int i = 0; i < numCards; i++){
			fscanf(fpl, "%s", buff2[sntl2]);
                	priceList[i].name = buff2[sntl2];
			sntl2++;
                	//printf("%s\n", priceList[i].name);
                	fgets(buff2[sntl2], 255,(FILE*)fpl);
                	priceList[i].val = atoi(buff2[sntl2]);
			sntl2++;
			//printf("%s\n", priceList[i].name);
                	//printf("%d\n", priceList[i].val);
			n++;
		}
		//printf("%s\n", priceList[0].name);
		//printf("%s\n", priceList[1].name);
		cardList list[numCards];
		int flag = 0;
		for(int i = 0; i < numCards; i++){
			//printf("%s\n", priceList[i].name);
			for(int j = 0; j < sizeof(markList)/sizeof(markList[0]); j++){
				//printf("%s\n", markList[j].name);
				if(strcmp(priceList[i].name, markList[j].name) == 0){
					list[flag].name = priceList[i].name;
					//printf("%s\n", list[flag].name);
					list[flag].listVal = priceList[i].val;
					//printf("%d\n", list[flag].listVal);
					list[flag].markVal = markList[j].val;
					//printf("%d\n", list[flag].markVal);
					flag++;
					break;
				}
			}
		}
		fp = fopen("output.txt", "a");
		clock_t t;
        	t = clock();
		profit = ComputeMaxSteal(list, cash, (numCards*numCards)-1, numCards);
		//printf("%d\n", ComputeMaxSteal(list, cash, (numCards*numCards)-1, numCards));
		t = clock()-t;
        	double time_taken = ((double)t)/CLOCKS_PER_SEC;
		fprintf(fp, "%d input cards\n", numCards);
		fprintf(fp, "%d dollars profit\n", profit);
		fprintf(fp, "%d cards to achieve max profit\n", optimalCards);
		fprintf(fp, "%f time to execute (in seconds)\n", time_taken);
		for(int i = 0; i < optimalCards; i++){
			fprintf(fp, "Name = %s, cost = %d\n", optimalNames[i].name, optimalNames[i].val);
		}
		free(optimalNames);
		fclose(fp);
        	//printf("this took %f seconds to execute\n", time_taken);
		//printf("this required %d cards\n", optimalCards);
	}while(n < lines);
	//cardList list[3];
	//list[0].name = "JimRice1975";
	//list[0].markVal = 1000;
	//list[0].listVal = 80;
	//list[1].name = "HonusWagner1933";
        //list[1].markVal = 2000;
        //list[1].listVal = 202;
	//list[2].name = "DerekJeter1996";
        //list[2].markVal = 300;
        //list[2].listVal = 120;
	//printf("%d\n", ComputeMaxSteal(list, 200, 8, 3));
	//printf("%d\n", numCards);
	//printf("%d\n", atoi(buffer));
	//t = clock()-t;
	//double time_taken = ((double)t)/CLOCKS_PER_SEC;
	//printf("this took %f seconds to execute", time_taken);
	fclose(fpm);
	fclose(fpl);
	return 0;
}
