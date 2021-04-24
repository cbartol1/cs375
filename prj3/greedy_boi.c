#include<stdio.h>
#include<string.h>
#include<stdlib.h>

typedef struct{
	int profit;
	int weight;
	int ratio;
} item;

void swap(item *elem1, item *elem2){
	item temp = *elem1;
	*elem1 = *elem2;
	*elem2 = temp;
}

void sort(item* arr, int size){
	int min;
	for(int i = 0; i < size-1; i++){
		min = i;
		for(int j = i+1; j < size; j++){
			if(arr[j].ratio < arr[min].ratio)
				min = j;
		}
		swap(&arr[min], &arr[i]);
	}
}

void greedy1(int c, item* arr, item* newarr, int size){
	int sum = 0;
	//int size = sizeof(arr)/sizeof(arr[0]);
	//int newarr[size];
	//sort(arr, size);
	for(int i = 0; i < size; i++){
		sum += arr[i].weight;
		newarr[i].profit = arr[i].profit;
		newarr[i].weight = arr[i].weight;
		newarr[i].ratio = arr[i].ratio;
		if(sum == c){
			break;
		}
		if(sum >= c){
			newarr[i].weight -= sum - c;
			newarr[i].profit = 0;
			break;
		}
	}
}

void greedy2(int c, item* arr, item* newarr, int size){
	//int size = sizeof(arr)/sizeof(arr[0]);
	//sort(arr, size);
	item maximus;
	int sum = 0;
	maximus.profit = 0;
	maximus.weight = 0;
	maximus.ratio = 0;
	for(int i = 0; i < size; i++){
		if(arr[i].profit >= maximus.profit && arr[i].weight <= c){
			maximus.profit = arr[i].profit;
			maximus.weight = arr[i].weight;
			maximus.ratio = arr[i].ratio;
		}
	}
	//printf("%d, %d\n", maximus.profit, maximus.weight);
	greedy1(c, arr, newarr, size);
	for(int i = 0; i < (sizeof(newarr)/sizeof(newarr[0])); i++){
		sum += newarr[i].profit;
	}
	if(sum < maximus.profit){
		for(int i = 0; i < (sizeof(newarr)/sizeof(newarr[0])); i++){
                	newarr[i].profit = 0;
			newarr[i].weight = 0;
			newarr[i].ratio = 0;
        	}
		newarr[0].profit = maximus.profit;
		newarr[0].weight = maximus.weight;
		newarr[0].ratio = maximus.ratio;
	}
}

void backtrack(){

}

int main(int argc, char* argv[]){
	//int maxprofit = 0;
	item arr[2];
	arr[1].profit = 5;
	arr[1].weight = 7;
	arr[1].ratio = 0;
	arr[0].profit = 8;
	arr[0].weight = 4;
	arr[0].ratio = 2;
	item newarr[2];
	sort(arr, 2);
	greedy2(10, arr, newarr, 2);
	//printf("%d\n", (sizeof(arr)/sizeof(arr[0])));
	for(int i = 0; i < 2; i++){
		printf("%d, %d, %d\n", newarr[i].profit, newarr[i].weight, newarr[i].ratio);
	}
}
