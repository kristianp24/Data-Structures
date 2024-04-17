#define _CRT_SECURE_NO_WARNINGS
#include <malloc.h>
#include <stdio.h>

typedef struct {
	int canitate;
	char* name;
	float pret;
}product;

typedef struct {
	product* vector;
	int nrElements;
}heap;

void filatrare(heap h, int index) {
	int indexRoot = index;
	int indexLeft = 2 * index + 1;
	int indexRight = 2 * index + 2;

	if (indexLeft < h.nrElements && h.vector[indexLeft].canitate > h.vector[indexRoot].canitate)
		indexRoot = indexLeft;
	if (indexRight < h.nrElements && h.vector[indexRight].canitate > h.vector[indexRoot].canitate)
		indexRoot = indexRight;

	if (index != indexRoot) {
		product p = h.vector[index];
		h.vector[index] = h.vector[indexRoot];
		h.vector[indexRoot] = p;

		filatrare(h, indexRoot);
	}
}

heap addInHeap(heap h, product newprod) {
	product* newVect = (product*)malloc((h.nrElements + 1) * sizeof(product));
	for (int i = 0; i < h.nrElements; i++)
		newVect[i] = h.vector[i];

	newVect[h.nrElements] = newprod;
	h.nrElements++;
	free(h.vector);
	h.vector = newVect;

	for (int i = (h.nrElements - 1) / 2; i >= 0; i--)
		filatrare(h, i);

	return h;
}

heap getElement(heap h, product* element) {
	product* newVect = (product*)malloc((h.nrElements - 1) * sizeof(product));


	//Interschimb nods
	product p = h.vector[0];
	h.vector[0] = h.vector[h.nrElements - 1];
	h.vector[h.nrElements - 1] = p;

	*element = h.vector[h.nrElements - 1];
	h.nrElements--;
	for (int i = 0; i < h.nrElements; i++)
		newVect[i] = h.vector[i];
	free(h.vector);
	h.vector = newVect;

	for (int i = (h.nrElements - 1) / 2; i >= 0; i--)
		filatrare(h, i);

	return h;
}

void viewHeap(heap h) {
	for (int i = 0; i < h.nrElements; i++)
		printf("\n Name:%s, Quantity:%d, Price:%5.2f",
			h.vector[i].name, h.vector[i].canitate, h.vector[i].pret);

}

void freeHeap(heap h) {
	for (int i = 0; i < h.nrElements; i++)
		free(h.vector[i].name);
	free(h.vector);
}

int main() {
	heap h;
	product p;
	char buffer[30];

	FILE* f = fopen("Text.txt", "r");
	fscanf(f, "%d", &h.nrElements);
	h.vector = (product*)malloc(h.nrElements * sizeof(product));
	for (int i = 0; i < h.nrElements; i++) {
		fscanf(f, "%s", buffer);
		h.vector[i].name = (char*)malloc(strlen(buffer) + 1);
		strcpy(h.vector[i].name, buffer);
		fscanf(f, "%d", &h.vector[i].canitate);
		fscanf(f, "%f", &h.vector[i].pret);
	}
	fclose(f);
	for (int i = (h.nrElements - 1) / 2; i >= 0; i--)
		filatrare(h, i);

	viewHeap(h);


	product ext;
	h = getElement(h, &ext);
	printf("\nExt-> Name:%s, Quantity:%d, Price:%5.2f", ext.name, ext.canitate, ext.pret);

	/*for (int i = (h.nrElements - 1) / 2; i >= 0; i--)
		filatrare(h, i);*/

	viewHeap(h);

	freeHeap(h);
}