#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>

typedef struct{
	int price;
	int weight;
	//int ratio;
	//int val;
} item;

//psuedocode:
//setup the array with 0's on the outside, for this one its only 2 rows
//loop through the columns 1 to C
//if (wi <= c) and (P[i – 1, c – wi] + pi > P[i – 1, c])
//P[i, c] = P[i – 1, c – wi] + pi
//else P[i, c] = P[i – 1, c]

//after that, move everything from the second row to the first row
//and make the second row all 0's, then repeat until all the inputs are in
//then the last val is the max profit (i think)

void dynamic(int cap, item* arr, int* newarr1, int* newarr2, int size){
	for(int i = 0; i < size; i++){
		for(int c = 1; c < cap+1; c++){
			if(arr[i].weight <= c && newarr1[c - arr[i].weight] + arr[i].price > newarr1[c]){
				newarr2[c] = newarr1[c - arr[i].weight] + arr[i].price;
			}
			else{
				newarr2[c] = newarr1[c];
			}
		}
		for(int c = 1; c < cap+1; c++){
                        newarr1[c] = newarr2[c];
			//newarr1[c].weight = newarr2[c].weight;
			newarr2[c] = 0;
			//newarr2[c].weight = 0;
                }
	}
}

int main(int argc, char* argv[]){
	//int cap = 16;
	//item arr[4];
	//arr[0].price = 40;
	//arr[0].weight = 2;
	//arr[1].price = 30;
	//arr[1].weight = 5;
	//arr[2].price = 50;
	//arr[2].weight = 10;
	//arr[3].price = 10;
	//arr[3].weight = 5;
	//int newarr1[17];
	//int newarr2[17];
	//for(int i = 0; i < 17; i++){
		//newarr1[i] = 0;
		//newarr2[i] = 0;
	//}
	//dynamic(cap, arr, newarr1, newarr2, 4);
	//printf("%d\n", newarr1[16]);
	FILE *fp;
	FILE *fpo;
	char buff[10000];
	int nlines = 0;
	int n = 0;
	int numItems = 0;
	int cap;
	int alg = atoi(argv[3]);
	clock_t start, end;
	double cpu_time_used;

	fp = fopen(argv[1], "r");
	char b = getc(fp);
	while(b != EOF){
		if(b == '\n') nlines++;
		b = getc(fp);
	}
	fclose(fp);

	fp = fopen(argv[1], "r");
	fpo = fopen(argv[2], "a");

	do{
		fscanf(fp, "%d", &numItems);
		fgets(buff, 10000, fp);
		cap = atoi(buff);
		n++;
		//printf("%d, %d\n", numItems, cap);
		item arr[numItems];
		int newarr1[cap+1];
		int newarr2[cap+1];
		//maxProfit = 0;
		for(int i = 0; i < numItems; i++){
			fscanf(fp, "%d", &arr[i].weight);
			//if(numItems==1000) b = getc(fp);
			fgets(buff, 10000, fp);
                        arr[i].price = atoi(buff);
			n++;
		}
		for(int i = 0; i <= cap; i++){
			newarr1[i] = 0;
			newarr2[i] = 0;
		}
		if(alg == 3){
			start = clock();
			dynamic(cap, arr, newarr1, newarr2, numItems);
			end = clock();
			cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
			cpu_time_used *= 1000;
			fprintf(fpo, "Dynamic Programming: %d %d %f\n", numItems, newarr1[cap], cpu_time_used);
		}
	}while(n < nlines);
	fclose(fp);
	fclose(fpo);
}
