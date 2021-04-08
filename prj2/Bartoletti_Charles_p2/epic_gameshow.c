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

int flag = -1;
int sntl = -1;

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
findContestant(int id, heap *list, FILE* fp){
	searchHeap(list, 0, id);
	if(flag != -1){
		fprintf(fp, "Contestant <%d> is in the extended heap with score <%d>\n", id+1, list->c[id].points);
	}
	else{
		fprintf(fp, "Contestant <%d> is not in the extended heap\n", id+1);
	}
	flag = -1;
}

void
insertContestant(int id, int score, heap* list, int *arr, FILE* fp){
	//searchHeap(list, 0, id);
	//FILE *fp = fopen("output.txt", "a");
	//if(flag != -1){
		//fprintf(fp, "Contestant <%d> is already in the extended heap: cannot insert.", id);
	//}
	//else{
		if(list->size){
			searchHeap(list, 0, id);
			if(flag != -1){
                		fprintf(fp, "Contestant <%d> is already in the extended heap: cannot insert.\n", id+1);
        		}
			else{
				list->c = realloc(list->c, ((list->size)+1) * sizeof(contestant));
			}
		}
		else{
			list->c = malloc(sizeof(contestant));
		}
		if(flag == -1){
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
			fprintf(fp, "Contestant <%d> inserted with initial score <%d>\n", id+1, score);
		}
	//}
	//fclose(fp);
	flag = -1;
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
eliminateWeakest(heap* list, int *arr, FILE* fp){
	if(list->size){
		if(sntl == -1){
			fprintf(fp, "Contestant <%d> with current lowest score %d eliminated\n", list->c[0].id+1, list->c[0].points);
		}
		arr[list->c[0].id] = 0;
		list->c[0] = list->c[--(list->size)];
		//arr[list->c[0].id] = 0;
		list->c = realloc(list->c, list->size * sizeof(contestant));
		heapify(list, 0);
	}
	else{
		fprintf(fp, "No contestant can be eliminated since the extended heap is empty\n");
		free(list->c);
	}
}

//int flag = -1;

//void searchHeap(heap *list, int i, int id){
	//if(LCHILD(i) < list->size){
		//searchHeap(list, LCHILD(i), id);
	//}
	//printf("%d\n", list->c[i].id);
	//if(list->c[i].id == id){
		//flag = i;
	//}
	//printf("%d\n", flag);
	//if(RCHILD(i) < list->size){
                //searchHeap(list, RCHILD(i), id);
        //}
//}

void
earnPoints(int id, int points, heap* list, int *arr, FILE* fp){
	//int flag = -1;
	searchHeap(list, 0, id);
	if(flag == -1){
		fprintf(fp, "Contestant <%d> is not in the extended heap\n", id+1);
	}
	else{
		list->c[flag].points = list->c[flag].points + points;
		arr[list->c[flag].id] = list->c[flag].points;
		fprintf(fp, "Contestant <%d>s score increased by <%d> points to <%d>\n", id+1, points, list->c[flag].points);
		heapify(list, 0);
	}
	flag = -1;
}

void
lostPoints(int id, int points, heap* list, int *arr, FILE* fp){
	//int flag = -1;
	searchHeap(list, 0, id);
        if(flag == -1){
                fprintf(fp, "Contestant <%d> is not in the extended heap\n", id+1);
        }
        else{
                list->c[flag].points = list->c[flag].points - points;
		arr[list->c[flag].id] = list->c[flag].points;
		fprintf(fp, "Contestant <%d>s score decreased by <%d> points to <%d>\n", id+1, points, list->c[flag].points);
		heapify(list, 0);
        }
	flag = -1;
}

void
showContestants(heap *list, int i, FILE* fp){
	fprintf(fp, "Contestant <%d> in extended heap location <%d> with score <%d>\n", list->c[i].id+1, i+1, list->c[i].points);
	if(LCHILD(i) < list->size){
		showContestants(list, LCHILD(i), fp);
	}
	//fprintf(fp, "Contestant <%d> in extended heap location <%d> with score <%d>\n", list->c[i].id+1, i+1, list->c[i].points);
	if(RCHILD(i) < list->size){
		showContestants(list, RCHILD(i), fp);
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
showLocation(int id, heap* list, FILE* fp){
	//int flag = -1;
	searchHeap(list, 0, id);
        if(flag == -1){
                fprintf(fp, "Contestant <%d> is not in the heap\n", id+1);
        }
        else{
                fprintf(fp, "Contestant <%d> is in location <%d>\n", id+1, flag);
        }
	flag = -1;
}

void
crownWinner(heap* list, int* arr, FILE *fp){
	sntl = 1;
	int total = list->size;
	for(int i = 0; i < total-1; i++){
		eliminateWeakest(list, arr, fp);
	}
	fprintf(fp, "Contestant <%d> wins with score <%d>!\n", list->c[0].id+1, list->c[0].points);
	sntl = -1;
}

int main(int argc, char* argv[]){
	FILE *fp;
	FILE *fpo;
	char buff[1000];
	//char ins1[1000];
	char sub1[1000];
	//int sntl = 0;
	//char ptr[1000];
	int size;
	int len;
	int arg1;
	int arg2;
	fp = fopen(argv[1], "r");
	fpo = fopen(argv[2], "a");
	fscanf(fp, "%d", &size);
	//size = atoi(buff);
	//printf("%d\n", size);
	//int size = atoi(buff);
	heap *list = makeHeap(size);
	int arr[size];
	//insertContestant(0, 10, list, arr);
	//insertContestant(1, 20, list, arr);
	//printf("%d\n",atoi("<5>"));
	while(fscanf(fp, "%s", buff)>0){
		if(strcmp(buff, "insertContestant") == 0){
			fscanf(fp, "%s", buff);
			len = strlen(buff);
			strncpy(sub1, &buff[1], len-1);
			arg1 = atoi(sub1);
			arg1 = arg1 - 1;
			fscanf(fp, "%s", buff);
                        len = strlen(buff);
                        strncpy(sub1, &buff[1], len-1);
                        arg2 = atoi(sub1);
			fprintf(fpo, "insertContestant <%d> <%d>\n", arg1 + 1, arg2);
			if(arg1 >= size){
				//fpo = fopen("output.txt", "a");
				fprintf(fpo, "Contestant <%d> could not be inserted because the extended heap is full", arg1);
				//fclose(fpo);
			}
			else{
				insertContestant(arg1, arg2, list, arr, fpo);
			}
		}
		else if(strcmp(buff, "showContestants") == 0){
			fprintf(fpo, "showContestants\n");
			showContestants(list, 0, fpo);
                }
		else if(strcmp(buff, "findContestant") == 0){
			fscanf(fp, "%s", buff);
                        len = strlen(buff);
                        strncpy(sub1, &buff[1], len-1);
                        arg1 = atoi(sub1);
                        arg1 = arg1 - 1;
			fprintf(fpo, "findContestant <%d>\n", arg1 + 1);
			findContestant(arg1, list, fpo);
                }
		else if(strcmp(buff, "eliminateWeakest") == 0){
			fprintf(fpo, "eliminateWeakest\n");
			eliminateWeakest(list, arr, fpo);
                }
		else if(strcmp(buff, "losePoints") == 0){
			fscanf(fp, "%s", buff);
                        len = strlen(buff);
                        strncpy(sub1, &buff[1], len-1);
                        arg1 = atoi(sub1);
                        arg1 = arg1 - 1;
                        fscanf(fp, "%s", buff);
                        len = strlen(buff);
                        strncpy(sub1, &buff[1], len-1);
                        arg2 = atoi(sub1);
			fprintf(fpo, "losePoints <%d>, <%d>\n", arg1 + 1, arg2);
			lostPoints(arg1, arg2, list, arr, fpo);
                }
		else if(strcmp(buff, "earnPoints") == 0){
			fscanf(fp, "%s", buff);
                        len = strlen(buff);
                        strncpy(sub1, &buff[1], len-1);
                        arg1 = atoi(sub1);
                        arg1 = arg1 - 1;
                        fscanf(fp, "%s", buff);
                        len = strlen(buff);
                        strncpy(sub1, &buff[1], len-1);
                        arg2 = atoi(sub1);
			fprintf(fpo, "earnPoints <%d>, <%d>\n", arg1 + 1, arg2);
                        earnPoints(arg1, arg2, list, arr, fpo);
                }
		else if(strcmp(buff, "showHandles") == 0){
			fprintf(fpo, "showHandles\n");
			handle handles[size];
        		for(int i = 0; i < size; i++){
                		handles[i].flag = 0;
        		}
        		showHandles(list, 0, handles);
        		for(int i = 0; i < size; i ++){
                		if(handles[i].flag) fprintf(fpo, "Contestant <%d> stored in extended heap location <%d>\n", i+1, handles[i].spot+1);
                		else fprintf(fpo, "There is no Contestant <%d> in the extended heap: handle[<%d>] = -1\n", i+1, i+1);
        		}
                }
		else if(strcmp(buff, "showLocation") == 0){
			fscanf(fp, "%s", buff);
                        len = strlen(buff);
                        strncpy(sub1, &buff[1], len-1);
                        arg1 = atoi(sub1);
                        arg1 = arg1 - 1;
			fprintf(fpo, "showLocation <%d>\n", arg1 + 1);
			showLocation(arg1, list, fpo);
                }
		else if(strcmp(buff, "crownWinner") == 0){
			fprintf(fpo, "crownWinner\n");
			crownWinner(list, arr, fpo);
                }
		else{
			printf("Command not recognized\n");
		}
	}
	fclose(fp);
	fclose(fpo);
	//arr[0] = 10;
	//arr[1] = 20;
	//arr[2] = 5;
	//arr[3] = 30;
	//arr[4] = 25;
	//insertContestant(0, 10, list, arr);
	//insertContestant(1, 20, list, arr);
	//insertContestant(2, 5, list, arr);
	//insertContestant(3, 30, list, arr);
	//insertContestant(4, 25, list, arr);
	//findContestant(2, arr);
	//eliminateWeakest(list, arr);
	//lostPoints(1, 10, list, arr);
	//showContestants(list, 0);
	//handle handles[5];
	//for(int i = 0; i < size; i++){
		//handles[i].flag = 0;
	//}
	//showHandles(list, 0, handles);
	//for(int i = 0; i < size; i ++){
		//if(handles[i].flag) printf("Contestant %d stored in extended heap location %d\n", i, handles[i].spot);
		//else printf("There is no contestant, die!\n");
	//}
	//showLocation(1, list);
	//crownWinner(list, arr);
	//printf("beans\n");
}
