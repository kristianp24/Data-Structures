#include<malloc.h>
#include<stdio.h>

typedef struct {
	unsigned int cod;
	char* titlu;
	char* beneficiar;
	unsigned short int durata;
	float buget;
}proiect;

typedef struct {
	proiect info;
	struct nodArb* stanga, * dreapta;
}nodArb;

nodArb* creareNod(nodArb* st, nodArb* dr, proiect p) {
	nodArb* nou = (nodArb*)malloc(sizeof(nodArb));
	nou->info.beneficiar = (char*)malloc(strlen(p.beneficiar) + 1);
	strcpy(nou->info.beneficiar, p.beneficiar);
	nou->info.titlu = (char*)malloc(strlen(p.titlu) + 1);
	strcpy(nou->info.titlu, p.titlu);
	nou->info.buget = p.buget;
	nou->info.cod = p.cod;
	nou->info.durata = p.durata;
	nou->dreapta = dr;
	nou->stanga = st;

	return nou;
}

nodArb* inserareNod(nodArb* rad, proiect p) {
	if (rad != NULL) {
		if (rad->info.cod > p.cod) {
			rad->stanga = inserareNod(rad->stanga, p);
			return rad;
		}
		else {
			if (rad->info.cod < p.cod) {
				rad->dreapta = inserareNod(rad->dreapta, p);
				return rad;
			}
			else
				return rad;
		}
	}
	else {
		return creareNod(NULL, NULL, p);
	}
}

void preorder(nodArb* rad) {
	if (rad != NULL) {
		printf("\nCod:%d, Beneficiar:%s, Salariul:%5.2f", rad->info.cod, rad->info.beneficiar, rad->info.buget);
		preorder(rad->stanga);
		preorder(rad->dreapta);
	}
}

void inorder(nodArb* rad) {
	if (rad != NULL) {
		inorder(rad->stanga);
		printf("\nCod:%d, Beneficiar:%s, Salariul:%5.2f", rad->info.cod, rad->info.beneficiar, rad->info.buget);
		inorder(rad->dreapta);
	}
}

void postorder(nodArb* rad) {
	if (rad != NULL) {
		postorder(rad->stanga);
		postorder(rad->dreapta);
		printf("\nCod:%d, Beneficiar:%s, Salariul:%5.2f", rad->info.cod, rad->info.beneficiar,rad->info.buget);

	}
}

void freeMem(nodArb* rad) {
	if (rad != NULL) {
		freeMem(rad->stanga);
		freeMem(rad->dreapta);
		free(rad->info.beneficiar);
		free(rad->info.titlu);
		free(rad);
	}
}

void  gasesteBeneficiar(nodArb* rad, const char* benefic,int* nr) {
	
	if (rad != NULL) {
		if (strcmp(rad->info.beneficiar) == 0)
			(*nr)++;
		gasesteBeneficiar(rad->stanga, benefic, nr);
		gasesteBeneficiar(rad->dreapta, benefic, nr);
	}
}

void modificaBuget(nodArb* rad, int codul, float coef) {
	if (rad != NULL) {
		if (rad->info.cod == codul)
			rad->info.buget = (rad->info.buget * coef) + rad->info.buget;
		if (codul > rad->info.cod)
			modificaBuget(rad->dreapta,codul,coef);
		else if (codul < rad->info.cod)
			modificaBuget(rad->stanga,codul,coef);
	}
}
void totalNodFrunza(nodArb* rad,int* nr) {
	if (rad != NULL) {
		if (rad->dreapta == NULL && rad->stanga == NULL)
			(*nr)++;
		totalNodFrunza(rad->stanga, nr);
		totalNodFrunza(rad->dreapta, nr);
	}
}

void salvareVector(nodArb* rad, int durataPrag,proiect* vector,int* nr) {
	if (rad != NULL) {
		if (rad->info.durata > durataPrag) {
			vector[(*nr)].cod = rad->info.cod;
			vector[(*nr)].beneficiar = (char*)malloc(strlen(rad->info.beneficiar) + 1);
			strcpy(vector[(*nr)].beneficiar, rad->info.beneficiar);
			vector[(*nr)].titlu = (char*)malloc(strlen(rad->info.titlu) + 1);
			strcpy(vector[(*nr)].titlu, rad->info.titlu);
			vector[(*nr)].buget = rad->info.buget;
			vector[(*nr)].durata = rad->info.durata;
			(*nr)++;
 
		}
		salvareVector(rad->stanga, durataPrag, vector, nr);
		salvareVector(rad->dreapta, durataPrag, vector, nr);

	}

}

void main() {
	int nrNod;
	char buffer[30];
	proiect p;
	nodArb* rad = NULL;
	FILE* f = fopen("Text.txt", "r");
	fscanf(f, "%d", &nrNod);
	for (int i = 0; i < nrNod; i++) {
		fscanf(f, "%d", &p.cod);
		
		fscanf(f, "%s", buffer);
		p.titlu = (char*)malloc(strlen(buffer) + 1);
		strcpy(p.titlu, buffer);
		
		fscanf(f, "%s", buffer);
		p.beneficiar = (char*)malloc(strlen(buffer) + 1);
		strcpy(p.beneficiar, buffer);
		
		fscanf(f, "%d", &p.durata);
		fscanf(f, "%f", &p.buget);

		rad = inserareNod(rad, p);
		free(p.beneficiar);
		free(p.titlu);

	}
	fclose(f);
	//preorder(rad);
	printf("\n-----------------");
	//inorder(rad);
	printf("\n-----------------");
	postorder(rad);
	printf("\n-----------------");
	int ben = 0;
	gasesteBeneficiar(rad, "Ana", &ben);
	printf("\nBeneficiarul apare de:%d ori", ben);
	printf("\n-----------------");
	int cod = 0;
	/*float coef;
	printf("\nIntrodu codul caruia vrei sa ii schimbi salariul:");
	scanf("%d", &cod);
	printf("\nIntrodu coef de crestere:");
	scanf("%f", &coef);
	modificaBuget(rad, cod, coef);
	postorder(rad);*/
	printf("\n-----------------");
	int nodFrunze = 0;
	totalNodFrunza(rad, &nodFrunze);
	printf("\nSunt %d noduri frunze.", nodFrunze);
	printf("\n-----------------");
	proiect* vect = (proiect*)malloc(sizeof(proiect) * nrNod);
	//for (int i = 0; i < nrNod; i++)
		//vect[i] = NULL;
	int pragDurata;
	int contor = 0;
	printf("\nIntroduceti o durata ca prag:");
	scanf("%d", &pragDurata);
	salvareVector(rad, pragDurata, vect, &contor);
	for(int i=0;i<contor;i++)
		printf("\nCod:%d, Beneficiar:%s, Salariul:%5.2f, Durata:%d",vect[i].cod, vect[i].beneficiar, vect[i].buget,vect[i].durata);


    for (int i = 0; i < contor; i++) {
		free(vect[i].beneficiar);
		free(vect[i].titlu);
	}
	free(vect);
		
	freeMem(rad);

}