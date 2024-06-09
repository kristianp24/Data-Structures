#include <malloc.h>
#include <stdio.h>

typedef struct {
	char* specialitate;
	char* numeMedic;
	char* diagnostic;
	char* data;
	float pretConsultatie;
}consultatie;

typedef struct {
	consultatie info;
	struct nodLS* next;
}nodLS;

typedef struct {
	struct nodLS* info;
	struct nodLP* next;
}nodLP;


void inserareLS(nodLS** beg, consultatie info) {
	nodLS* nou = (nodLS*)malloc(sizeof(nodLS));
	nou->info.data = (char*)malloc(strlen(info.data) + 1);
	strcpy(nou->info.data, info.data);
	nou->info.diagnostic = (char*)malloc(strlen(info.diagnostic) + 1);
	strcpy(nou->info.diagnostic, info.diagnostic);
	nou->info.numeMedic = (char*)malloc(strlen(info.numeMedic) + 1);
	strcpy(nou->info.numeMedic, info.numeMedic);
	nou->info.specialitate = (char*)malloc(strlen(info.specialitate) + 1);
	strcpy(nou->info.specialitate, info.specialitate);
	nou->info.pretConsultatie = info.pretConsultatie;
	nou->next = NULL;

	if ((*beg) == NULL)
		(*beg) = nou;
	else {
		nodLS* temp = (*beg);
		while (temp->next != NULL)
			temp = temp->next;
		temp->next = nou;
	}
}


void inserareLP(nodLP** beg, nodLS* begLS) {
	nodLP* nou = (nodLP*)malloc(sizeof(nodLP));
	nou->next = NULL;
	nou->info = begLS;

	if ((*beg) == NULL)
		(*beg) = nou;
	else {
		nodLP* temp = (*beg);
		while (temp->next != NULL)
			temp = temp->next;
		temp->next = nou;
	}
}

void afisareLS(nodLS* beg) {
	nodLS* temp = beg;
	while (temp != NULL) {
		printf("\nSpecialitate:%s, Data:%s, Nume Medic:%s, pret:%5.2f, Diagnoza:%s",
			temp->info.specialitate, temp->info.data, temp->info.numeMedic, temp->info.pretConsultatie,temp->info.diagnostic);
		temp = temp->next;
	}
}

void afisareLP(nodLP* beg) {
	nodLP* temp = beg;
	int i = 1;
	while (temp != NULL) {
		printf("\nSublista %d", i);
		if (temp->info != NULL)
			afisareLS(temp->info);
		i++;
		temp = temp->next;
		
			
	}
}

void dezalocaLS(nodLS* beg) {
	nodLS* temp = beg;
	while (temp != NULL)
	{
		nodLS* aux = temp->next;
		free(temp->info.data);
		free(temp->info.diagnostic);
		free(temp->info.numeMedic);
		free(temp->info.specialitate);
		free(temp);
		temp = aux;
		
	}
}

void dezalocareLP(nodLP* beg) {
	nodLP* temp = beg;
	while (temp != NULL) {
		nodLP* aux = temp->next;
		dezalocaLS(temp->info);
		free(temp);
		temp = aux;
	}
}

int valTotalaConsultati(nodLP* beg, const char* specialitate) {
	int contor = 0;
	nodLP* temp = beg;
	while (temp != NULL) {
		nodLS* aux = temp->info;
		if (strcmp(aux->info.specialitate, specialitate) == 0) {
			while (aux != NULL) {
				contor++;
				aux = aux->next;
			}
			return contor;
		}
		temp = temp->next;
	}
	return 0;

}

void modificarePret(nodLP* beg, const char* data, float pretNou) {
	nodLP* temp = beg;
	while (temp != NULL) {
		nodLS* aux = temp->info;
		while (aux != NULL) {
			if (strcmp(aux->info.data, data) == 0) {
				aux->info.pretConsultatie = pretNou;

			}
			aux = aux->next;
		}
		temp = temp->next;
	}
}

//Gresit, nu modul care se cere.
// void deleteNod(nodLP* begLP, const char* diag) {
// 	nodLP* tempLP = begLP;
// 	while (tempLP != NULL) {
// 		nodLS* aux = tempLP->info;
// 		//nodLS* aux = tempLS;
		
		
// 			while (aux != NULL)
// 			{
// 				if (strcmp(aux->info.diagnostic, diag) == 0) {
// 					nodLS* temp = aux->next;
// 					//aux = aux->next;
// 					free(aux->info.data);
// 					free(aux->info.numeMedic);
// 					free(aux->info.specialitate);
// 					free(aux);
// 					tempLP->info = temp;
// 					aux = temp;
// 				}

// 				else
// 				{
// 					nodLS* ajutor = aux->next;
// 					if (ajutor != NULL) {


// 						if (strcmp(ajutor->info.diagnostic, diag) == 0) {
// 							nodLS* newnext = ajutor->next;
// 							free(ajutor->info.data);
// 							free(ajutor->info.numeMedic);
// 							free(ajutor->info.specialitate);
// 							free(ajutor);
// 							aux->next = newnext;
// 							aux = aux->next;

// 						}
// 						else
// 							aux = aux->next;
// 					}
// 					else {
// 						aux = aux->next;
// 					}

