#define _CRT_SECURE_NO_WARNINGS
#include<malloc.h>
#include <stdio.h>

typedef struct {
	int zileScadenta;
	char* data;
	char* beneficiar;
	float sumaPlata;
}factura;

typedef struct {
	factura* vect;
	int nrElem;
}heap;

typedef struct {
	factura info;
	struct arboreB* left, * right;
}arboreB;

typedef struct {
	factura info;
	struct nodList* next;
}nodList;


void inserareList(nodList** beg, factura f) {
	nodList* nou = (nodList*)malloc(sizeof(nodList));
	nou->info.sumaPlata = f.sumaPlata;
	nou->info.zileScadenta = f.zileScadenta;
	nou->info.beneficiar = (char*)malloc(strlen(f.beneficiar) + 1);
	strcpy(nou->info.beneficiar, f.beneficiar);
	nou->info.data = (char*)malloc(strlen(f.data) + 1);
	strcpy(nou->info.data, f.data);
	nou->next = NULL;

	if (*beg == NULL)
		(*beg) = nou;
	else {
		nodList* temp = *beg;
		while (temp->next != NULL)
			temp = temp->next;
		temp->next = nou;
	}
}

void afisareLista(nodList* beg) {
	nodList* temp = beg;
	while (temp != NULL) {
		printf("\nZile:%d, Beneficiar:%s", temp->info.zileScadenta, temp->info.beneficiar);
		temp = temp->next;
	}
}

void dezalocaLista(nodList* beg) {
	nodList* temp = beg;
	while (temp != NULL) {
		nodList* aux = temp->next;
		free(temp->info.beneficiar);
		free(temp->info.data);
		free(temp);
		temp = aux;
	}
}

void arboreToLista(arboreB* rad, nodList** beg,int salariuDorit) {
	if (rad != NULL) {
		inserareList(beg, rad->info);
		if (salariuDorit > rad->info.zileScadenta)
			arboreToLista(rad->right, beg, salariuDorit);
		else if (salariuDorit < rad->info.zileScadenta)
			arboreToLista(rad->left, beg, salariuDorit);
	}
}

arboreB* insertNod(arboreB* rad, factura f)
{
	if (rad == NULL) {
		arboreB* nou = (arboreB*)malloc(sizeof(arboreB));
		nou->info.beneficiar = (char*)malloc(strlen(f.beneficiar) + 1);
		strcpy(nou->info.beneficiar, f.beneficiar);
		nou->info.data = (char*)malloc(strlen(f.data) + 1);
		strcpy(nou->info.data, f.data);
		nou->info.sumaPlata = f.sumaPlata;
		nou->info.zileScadenta = f.zileScadenta;
		nou->left = NULL;
		nou->right = NULL;
		return nou;
	}
	else {
		if (f.zileScadenta > rad->info.zileScadenta) {
			rad->right = insertNod(rad->right, f);
			return rad;
		}
		else if (f.zileScadenta < rad->info.zileScadenta) {
			rad->left = insertNod(rad->left, f);
			return rad;
		}
		else
			return rad;
	}
}

void preorder(arboreB* rad) {
	if (rad != NULL) {
		printf("\nZile:%d, Beneficiar:%s", rad->info.zileScadenta, rad->info.beneficiar);
		preorder(rad->left);
		preorder(rad->right);
	}
}

void heapToArbore(heap h, arboreB** rad) {
	for (int i = 0; i < h.nrElem; i++) {
		if (h.vect[i].zileScadenta < 10)
			*rad = insertNod(*rad, h.vect[i]);
	}
}


void heapify(int index, heap h) {
	int indexR = index;
	int indexLeft = 2 * index + 1;
	int indexRight = 2 * index + 2;

	if (indexLeft < h.nrElem && h.vect[indexLeft].zileScadenta > h.vect[indexR].zileScadenta)
		indexR = indexLeft;

	if (indexRight < h.nrElem && h.vect[indexRight].zileScadenta>h.vect[indexR].zileScadenta)
		indexR = indexRight;

	if (index != indexR) {
		factura aux = h.vect[index];
		h.vect[index] = h.vect[indexR];
		h.vect[indexR] = aux;

		heapify(indexR, h);
	}
}

