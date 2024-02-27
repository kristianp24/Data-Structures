#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <malloc.h>

typedef struct {
	char* name;
	int yearProduction;
	float price;

}laptop;

typedef struct {
	laptop information;
	struct Nods* nextNod;
}Nods;

Nods* addNode(Nods* beginning, laptop l) {
	//alocate memory for new nod
	Nods* new1 = (Nods*)malloc(sizeof(Nods));

	//intialize list
	new1->information.yearProduction = l.yearProduction;
	new1->information.name = (char*)malloc((strlen(l.name) + 1) * sizeof(char));
	strcpy(new1->information.name, l.name);
	new1->information.price = l.price;
	new1->nextNod = NULL;

	if (beginning == NULL)
		beginning = new1;
	else {
		Nods* temp = beginning;
		while (temp->nextNod != NULL)
			temp = temp->nextNod;
		temp->nextNod = new1;
	}
	return beginning;
}

void displayList(Nods* beginning) {
	Nods* temp = beginning;
	while (temp != NULL) {
		printf("Laptop type=%s ,Year of prod.= %d, Price=%5.2f\n ",
			temp->information.name, temp->information.yearProduction, temp->information.price);
		temp = temp->nextNod;  //move 1 element forward
	}
}

void freeMemory(Nods* beginning) {
	Nods* temp = beginning;
	while (temp != NULL)
	{
		Nods* aux = temp->nextNod; //to save the next element adress before we delete it

		free(temp->information.name);
		free(temp);
		temp = aux;
	}
}

//function to display only selected type of laptops (>= year 2015)
void saveLaptops(Nods* beginning, laptop* vector, int* nrLaptop, int year) {
	Nods* temp = beginning;
	while (temp != NULL) {
		if (temp->information.yearProduction >= year) {
			vector[*nrLaptop].name = (char*)malloc((strlen(temp->information.name) + 1) * sizeof(char));
			strcpy(vector[*nrLaptop].name, temp->information.name);
			vector[*nrLaptop].price = temp->information.price;
			vector[*nrLaptop].yearProduction = temp->information.yearProduction;
			(*nrLaptop)++;  //should be in ( )
		}
		temp = temp->nextNod;
	}
}

void main() {
	int nrLaptop;
	char buffer[20];
	Nods* beginning = NULL;
	laptop l;

	FILE* f = fopen("Text.txt", "r");
	fscanf(f, "%d", &nrLaptop);
	for (int i = 0; i < nrLaptop; i++) {
		fscanf(f, "%s", buffer);
		l.name = (char*)malloc((strlen(buffer)+1)*sizeof(char));
		strcpy(l.name, buffer);
		fscanf(f, "%d", &l.yearProduction);
		fscanf(f, "%f", &l.price);
		beginning= addNode(beggining, l);
		free(l.name);
	}
	fclose(f);

	displayList(beginning);
	printf("\n------------------\n");

	laptop* vector = (laptop*)malloc(sizeof(laptop)*nrLaptop);
	int nrElements=0;
	saveLaptops(beginning, vector, &nrElements, 2015);
	for (int i = 0; i < nrElements; i++) {
		printf("Laptop type=%s ,Year of prod.= %d, Price=%5.2f\n ",
			vector[i].name, vector[i].yearProduction, vector[i].price);
	}

	//free memory of vector
	for (int i = 0; i < nrElements; i++)
		free(vector[i].name);
	free(vector);
	


	freeMemory(beginning);
}
