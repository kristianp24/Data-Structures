#define _CRT_SECURE_NO_WARNINGS
#include <malloc.h>
#include <stdio.h>

typedef struct {
	unsigned int nrCursa;
	char* dataCursa;
	unsigned char nrVagoane;
	unsigned short int nrBileteCump[2];
	float pretBileta[2];
}cursaFeroviara;

typedef struct {
	cursaFeroviara info;
	struct nodArb* left, * right;
}nodArb;

nodArb* createNod(nodArb* left, nodArb* right, cursaFeroviara c) {
	nodArb* nou = (nodArb*)malloc(sizeof(nodArb));
	nou->info.nrCursa = c.nrCursa;
	nou->info.dataCursa = (char*)malloc(strlen(c.dataCursa) + 1);
	strcpy(nou->info.dataCursa, c.dataCursa);
	nou->info.nrVagoane = c.nrVagoane;
	for (int i = 0; i < 2; i++)
		nou->info.nrBileteCump[i] = c.nrBileteCump[i];
	for (int i = 0; i < 2; i++)
		nou->info.pretBileta[i] = c.pretBileta[i];
	nou->left = left;
	nou->right = right;

	return nou;
}

nodArb* insertNod(nodArb* rad, cursaFeroviara c) {
	if (rad == NULL)
		return createNod(NULL, NULL, c);
	else {
		if (c.nrCursa < rad->info.nrCursa) {
			rad->left = insertNod(rad->left, c);
			return rad;
		}
		else if (c.nrCursa > rad->info.nrCursa) {
			rad->right = insertNod(rad->right, c);
			return rad;
		}
		else
			return rad;
	}
}

void preorder(nodArb* rad) {
	if (rad != NULL) {
		printf("\nNr cursa:%d, Data:%s, Nr vag:%u,Nr Bilete Cump: ", rad->info.nrCursa, rad->info.dataCursa, rad->info.nrVagoane);
		
		for (int i = 0; i < 2; i++)
			printf(" %hu,", rad->info.nrBileteCump[i]);
		printf(", Pret Bilet:");
		for (int j = 0; j < 2; j++)
			printf(" %5.2f,", rad->info.pretBileta[j]);
		preorder(rad->left);
		preorder(rad->right);

	}
}

void inorder(nodArb* rad) {
	if (rad != NULL) {
		inorder(rad->left);
		printf("\nNr cursa:%d, Data:%s, Nr vag:%u,Nr Bilete Cump: ", rad->info.nrCursa, rad->info.dataCursa, rad->info.nrVagoane);

		for (int i = 0; i < 2; i++)
			printf(" %hu,", rad->info.nrBileteCump[i]);
		printf(", Pret Bilet:");
		for (int j = 0; j < 2; j++)
			printf(" %5.2f,", rad->info.pretBileta[j]);
		inorder(rad->right);
	}
}

void postorder(nodArb* rad) {
	if (rad != NULL) {
		postorder(rad->left);
		postorder(rad->right);
		printf("\nNr cursa:%d, Data:%s, Nr vag:%u,Nr Bilete Cump: ", rad->info.nrCursa, rad->info.dataCursa, rad->info.nrVagoane);

		for (int i = 0; i < 2; i++)
			printf(" %hu,", rad->info.nrBileteCump[i]);
		printf(", Pret Bilet:");
		for (int j = 0; j < 2; j++)
			printf(" %5.2f,", rad->info.pretBileta[j]);
	}
}

void freeMemory(nodArb* rad) {
	if(rad!=NULL){
		free(rad->info.dataCursa);
		freeMemory(rad->left);
		freeMemory(rad->right);
		free(rad);
	}
}

void nrBileteCumpClasa2(nodArb* rad, int* suma) {
	if (rad != NULL) {
		(*suma) = (*suma) + rad->info.nrBileteCump[1];
		nrBileteCumpClasa2(rad->left, suma);
		nrBileteCumpClasa2(rad->right, suma);
	}
}

void modificaPretBilet(nodArb* rad, char* data,float procentModificarePret) {
	if (rad != NULL) {
		if (strcmp(rad->info.dataCursa, data) == 0)
			rad->info.pretBileta[0] = (rad->info.pretBileta[0] * procentModificarePret) + rad->info.pretBileta[0];
		modificaPretBilet(rad->left,data,procentModificarePret);
		modificaPretBilet(rad->right,data,procentModificarePret);

	}
}