heap inserare(heap h, factura f) {
	factura* vectNou = (factura*)malloc(sizeof(factura) * (h.nrElem + 1));
	for (int i = 0; i < h.nrElem; i++)
		vectNou[i] = h.vect[i];
	vectNou[h.nrElem] = f;
	h.nrElem++;


	free(h.vect);
	h.vect = vectNou;

	for (int i = (h.nrElem - 1) / 2; i >= 0; i--)
		heapify(i, h);

	return h;
}

void dezalocareArbore(arboreB* rad) {
	if (rad != NULL) {
		free(rad->info.beneficiar);
		free(rad->info.data);
		dezalocareArbore(rad->left);
		dezalocareArbore(rad->right);
		free(rad);
	}
}

void afisare(heap h) {
	for (int i = 0; i < h.nrElem; i++) {
		printf("\nZile pana scadenta:%d, Beneficiar:%s", h.vect[i].zileScadenta, h.vect[i].beneficiar);
	}
}

heap eleminarenoduri(heap h) {
	int contor = 0;
	for (int i = 0; i < h.nrElem; i++) {
		if (h.vect[i].zileScadenta < 3)
			contor++;
	}
	factura* vectnou = (factura*)malloc(sizeof(factura) * (h.nrElem - contor));
	for (int i = 0; i < h.nrElem - contor; i++) {
		if (h.vect[i].zileScadenta > 3)
			vectnou[i] = h.vect[i];
	}
	h.nrElem = h.nrElem - contor;
	free(h.vect);
	h.vect = vectnou;
	for (int i = (h.nrElem - 1) / 2; i >= 0; i--)
		heapify(i, h);

	return h;
}

void dezalocareHeap(heap h) {
	for (int i = 0; i < h.nrElem; i++) {
		free(h.vect[i].beneficiar);
		free(h.vect[i].data);
	}
	free(h.vect);
}

void main() {
	heap h;
	factura fac;
	char buffer[20];
	FILE* f = fopen("Text.txt", "r");
	fscanf(f, "%d", &h.nrElem);

	h.vect = (factura*)malloc(sizeof(factura) * h.nrElem);
	for (int i = 0; i < h.nrElem; i++) {
		fscanf(f, "%d", &h.vect[i].zileScadenta);
		fscanf(f, "%s", buffer);
		h.vect[i].data = (char*)malloc(strlen(buffer) + 1);
		strcpy(h.vect[i].data, buffer);
		fscanf(f, "%s", buffer);
		h.vect[i].beneficiar = (char*)malloc(strlen(buffer) + 1);
		strcpy(h.vect[i].beneficiar, buffer);
		fscanf(f, "%f", &h.vect[i].sumaPlata);

	}

	fclose(f);
	for (int i = (h.nrElem - 1) / 2; i >= 0; i--)
		heapify(i, h);

	afisare(h);
	/*factura fac2;
	printf("\n Zile scadenta:");
	scanf("%d", &fac2.zileScadenta);
	printf("\nData:");
	scanf("%s", buffer);
	fac2.data = (char*)malloc(strlen(buffer) + 1);
	strcpy(fac2.data, buffer);
	printf("\nBeneficiar:");
	scanf("%s", buffer);
	fac2.beneficiar = (char*)malloc(strlen(buffer) + 1);
	strcpy(fac2.beneficiar, buffer);
	printf("\nSuma plata:");
	scanf("%f", &fac2.sumaPlata);

	h = inserare(h, fac2);*/

	/*printf("\n----------------");
	h = eleminarenoduri(h);
	afisare(h);*/

	printf("\n-----------------");
	arboreB* rad = NULL;
	heapToArbore(h, &rad);
	preorder(rad);
	printf("\n-----------------");
	nodList* beg = NULL;
	int plata;
	printf("\nIntroduceti nodul cu ziua de scadenta pana la care doriti sa copiati:");
	scanf("%d", &plata);
	arboreToLista(rad, &beg, plata);
	afisareLista(rad);

	dezalocareHeap(h);
	dezalocareArbore(rad);

}

