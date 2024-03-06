#include<stdio.h>
#include<malloc.h>

typedef struct {
	int* note;
	int nrNote;
	char* name;
	float average;
}student;

typedef struct {
	student info;
	struct nod* next, * prev;
}nod;

void inserare(nod** beginning, nod** end, student s) {
	nod* newNod = (nod*)malloc(sizeof(nod));

	newNod->info.nrNote = s.nrNote;
	newNod->info.note = (int*)malloc(s.nrNote * sizeof(int));
	for (int i = 0; i < s.nrNote; i++) {
		newNod->info.note[i] = s.note[i];
	}
	newNod->info.name = (char*)malloc((strlen(s.name) + 1) * sizeof(char));
	strcpy(newNod->info.name, s.name);
	newNod->info.average = s.average;

	if (*beginning == NULL) {
		*beginning = newNod;
		*end = newNod;
		newNod->next = *beginning;
		newNod->prev = *beginning;
	}
	else
	{
		nod* aux = *beginning;
		aux->prev = newNod;
		while (aux->next != *beginning)
			aux = aux->next;
		aux->next = newNod;
		newNod->prev = aux;
		newNod->next = *beginning;
		*end = newNod;

	}
}

void display(nod** beginning) {
	nod* aux = *beginning;
	while (aux->next != *beginning)
	{
		printf("Name:%s, No. grades:%d, ", aux->info.name,aux->info.nrNote);
		printf("Grades: ");
		for (int i = 0; i < aux->info.nrNote; i++) {
			printf("%d,", aux->info.note[i]);
		}
		printf("Avg:%f \n", aux->info.average);
		aux = aux->next;
	}
	printf("Name:%s, No. grades:%d, ", aux->info.name, aux->info.nrNote);
	printf("Grades: ");
	for (int i = 0; i < aux->info.nrNote; i++) {
		printf("%d,", aux->info.note[i]);
	}
	printf("Avg:%f \n", aux->info.average);

}

void displayInvers(nod* end) {
	nod* aux = end;
	while (aux->prev != end)
	{
		printf("Name:%s, No. grades:%d, ", aux->info.name, aux->info.nrNote);
		printf("Grades: ");
		for (int i = 0; i < aux->info.nrNote; i++) {
			printf("%d,", aux->info.note[i]);
		}
		printf("Avg:%f \n", aux->info.average);
		aux = aux->prev;
	}
	printf("Name:%s, No. grades:%d, ", aux->info.name, aux->info.nrNote);
	printf("Grades: ");
	for (int i = 0; i < aux->info.nrNote; i++) {
		printf("%d,", aux->info.note[i]);
	}
	printf("Avg:%f \n", aux->info.average);
	
}

void freeMemory(nod** beginning,nod**end) {
	nod* aux = *beginning;
	while (aux != *end) {
		nod* temp = aux->next;
		free(aux->info.name);
		free(aux->info.note);
		free(aux);
		aux = temp;
	}
	free(aux->info.name);
	free(aux->info.note);
	free(aux);
}

void deleteNod(nod** beginning, nod** end, char* name) {
	//Delete first nod
	if (strcmp((*beginning)->info.name, name) == 0) {
		nod* newNext = (*beginning)->next;
		nod* newPrev = (*beginning)->prev;
		free((*beginning)->info.name);
		free((*beginning)->info.note);
		free((*beginning));
		(*end)->next = newNext;
		newNext->prev = *end;
		*beginning = newNext;
	}
	//Delete last node
	if (strcmp((*end)->info.name, name) == 0) {
		nod* newNext = (*end)->next;
		nod* newPrev = (*end)->prev;
		free((*end)->info.name);
		free((*end)->info.note);
		free((*end));
		(*beginning)->prev = newPrev;
		(*newPrev).next = (*beginning);
		*end = newPrev;
	}
	else 
	{
		nod* aux = *beginning;
		while (aux->next != *beginning) {
			if (strcmp(aux->info.name, name) == 0) {
				nod* newNext = aux->next;
				nod* newPrev = aux->prev;
				free(aux->info.name);
				free(aux->info.note);
				free(aux);
				newPrev->next = newNext;
				newNext->prev = newPrev;
				aux = newNext;
			}
			else {
              aux = aux->next;
			}
			
		}

	}

	
}

void biggestGrade(nod* beginning) {
	float grade = beginning->info.average;
	char buffer[20];
	nod* aux = beginning;
	while (aux->next != beginning)
	{
		if (aux->info.average > grade) {
			grade = aux->info.average;
			strcpy(buffer, aux->info.name);
		}
		aux = aux->next;
    }
	if (aux->info.average > grade) {
		grade = aux->info.average;
		strcpy(buffer, aux->info.name);
	}
	
	printf("Student: %s has the biggest average %f ", buffer,grade);

	
}



int main() 
{
	nod* beginning = NULL, * end = NULL;
	int nrStud;
	char buffer[20];
	student s;
	FILE* f = fopen("Text.txt", "r");
	fscanf(f, "%d", &nrStud);
	for (int i = 0; i < nrStud; i++) {
		fscanf(f, "%d", &s.nrNote);
		fscanf(f, "%s", buffer);
		s.name = (char*)malloc((strlen(buffer) + 1) * sizeof(char));
		strcpy(s.name, buffer);
		s.note = (int*)malloc(sizeof(int) * s.nrNote);
		for (int i = 0; i < s.nrNote; i++)
			fscanf(f, "%d", &s.note[i]);
		fscanf(f, "%f", &s.average);
		inserare(&beginning, &end, s);
		free(s.name);
		free(s.note);
	}

	display(&beginning);
	printf("---------------\n");
	//displayInvers(end);


	printf("---------------\n");
	display(&beginning);
	//biggestGrade(beginning);

	/*deleteNod(&beginning, &end, "Miri");
	
	printf("---------------\n");
	display(&beginning);
	printf("---------------\n");
	displayInvers(end);*/

	freeMemory(&beginning,&end);

}
