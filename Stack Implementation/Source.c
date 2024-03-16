#include <malloc.h>
#include<stdio.h>

typedef struct {
	int dd, mm, aaaa;
}data;

typedef struct {
	data date;
	char* owner;
	float value;
}orders;

typedef struct {
	orders info;
	struct nodStack* next;
}nodStack;

typedef struct {
	orders info;
	struct nodlist*next;
}nodList;

void push(nodStack** top, nodStack** end, orders order) {
	nodStack* newNod = (nodStack*)malloc(sizeof(nodStack));
	//adding node
	newNod->info.date.dd = order.date.dd;
	newNod->info.date.mm = order.date.mm;
	newNod->info.date.aaaa = order.date.aaaa;
	if (order.owner != NULL) {
		newNod->info.owner = (char*)malloc((strlen(order.owner) + 1) * sizeof(char));
		strcpy(newNod->info.owner, order.owner);
	}
	newNod->info.value = order.value;
	newNod->next = NULL;

	if (*top == NULL && *end == NULL) {
		*top = newNod;
		
	}
	else {
		newNod->next = *top;
		*top = newNod;
	}
}

int pop(nodStack** top, orders* info) {
	if (*top == NULL)
		return -1;
	else {
		(*info).date.dd = (*top)->info.date.dd;
		(*info).date.mm = (*top)->info.date.mm;
		(*info).date.aaaa = (*top)->info.date.aaaa;
		if ( (*top)->info.owner != NULL) {
			(*info).owner = (char*)malloc( (strlen((*top)->info.owner) + 1) * sizeof(char));
			strcpy((*info).owner, (*top)->info.owner);
		}
		(*info).value = (*top)->info.value;
		nodStack* temp = *top;
		(*top) = (*top)->next;
		free(temp->info.owner);
		free(temp);
		return 0;

	}
}

void viewStack(nodStack** top) {
	nodStack* temp = *top;
	while (temp != NULL) {
		printf("Owner:%s, Date:%d/%d/%d, Value order:%5.2f\n",
			temp->info.owner, temp->info.date.dd, temp->info.date.mm, temp->info.date.aaaa, temp->info.value);
		temp = temp->next;
	}

}


void addNodList(nodList**beg,nodList**end,orders o) {
	nodList* newNod = (nodList*)malloc(sizeof(nodList));

	newNod->info.date.dd = o.date.dd;
	newNod->info.date.mm = o.date.mm;
	newNod->info.date.aaaa = o.date.aaaa;
	if (o.owner != NULL) {
		newNod->info.owner = (char*)malloc((strlen(o.owner) + 1) * sizeof(char));
		strcpy(newNod->info.owner, o.owner);
	}
	newNod->info.value = o.value;
	newNod->next = NULL;

	if (*beg == NULL) {
		*beg = newNod;
	}
	else {
		nodList* temp = *beg;
		while (temp->next != NULL)
			temp = temp->next;
		temp->next = newNod;
	}

}

void stackToSimpleList(nodStack* top,nodList* beg,nodList* end) {
	orders o;
	while (pop(&top, &o) == 0) {
		addNodList(beg,end,o);
     }
	
}

void stackToVector(nodStack* top, orders* vect, int* size) {
	orders o;
	while (pop(&top, &o) == 0) {
		vect[(*size)++] = o;
		//(*size)++;
	}
}

void viewList(nodList* beginning) {
	nodList* temp = beginning;
	while (temp != NULL) {
		printf("Owner:%s, Date:%d/%d/%d, Value order:%5.2f\n",
			temp->info.owner, temp->info.date.dd, temp->info.date.mm, temp->info.date.aaaa, temp->info.value);
		temp = temp->next;
	}
}

void freeList(nodList* beginning) {
	nodList* temp = beginning;
	while (temp != NULL) {
		nodList* aux = temp->next;
		free(temp->info.owner);
		free(temp);
		temp = aux;

	}
}

int main() {
	nodStack* end = NULL;
	nodStack* top = NULL;
	orders order;
	char buffer[20];
	int nr;
	nodList* beginning=NULL;
	nodList* endL=NULL;

	FILE* f = fopen("Text.txt", "r");
	fscanf(f, "%d", &nr);
	for (int i = 0; i < nr; i++) {
		fscanf(f, "%s", buffer);
		order.owner = (char*)malloc((strlen(buffer) + 1) * sizeof(char));
		strcpy(order.owner, buffer);
		fscanf(f, "%d", &order.date.dd);
		fscanf(f, "%d", &order.date.mm);
		fscanf(f, "%d", &order.date.aaaa);
		fscanf(f, "%f", &order.value);

		push(&top, &end, order);
		free(order.owner);
	}

	viewStack(&top);
	stackToSimpleList(top, &beginning, endL);
	printf("-----Simple List-----\n");
	viewList(beginning);
	freeList(beginning);
	
	//int sizeVect=0;
	//orders* vect=(orders*)malloc(sizeof(orders)*nr);
	//stackToVector(top, vect, &sizeVect);
	//printf("-------vector--------\n");
	//for (int i = 0; i < sizeVect; i++) {
	//	printf("Owner:%s, Date:%d/%d/%d, Value order:%5.2f\n",
	//		vect[i].owner, vect[i].date.dd, vect[i].date.mm, vect[i].date.aaaa, vect[i].value);
	//}

 // //free vector
	//for (int i = 0; i < nr; i++)
	//	free(vect[i].owner);
	//free(vect);
	////free stack
	//while (pop(&top, &order)==0)
	//	free(order.owner);  
 //  

}