void incasariMaxime(nodArb* rad, cursaFeroviara** aleasa,float* incasariMax) {
	if (rad != NULL) {
		float incasari = (rad->info.nrBileteCump[0] * rad->info.pretBileta[0]) + (rad->info.nrBileteCump[1] * rad->info.pretBileta[1]);
		if (incasari >= *incasariMax) {
			(*incasariMax) = incasari;
			(*aleasa) = &rad->info;
		}
		incasariMaxime(rad->left, aleasa, incasariMax);
		incasariMaxime(rad->right, aleasa, incasariMax);
	}
	
}

void salvareVector(nodArb* rad, cursaFeroviara* vect, int* contor) {
	if (rad != NULL) {
		if (rad->left == NULL && rad->right == NULL) {
			vect[(*contor)].dataCursa = (char*)malloc(strlen(rad->info.dataCursa) + 1);
			strcpy(vect[(*contor)].dataCursa, rad->info.dataCursa);
			vect[(*contor)].nrCursa = rad->info.nrCursa;
			vect[(*contor)].nrVagoane = rad->info.nrVagoane;
			vect[(*contor)].nrBileteCump[0] = rad->info.nrBileteCump[0];
			vect[(*contor)].nrBileteCump[1] = rad->info.nrBileteCump[1];
			vect[(*contor)].pretBileta[0] = rad->info.pretBileta[0];
			vect[(*contor)].pretBileta[1] = rad->info.pretBileta[1];
			(*contor)++;
		}
		salvareVector(rad->left, vect, contor);
		salvareVector(rad->right, vect, contor);
	}
}


void main() {
	int nrNod;
	nodArb* rad = NULL;
	char buffer[20];
	cursaFeroviara c;
	FILE* f = fopen("Text.txt", "r");
	fscanf(f, "%d", &nrNod);
	for (int i = 0; i < nrNod; i++) {
		fscanf(f, "%d", &c.nrCursa);
		fscanf(f, "%s", buffer);
		c.dataCursa = (char*)malloc(strlen(buffer) + 1);
		strcpy(c.dataCursa, buffer);
		fscanf(f, "%u", &c.nrVagoane);
		
		fscanf(f, "%hu", &c.nrBileteCump[0]);
		fscanf(f, "%hu", &c.nrBileteCump[1]);
		
		fscanf(f, "%f", &c.pretBileta[0]);
		fscanf(f, "%f", &c.pretBileta[1]);
		rad = insertNod(rad, c);
		free(c.dataCursa);
	}
fclose(f);
	printf("\n------------------");
	preorder(rad);
	/*printf("\n------------------");
	inorder(rad);
	printf("\n------------------");
	postorder(rad);*/
	printf("\n------------------");
	int suma = 0;
	nrBileteCumpClasa2(rad, &suma);
	printf("\nNumar bilete cump clasa 2:%d", suma);
	printf("\n------------------");
	/*float procent;
	printf("\n Data care  vreti sa modificati pretul:");
	scanf("%s", buffer);
	printf("\nProcentul de schimbare:");
	scanf("%f", &procent);
	modificaPretBilet(rad, buffer, procent);
	preorder(rad);*/
	printf("\n------------------");
	float incasariMax = 0;
	cursaFeroviara* ales = NULL;
	incasariMaxime(rad, &ales, &incasariMax);
	printf("\nNr cursa:%d, Data:%s, Nr vag:%u,Nr Bilete Cump: ", ales->nrCursa, ales->dataCursa, ales->nrVagoane);

	for (int i = 0; i < 2; i++)
		printf(" %hu,",ales->nrBileteCump[i]);
	printf(", Pret Bilet:");
	for (int j = 0; j < 2; j++)
		printf(" %5.2f,",ales->pretBileta[j]);
	printf("\nIncasarile:%5.2f", incasariMax);
	printf("\n------------------");
	cursaFeroviara* vect = (cursaFeroviara*)malloc(sizeof(cursaFeroviara) * nrNod);
	int contor = 0;
	salvareVector(rad, vect, &contor);
	for (int i = 0; i < contor; i++) {
		printf("\nNr cursa:%d, Data:%s, Nr vag:%u,Nr Bilete Cump: ", vect[i].nrCursa, vect[i].dataCursa, vect[i].nrVagoane);

		for (int i = 0; i < 2; i++)
			printf(" %hu,", vect[i].nrBileteCump[i]);
		printf(", Pret Bilet:");
		for (int j = 0; j < 2; j++)
			printf(" %5.2f,",vect[i].pretBileta[j]);
	}



	freeMemory(rad);
	
}