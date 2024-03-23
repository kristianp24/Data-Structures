#include<malloc.h>
#include<stdio.h>

typedef struct {
	int id;
	char* name;
	float price;
}product;

typedef struct {
	struct nodList* next;
	product info;
}nodList;

typedef struct {
	struct nodList** vector;
	int nrElements;
}hashTable;

int hashFunction(int key, hashTable T) {
	return key % T.nrElements;
}

void addNodList(nodList** beginning, product p) {
	nodList* newNod = (nodList*)malloc(sizeof(nodList));
	if (p.name != NULL) {
		newNod->info.name = (char*)malloc((strlen(p.name) + 1));
		strcpy(newNod->info.name, p.name);
	}
	newNod->info.id = p.id;
	newNod->info.price = p.price;
	newNod->next = NULL;

	if (*beginning == NULL) {
		*beginning = newNod;
	}
	else {
		nodList* temp = *beginning;
		while (temp->next != NULL)
			temp = temp->next;
		temp->next = newNod;
	}
}

void addHashTable(product p, hashTable table) {
	int position = hashFunction(p.id, table);
	addNodList(&table.vector[position], p);
}

void viewList(nodList* beginning) {
	nodList* temp = beginning;
	while (temp != NULL) {
		printf("Name product:%s, Price:%5.2f, Id:%d\n",
			temp->info.name, temp->info.price, temp->info.id);
		temp = temp->next;
	}
}

void viewhashTable(hashTable table) {
	for (int i = 0; i < table.nrElements; i++) {
		if (table.vector[i] != NULL) {
			printf("Position %d\n", i);
			viewList(table.vector[i]);
		}
	}
}

void freeList(nodList* beginning) {
	nodList* aux = beginning;
	while (aux != NULL) {
		nodList* temp = aux->next;
		free(aux->info.name);
		free(aux);
		aux = temp;
	}
}

void freehashTable(hashTable table) {
	for (int i = 0; i < table.nrElements; i++) {
		if (table.vector[i] != NULL) {
			freeList(table.vector[i]);
			
		}
		
	}
	free(table.vector);
}

void deleteNodLista(nodList** beginning, int id,hashTable table,int position)
{
	//if its the 1st nod
	if ((*beginning)->info.id == id) {
		nodList* temp = *beginning;
		table.vector[position] = (*beginning)->next;
		//*beginning = (*beginning)->next;

		free(temp->info.name);
		free(temp);
	}
	else 
	{
		nodList* aux = *beginning;
		while (aux->next != NULL)
		{
			nodList* todelete = aux->next;
			if (todelete->info.id == id)
			{
				nodList* help = todelete;
				aux->next = help->next;
				free(help->info.name);
				free(help);
				return;
			}
			aux = aux->next;
		}
	}
}

void deleteElement(int position, hashTable table,int id) {
	for (int i = 0; i < table.nrElements; i++) {
		if (i == position) 
		{
			deleteNodLista(&table.vector[i], id, table, position);
		}
	}
}

void main() {
	int nrProducts;
	char buffer[20];
	int idInput;
	product p;
	hashTable table;
	table.nrElements = 19;
	table.vector = (nodList**)malloc(sizeof(nodList)*table.nrElements);
	for (int i = 0; i < table.nrElements; i++)
		table.vector[i] = NULL;

	FILE* f = fopen("Text.txt", "r");
	fscanf(f, "%d", &nrProducts);
	for (int i = 0; i < nrProducts; i++) {
		fscanf(f, "%s", buffer);
		p.name = (char*)malloc((strlen(buffer) + 1));
		strcpy(p.name, buffer);
		fscanf(f, "%f", &p.price);
		fscanf(f, "%d", &p.id);

		addHashTable(p, table);
		free(p.name);
	}


	viewhashTable(table);
	printf("Id to delete:");
	scanf("%d", &idInput);
	int position = hashFunction(idInput, table);
	deleteElement(position, table, idInput);
	viewhashTable(table);
	freehashTable(table);

}