//       			}
// 				//aux = aux->next;

// 			}
		
		
		
// 		tempLP = tempLP->next;
// 	}
// }

void salvareConsultatiVector(nodLP* begLP, consultatie* vector, int* contor, float pret) {
	nodLP* temp = begLP;
	while (temp != NULL) {
		nodLS* aux = temp->info;
		while (aux != NULL) {
			if (aux->info.pretConsultatie > pret) {
				vector[(*contor)].data = (char*)malloc(strlen(aux->info.data) + 1);
				strcpy(vector[(*contor)].data, aux->info.data);
				vector[(*contor)].diagnostic = (char*)malloc(strlen(aux->info.diagnostic) + 1);
				strcpy(vector[(*contor)].diagnostic, aux->info.diagnostic);
				vector[(*contor)].numeMedic = (char*)malloc(strlen(aux->info.numeMedic) + 1);
				strcpy(vector[(*contor)].numeMedic, aux->info.numeMedic);
				vector[(*contor)].specialitate = (char*)malloc(strlen(aux->info.specialitate) + 1);
				strcpy(vector[(*contor)].specialitate, aux->info.specialitate);
				vector[(*contor)].pretConsultatie = aux->info.pretConsultatie;
				(*contor)++;
				aux = aux->next;
			}
			else {
				aux = aux->next;
			}
		}
		temp = temp->next;
	}
}


void main() {
	int nr;
	char buffer[30];
	FILE* f = fopen("Text.txt", "r");
	fscanf(f, "%d", &nr);
	nodLP* begLP = NULL;
	nodLS** begsLS = (nodLS*)malloc(sizeof(nodLS*) * nr);
	for (int i = 0; i < nr; i++) {
		begsLS[i] = NULL;
	}
	
	consultatie c;
	int j  = 0;
	for (int i = 0; i < nr; i++) {
		fscanf(f, "%s", buffer);
		c.specialitate = (char*)malloc(strlen(buffer) + 1);
		strcpy(c.specialitate, buffer);
		fscanf(f, "%s", buffer);
		c.data = (char*)malloc(strlen(buffer) + 1);
		strcpy(c.data, buffer);
		fscanf(f, "%s", buffer);
		c.numeMedic = (char*)malloc(strlen(buffer) + 1);
		strcpy(c.numeMedic, buffer);
		fscanf(f, "%s", buffer);
		c.diagnostic = (char*)malloc(strlen(buffer) + 1);
		strcpy(c.diagnostic, buffer);
		fscanf(f, "%f", &c.pretConsultatie);

		if (begsLS[0] == NULL) {
			inserareLS((&begsLS[0]),c);
			j++;
		}
		else {
			int contor = j;
			for (int i = 0; i < nr; i++) {
				if (begsLS[i] != NULL) {
					if (strcmp(begsLS[i]->info.specialitate, c.specialitate) == 0) {
						inserareLS(&begsLS[i], c);
						contor++;
						break;
					}
						
				}
			}

			if (contor == j) {
				
				inserareLS(&begsLS[j], c);
				j++;
			}
		}

		free(c.data);
		free(c.numeMedic);
		free(c.diagnostic);
		free(c.specialitate);
    }

	for (int i = 0; i < j; i++) {
		inserareLP(&begLP, begsLS[i]);
	}
	
	afisareLP(begLP);
    
	
	printf("\n-----------------");
	char spec[30];
	/*printf("\nIntroduceti speciaitatea dorita:");
	scanf("%s", spec);
	int cons = valTotalaConsultati(begLP, spec);
	printf("\n Exista %d consultati pentru specialitatea de %s", cons, spec);*/
	
	printf("\n-----------------");
	char dataNoua[30];
	float pretNoua;
	/*printf("\nIntroduceti data in care doriti sa modificati pretul:");
	scanf("%s", dataNoua);
	printf("\nIntroduceti noul pret:");
	scanf("%f", &pretNoua);
	modificarePret(begLP, dataNoua, pretNoua);*/
	printf("\n-----------------");
	/*char diag[30];
	printf("\nIntroduceti diagnoza pe care vreti sa stergeti:");
	scanf("%s", diag);
	deleteNod(begLP, diag);
	afisareLP(begLP);*/
	printf("\n-----------------");
	float pretCons;
	printf("\nIntroduceti un pret minim pt consultatie:");
	scanf("%f", &pretCons);
	consultatie* vect = (consultatie*)malloc(sizeof(consultatie) * nr);
	int contor = 0;
	salvareConsultatiVector(begLP, vect, &contor, pretCons);
	for (int i = 0; i < contor; i++) {
		printf("\nSpecialitate:%s, Data:%s, Nume Medic:%s, pret:%5.2f, Diagnoza:%s",
			vect[i].specialitate, vect[i].data, vect[i].numeMedic, vect[i].pretConsultatie, vect[i].diagnostic);
	}

	//dezalocare vector
	for (int i = 0; i < contor; i++) {
		free(vect[i].data);
		free(vect[i].diagnostic);
		free(vect[i].numeMedic);
		free(vect[i].specialitate);
	}
	free(vect);
	
//dezalocare
	dezalocareLP(begLP);


	fclose(f);
}
