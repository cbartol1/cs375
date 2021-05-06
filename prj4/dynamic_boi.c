#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>

typedef struct{
	int profit;
	int weight;
	int ratio;
	int val;
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

void dynamic(int cap, item* arr, item* newarr1, item* newarr2, int size){
	for(int i = 0; i < size; i++){
		for(int c = 1; c < size+1; c++){
			if(arr[i].weight <= c && newarr1[c - arr[i].weight].price + arr[i].price > newarr1[c].price){
				newarr2[c].price = newarr1[c - arr[i-1].weight].price + arr[i-1].price;
			}
			else{
				newarr2[c].price = newarr1[c].price;
			}
		}
		for(int c = 1; c < size+1; c++){
                        newarr1[c].price = newarr2[c].price;
			newarr1[c].weight = newarr2[c].weight;
			newarr2[c].price = 0;
			newarr2[c].weight = 0;
                }
	}
}
