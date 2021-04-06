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
	contestant *c;
} heap;

heap makeHeap(int size){
	heap min;
	min.size = 0;
	return min;
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
		printf("Contestant %d is not in the extended heap\n");
	}
}

void
insertContestant(int id, int score, heap* list){
	if(list->size){
		list->c = realloc(list->c, (size+1) * sizeof(contestant));
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
	list->c[i] = c;
}

void swap(contestant *c1, contestant *c2){
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
		swap(&(list->c[i]), &(list->c[smallest]));
		heapify(list, smallest);
	}
}

void
eliminateWeakest(heap* list){
	if(list->size){
		list->c[0] = list->c[--(list->size)];
		list->c = realloc(list->c, list->size * sizeof(contestant));
		heapify(list, 0);
	}
	else{
		printf("no players in da game yet\n");
		free(list->c);
	}
}

int searchHeap(heap *list, int i, int id){
	if(LCHILD(i) < list->size){
		searchHeap(list, LCHILD(i));
	}
	if(list->c[i].id == id){
		return i;
	}
	if(RCHILD(i) < list->size){
                searchHeap(list, RCHILD(i));
        }
	return -1;
}

void
earnPoints(int id, int points, heap* list){
	int found = searchHeap(list, 0, id);
	if(found == -1){
		printf("Contestant %d is not in the heap\n", id);
	}
	else{
		list->c[found].points = list->c[found].points + points;
	}
}

void
lostPoints(int id, int points, heap* list){
	int found = searchHeap(list, 0, id);
        if(found == -1){
                printf("Contestant %d is not in the heap\n", id);
        }
        else{
                list->c[found].points = list->c[found].points - points;
        }
}

void
showContestants(heap* list){

}

void
showHandles(heap* list){

}

void
showLocation(int id, heap* list){
	int found = searchHeap(list, 0, id);
        if(found == -1){
                printf("Contestant %d is not in the heap\n", id);
        }
        else{
                printf("Contestant %d is in location %d\n", id, found);
        }
}

void
crownWinner(heap* list){

}
