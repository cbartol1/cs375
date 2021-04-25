#include<stdio.h>
#include<string.h>
#include<stdlib.h>

typedef struct{
	int profit;
	int weight;
	int ratio;
	float knap;
	int optimal;
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

int kwf2(int i,int weight, int profit, item* arr, int c, int size){
	int bound = profit;
	for(int j = i; j < size; j++)
		arr[j].knap = 0;
	while((weight < c) && (i <= size)){
		if(weight + arr[i].weight <= c){
			arr[i].knap = 1;
			weight += arr[i].weight;
			bound += arr[i].profit;
		}
		else{
			arr[i].knap = (c-weight)/arr[i].weight;
			weight = c;
			bound += (arr[i].profit * arr[i].knap);
		}
		i++;
	}
	return bound;
}

int promising(int i, item* arr, int c, int size, int weight, int profit, int maxprofit){
	if(weight >= c) return 0;
	int bound = kwf2(i, weight, profit, arr, c, size);
	//printf("%d\n", bound);
	if(bound > maxprofit) return 1;
	return 0;
}

void knapsack(int i, int profit, int weight, int c, int maxprofit, item* arr, int* optimal, int size, int* include){
	if(weight <= c && profit > maxprofit){
		//printf("changed!");
		maxprofit = profit;
		//numbest = i;
		for(int i = 0; i < 3; i ++){
                	optimal[i] = include[i];
        	}
	}
	if(promising(i, arr, c, size, weight, profit, maxprofit)){
		include[i+1] = 1;
		knapsack(i+1, profit + arr[i+1].profit, weight + arr[i+1].weight, c, maxprofit, arr, optimal, size, include);
		include[i+1] = 0;
		knapsack(i+1, profit, weight, c, maxprofit, arr, optimal, size, include);
	}
}

void backtrack(int c, item* arr, item* newarr, int size){
	greedy2(c, arr, newarr, size);
	int maxprofit = 0;
	for(int i = 0; i < size; i++){
		maxprofit += newarr[i].profit;
	}
	int optimal[3];
	optimal[0] = 0;
	optimal[1] = 0;
	optimal[2] = 1;
	int include[3];
	for(int i = 0; i < 3; i ++){
                include[i] = 0;
        }
	//int numbest = 0;
	knapsack(0, 0, 0, c, maxprofit, arr, optimal, size, include);
	for(int i = 0; i < 3; i ++){
		printf("%d, %d\n", optimal[i], include[i]);
	}
	for(int i = 0; i < size; i++){
		if(optimal[i+1]) printf("%d, %d, %d\n", arr[i].profit, arr[i].weight, arr[i].ratio);
	}
}

int main(int argc, char* argv[]){
	//int maxprofit = 0;
	item arr[2];
	arr[0].profit = 5;
	arr[0].weight = 7;
	arr[0].ratio = 0;
	arr[1].profit = 8;
	arr[1].weight = 4;
	arr[1].ratio = 2;
	item newarr[2];
	sort(arr, 2);
	backtrack(10, arr, newarr, 2);
	//greedy2(10, arr, newarr, 2);
	//printf("%d\n", (sizeof(arr)/sizeof(arr[0])));
	//for(int i = 0; i < 2; i++){
		//printf("%d, %d, %d\n", newarr[i].profit, newarr[i].weight, newarr[i].ratio);
	//}
}
