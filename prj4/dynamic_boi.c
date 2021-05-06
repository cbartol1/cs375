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
	int cap = 16;
	item arr[4];
	arr[0].price = 40;
	arr[0].weight = 2;
	arr[1].price = 30;
	arr[1].weight = 5;
	arr[2].price = 50;
	arr[2].weight = 10;
	arr[3].price = 10;
	arr[3].weight = 5;
	int newarr1[17];
	int newarr2[17];
	for(int i = 0; i < 17; i++){
		newarr1[i] = 0;
		newarr2[i] = 0;
	}
	dynamic(cap, arr, newarr1, newarr2, 4);
	printf("%d\n", newarr1[16]);
}
