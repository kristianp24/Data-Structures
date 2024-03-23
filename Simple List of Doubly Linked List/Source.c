#include <malloc.h>
#include <stdio.h>

typedef struct {
	char* name;
	float price;
	int quantity;
}product;

typedef struct {
	struct nodPrincipalList* next;
	product* info;
}nodPrincipalList;

typedef struct {
	struct nodSecondList* prev;
	struct nodSecondList* next;
	product info;
}nodSecondList;

void addNodSecondList(nodSecondList** top, product info,nodSecondList**end) {
	nodSecondList* newNod = (nodSecondList*)malloc(sizeof(nodSecondList));
	if (info.name != NULL) {
         newNod->info.name = (char*)malloc((strlen(info.name) + 1)*sizeof(char));
		 strcpy(newNod->info.name, info.name);
	}
	  
	
	newNod->info.price = info.price;
	newNod->info.quantity = info.quantity;
	newNod->next = NULL;
	newNod->prev = NULL;

	if ((*top) == NULL) {
		(*top) = newNod;
		(*end) = newNod;
	}
	else {
		nodSecondList* temp = (*top);
		while (temp->next != NULL)
			temp = temp->next;
		temp->next = newNod;
		newNod->prev = temp;
		(*end) = newNod;
	}
}

void addNodFirstList(nodPrincipalList** beginning, nodSecondList* info) {
	nodPrincipalList* newNod = (nodPrincipalList*)malloc(sizeof(nodPrincipalList));
	newNod->info = info;
	newNod->next = NULL;
	if ((*beginning) == NULL) {
		*beginning = newNod;
		//(*beginning)->info = info;
	}
	else{
		nodPrincipalList* temp = (*beginning);
		while (temp->next != NULL)
			temp = temp->next;

		temp->next = newNod;
		
	}

}

void viewSecondList(nodSecondList* beginning) {
	nodSecondList* temp = beginning;
	while (temp != NULL) {
		printf("Name product:%s, Price:%5.2f, Quantity:%d\n",
			temp->info.name, temp->info.price, temp->info.quantity);
		temp = temp->next;
	}
}

void view(nodPrincipalList* beginning) {
	int contor = 1;
	nodPrincipalList* temp = beginning;
	while (temp != NULL) {
		printf("Lista din nodul %d\n", contor);
		viewSecondList(temp->info);
		contor++;
		temp = temp->next;
	}
}

void freeMemorySecondList(nodSecondList* beginning) {
	nodSecondList* temp = beginning;
	while (temp != NULL) {
		nodSecondList* aux = temp->next;
		free(temp->info.name);
		free(temp);
		temp = aux;
	}
}

void freeMemory(nodPrincipalList* beginning) {
	nodPrincipalList* temp = beginning;
	while (temp != NULL) {
		nodPrincipalList* aux = temp->next;
		freeMemorySecondList(temp->info);
		free(temp);
		temp = aux;
	}
}



void main() {
	nodPrincipalList* beginningP = NULL;
	nodSecondList* beginningS1 = NULL, *beginningS2=NULL,*endS1=NULL,*endS2=NULL;
	product product;
	int noProduct;
	char buffer[20];

	FILE* f = fopen("Text.txt", "r");
	fscanf(f, "%d", &noProduct);
	for (int i = 0; i < noProduct; i++) {
		fscanf(f, "%s", buffer);
		product.name = (char*)malloc((strlen(buffer) + 1) * sizeof(char));
		strcpy(product.name, buffer);
		fscanf(f, "%f", &product.price);
		fscanf(f, "%d", &product.quantity);

		if (product.price > 10)
			addNodSecondList(&beginningS1, product,&endS1);
		else
			addNodSecondList(&beginningS2, product,&endS2);

		free(product.name);
	}

	addNodFirstList(&beginningP, beginningS1);
	addNodFirstList(&beginningP, beginningS2);

	view(beginningP);

	freeMemory(beginningP);



}