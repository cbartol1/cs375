#include<stdio.h>
#include<string.h>
#include<stdlib.h>

#define LCHILD(x) 2 * x + 1
#define RCHILD(x) 2 * x + 2
#define PARENT(x) (x - 1) / 2


typedef struct{
	int id;
	int points;
} contestant;

typedef struct{
	int size;
	int cap;
	contestant *c;
} heap;

typedef struct{
	int flag;
	int spot;
} handle;

heap *makeHeap(int size){
	heap *min = (heap*) malloc(sizeof(heap));
	min->size = 0;
	min->cap = 5;
	return min;
}

void switcheroo(contestant *c1, contestant *c2){
        contestant temp = *c1;
        *c1 = *c2;
        *c2 = temp;
}

void heapify(heap *list, int i){
        int smallest = i;
        if(LCHILD(i) < list->size && list->c[LCHILD(i)].points < list->c[i].points){
                smallest = LCHILD(i);
        }
        if(RCHILD(i) < list->size && list->c[RCHILD(i)].points < list->c[smallest].points){
                smallest = RCHILD(i);
        }
        if(smallest != i){
                switcheroo(&(list->c[i]), &(list->c[smallest]));
                heapify(list, smallest);
        }
}

void buildHeap(heap *list, int *arr, int size){
	for(int i = 0; i < size; i++){
		if(list->size){
			list->c = realloc(list->c, (list->size+1)*sizeof(contestant));
		}
		else{
			list->c = malloc(sizeof(contestant));
		}
		contestant c;
		c.id = i;
		c.points = arr[i];
		list->c[(list->size)++] = c;
	}
	for(int i = (list->size - 1)/2; i>=0; i--){
		heapify(list, i);
	}
}

void
findContestant(int id, int* arr){
	if(arr[id]){
		printf("Contestant %d is in the extended heap with score %d\n", id, arr[id]);
	}
	else{
		printf("Contestant %d is not in the extended heap\n", id);
	}
}

void
insertContestant(int id, int score, heap* list, int *arr){
	if(list->size){
		list->c = realloc(list->c, ((list->size)+1) * sizeof(contestant));
	}
	else{
		list->c = malloc(sizeof(contestant));
	}

	contestant c;
	c.id = id;
	c.points = score;

	int i = (list->size)++;
	while(i && c.points < list->c[PARENT(i)].points){
		list->c[i] = list->c[PARENT(i)];
		i = PARENT(i);
	}
	arr[id] = score;
	list->c[i] = c;
}

//void swap(contestant *c1, contestant *c2){
	//contestant temp = *c1;
	//*c1 = *c2;
	//*c2 = temp;
//}

//void heapify(heap *list, int i){
	//int smallest = i;
	//if(LCHILD(i) < list->size && list->c[LCHILD(i)].points < list->c[i].points){
		//smallest = LCHILD(i);
	//}
	//if(RCHILD(i) < list->size && list->c[RCHILD(i)].points < list->c[smallest].points){
                //smallest = RCHILD(i);
        //}
	//if(smallest != i){
		//swap(&(list->c[i]), &(list->c[smallest]));
		//heapify(list, smallest);
	//}
//}

void
eliminateWeakest(heap* list, int *arr){
	if(list->size){
		printf("Contestant %d with current lowest score %d eliminated\n", list->c[0].id, list->c[0].points);
		arr[list->c[0].id] = 0;
		list->c[0] = list->c[--(list->size)];
		//arr[list->c[0].id] = 0;
		list->c = realloc(list->c, list->size * sizeof(contestant));
		heapify(list, 0);
	}
	else{
		printf("no players in da game yet\n");
		free(list->c);
	}
}

int flag = -1;

void searchHeap(heap *list, int i, int id){
	if(LCHILD(i) < list->size){
		searchHeap(list, LCHILD(i), id);
	}
	//printf("%d\n", list->c[i].id);
	if(list->c[i].id == id){
		flag = i;
	}
	//printf("%d\n", flag);
	if(RCHILD(i) < list->size){
                searchHeap(list, RCHILD(i), id);
        }
}

void
earnPoints(int id, int points, heap* list, int *arr){
	//int flag = -1;
	searchHeap(list, 0, id);
	if(flag == -1){
		printf("Contestant %d is not in the heap\n", id);
	}
	else{
		list->c[flag].points = list->c[flag].points + points;
		arr[list->c[flag].id] = list->c[flag].points;
		heapify(list, 0);
	}
	flag = -1;
}

void
lostPoints(int id, int points, heap* list, int *arr){
	//int flag = -1;
	searchHeap(list, 0, id);
        if(flag == -1){
                printf("Contestant %d is not in the heap\n", id);
        }
        else{
                list->c[flag].points = list->c[flag].points - points;
		arr[list->c[flag].id] = list->c[flag].points;
		heapify(list, 0);
        }
	flag = -1;
}

void
showContestants(heap *list, int i){
	if(LCHILD(i) < list->size){
		showContestants(list, LCHILD(i));
	}
	printf("Contestant %d in extended heap location %d with score %d\n", list->c[i].id, i, list->c[i].points);
	if(RCHILD(i) < list->size){
		showContestants(list, RCHILD(i));
	}
}

void
showHandles(heap* list, int i, handle* arr){
	//int arr[list->size];
	if(LCHILD(i) < list->size){
                showHandles(list, LCHILD(i), arr);
        }

	arr[list->c[i].id].spot = i;
	arr[list->c[i].id].flag = 1;

	if(RCHILD(i) < list->size){
                showHandles(list, RCHILD(i), arr);
        }
}

void
showLocation(int id, heap* list){
	//int flag = -1;
	searchHeap(list, 0, id);
        if(flag == -1){
                printf("Contestant %d is not in the heap\n", id);
        }
        else{
                printf("Contestant %d is in location %d\n", id, flag);
        }
	flag = -1;
}

void
crownWinner(heap* list, int* arr){
	int total = list->size;
	for(int i = 0; i < total-1; i++){
		eliminateWeakest(list, arr);
	}
	printf("Contestant %d wins with score %d!\n", list->c[0].id, list->c[0].points);
}

int main(int argc, char* argv[]){
	heap *list = makeHeap(5);
	int arr[5];
	//arr[0] = 10;
	//arr[1] = 20;
	//arr[2] = 5;
	//arr[3] = 30;
	//arr[4] = 25;
	insertContestant(0, 10, list, arr);
	insertContestant(1, 20, list, arr);
	insertContestant(2, 5, list, arr);
	insertContestant(3, 30, list, arr);
	insertContestant(4, 25, list, arr);
	//findContestant(2, arr);
	//eliminateWeakest(list, arr);
	//lostPoints(1, 10, list, arr);
	//showContestants(list, 0);
	//handle handles[5];
	//for(int i = 0; i < 5; i++){
		//handles[i].flag = 0;
	//}
	//showHandles(list, 0, handles);
	//for(int i = 0; i < 5; i ++){
		//if(handles[i].flag) printf("Contestant %d stored in extended heap location %d\n", i, handles[i].spot);
		//else printf("There is no contestant, die!\n");
	//}
	//showLocation(1, list);
	crownWinner(list, arr);
	//printf("beans\n");
}
