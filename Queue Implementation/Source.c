#include<malloc.h>
#include <stdio.h>

typedef struct {
	char* name;
	float GPA_tobeaccepted;
	int no_Students;
	int no_departaments;
}university;

typedef struct {
	university info;
	struct nodQueue* next;
}nodQueue;

typedef struct {
	university info;
	struct nodQueue* next;
	struct nodQueue* prev;
}nodDoubleList;




void put(nodQueue** top, nodQueue** end, university u) {
	nodQueue* newNod = (nodQueue*)malloc(sizeof(nodQueue));
	//adding new nod
	if (u.name != NULL) {
		newNod->info.name = (char*)malloc((strlen(u.name) + 1) * sizeof(char));
		strcpy(newNod->info.name, u.name);
	}
	newNod->info.GPA_tobeaccepted = u.GPA_tobeaccepted;
	newNod->info.no_departaments = u.no_departaments;
	newNod->info.no_Students = u.no_Students;
	newNod->next = NULL;

	if (*top == NULL && *end == NULL) {
		*top = newNod;
		*end = newNod;
	}
	else {
		(*end)->next = newNod;
		*end = newNod;
	}
}

int push(nodQueue** top, university* info) {
	if (*top == NULL) {
		return -1;
	}
	else {
		if ((*top)->info.name != NULL) {
			info->name = (char*)malloc((strlen((*top)->info.name) + 1) * sizeof(char));
			strcpy(info->name, (*top)->info.name);
		}
		info->GPA_tobeaccepted = (*top)->info.GPA_tobeaccepted;
		info->no_departaments = (*top)->info.no_departaments;
		info->no_Students = (*top)->info.no_Students;

nodQueue* temp = *top;
(*top) = (*top)->next;

free(temp->info.name);
free(temp);
return 0;
	}
}

void viewQueue(nodQueue** top) {
	nodQueue* temp = *top;
	while (temp != NULL) {
		printf("Name:%s, Avg.Grade:%5.2f, No.of Departments:%d, No.Students:%d\n",
			temp->info.name, temp->info.GPA_tobeaccepted, temp->info.no_departaments, temp->info.no_Students);
		temp = temp->next;
	}
}

void queueTovector(nodQueue* top, university* vect, int* nr) {
	university u;
	while (push(top, &u) == 0) {
		vect[(*nr)++] = u;
	}
}

void addNodList(nodDoubleList** beginning, nodDoubleList** end, university u) {
	nodDoubleList* newNod = (nodDoubleList*)malloc(sizeof(nodDoubleList));

	if (u.name != NULL) {
		newNod->info.name = (char*)malloc((strlen(u.name) + 1) * sizeof(char));
		strcpy(newNod->info.name, u.name);
	}
	newNod->info.GPA_tobeaccepted = u.GPA_tobeaccepted;
	newNod->info.no_departaments = u.no_departaments;
	newNod->info.no_Students = u.no_Students;
	newNod->next = NULL;
	newNod->prev = NULL;

	if (*beginning == NULL) {
		*beginning = newNod;
	}
	else {
		nodDoubleList* temp = *beginning;
		while (temp->next != NULL) {
			temp = temp->next;
		}
		newNod->prev = temp;
		temp->next = newNod;
		(*end) = newNod;

	}
}

void queueToList(nodQueue* top, nodDoubleList* beginning, nodDoubleList* end) {
	university u;
	while (push(top, &u) == 0)
	{
		addNodList(beginning, end, u);
	}
}

void viewInversList(nodDoubleList* end) {
	nodDoubleList* temp = end;
	while (temp != NULL) {
		printf("Name:%s, Avg.Grade:%5.2f, No.of Departments:%d, No.Students:%d\n",
			temp->info.name, temp->info.GPA_tobeaccepted, temp->info.no_departaments, temp->info.no_Students);
		temp = temp->prev;
	}
}

void viewList(nodDoubleList* beginning) {
	nodDoubleList* temp = beginning;
	while (temp != NULL) {
		printf("Name:%s, Avg.Grade:%5.2f, No.of Departments:%d, No.Students:%d\n",
			temp->info.name, temp->info.GPA_tobeaccepted, temp->info.no_departaments, temp->info.no_Students);
		temp = temp->next;
	}
}

void freeList(nodDoubleList* beg) {
	nodDoubleList* temp = beg;
	while (temp != NULL) {
		nodDoubleList* aux = temp->next;
		free(temp->info.name);
		free(temp);
		temp = aux;
	}
}

//deleting a particular nod
void deleteNod(nodDoubleList** beg, nodDoubleList** end, char* name) {
	if (strcmp((*beg)->info.name, name) == 0) {

		nodDoubleList* aux = *beg;
		*beg = (*beg)->next;

		free(aux->info.name);
		free(aux);
		return;
	}
	
	if (strcmp((*end)->info.name, name) == 0){
		nodDoubleList* aux = *end;
		*end = (*end)->prev;
		(*end)->next = NULL;

		free(aux->info.name);
		free(aux);
		return;
	}

	else {
		nodDoubleList* temp = *beg;
		while (temp != NULL) {
			if (strcmp(temp->info.name, name) == 0) {
				nodDoubleList* next;
				nodDoubleList* prev;
				next = temp->next;
				prev = temp->prev;
				next->prev = prev;
				prev->next = next;

				free(temp->info.name);
				free(temp);
				return;
				
			}
			temp = temp->next;
		}
	}
}



int main() {
	nodQueue* top = NULL;
	nodQueue* end = NULL;
	nodDoubleList* beg = NULL;
	nodDoubleList* endL = NULL;
	int nrfac=0;
	char buffer[20];
	university u;

	FILE* f = fopen("Text.txt", "r");
	fscanf(f, "%d", &nrfac);
	for (int i = 0; i < nrfac; i++) {
		fscanf(f, "%s", buffer);
		if (buffer != NULL) {
			u.name = (char*) malloc((strlen(buffer) + 1) * sizeof(char));
			strcpy(u.name, buffer);
		}
		fscanf(f, "%f", &u.GPA_tobeaccepted);
		fscanf(f, "%d", &u.no_departaments);
		fscanf(f, "%d", &u.no_Students);
		put(&top, &end, u);
		free(u.name);
	}
	viewQueue(&top);
	queueToList(&top, &beg,&endL);
	printf("--------Queue to List-------\n");
	viewInversList(endL);
	printf("----------List------\n");
	deleteNod(&beg,&endL, "Law");
	viewList(beg);
	
	freeList(beg);
	/*int nr = 0;
	university* vect = (university*)malloc(sizeof(university)*nrfac);
	queueTovector(&top, vect,&nr);
	printf("---------Queue to vector----------\n");
	for (int i = 0; i < nrfac; i++) {
		printf("Name:%s, Avg.Grade:%5.2f, No.of Departments:%d, No.Students:%d\n",
			vect[i].name, vect[i].GPA_tobeaccepted,vect[i].no_departaments, vect[i].no_Students);
	}

	for (int i = 0; i < nrfac; i++)
		free(vect[i].name);
	free(vect);*/

	/*while (push(&top, &u) == 0)
		 free(u.name);*/

}

