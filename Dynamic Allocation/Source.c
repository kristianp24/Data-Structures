#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <malloc.h>

typedef struct {
	int id;
	char* nume;
	float taxa;
	short int avg;
}student;

void citireStudent(student* s, int nr) {
	char buffer[50];
	for (int i = 0; i < nr; i++) {
		printf("\nId:");
		scanf("%d", &s[i].id);
		printf("Nume:");
		scanf("%s", buffer);
		s[i].nume = (char*)malloc((strlen(buffer) + 1) * sizeof(char));
		strcpy(s[i].nume, buffer);
		printf("Taxa:");
		scanf("%f", &s[i].taxa);
		printf("Media:");
		scanf("%d", &s[i].avg);
	}
}

void afisareStudent(student* s, int nr) {
	for (int i = 0; i < nr; i++) {
		printf("\nId=%d, Nume=%s, Taxa=%5.2f, Media=%d",
			s[i].id, s[i].nume, s[i].taxa, s[i].avg);
	}
}

void dezalocare(student* s,int nr) {
	for (int i = 0; i < nr; i++) {
		free(s[i].nume);
	}
	free(s);
}

void citireVcetori(int* id, char** nume, float* taxa, int* medii, int nr) {
	char buffer[50];
	for (int i = 0; i < nr; i++) {
		printf("\nId:");
		scanf("%d", &id[i]);
		printf("Nume:");
		scanf("%s", buffer);
	    nume[i] = (char*)malloc((strlen(buffer) + 1) * sizeof(char));
		strcpy(nume[i], buffer);
		printf("Taxa:");
		scanf("%f", &taxa[i]);
		printf("Media:");
		scanf("%d",&medii[i]);
	}
}

void afisareVectori(int* id, char** nume, float* taxa, int* medii, int nr) {
	for (int i = 0; i < nr; i++) {
		printf("\n Id=%d ,Nume=%s ,Taxa=%f ,Media=%d",
			id[i], nume[i], taxa[i], medii[i]);
    }
   
}

void dezalocareVcet(int* id, char** nume, float* taxa, int* medii, int nr) {
	for (int i = 0; i < nr; i++) {
		free(nume[i]);
	}
	free(id);
	free(nume);
	free(taxa);
	free(medii);
}

void citireMatrice(int** matrice, char** num, int nr) {
	char buffer[50];
	for (int i = 0; i < nr; i++) {
		printf("Id:");
		scanf("%d", &matrice[i][0]);
		printf("Nume:");
		scanf("%s", buffer);
		num[i] = (char*)malloc(strlen(buffer) + 1);
		strcpy(num[i], buffer);
		printf("Taxa:");
		scanf("%d", &matrice[i][1]);
		printf("Media:");
		scanf("%d", &matrice[i][2]);
	}
}

void afisareMatrice(int** matrice, char** num, int nr) {
	for (int i = 0; i < nr; i++) {
		printf("\n Id:%d , Nume=%s , Taxa=%d, Media=%d ",
			matrice[i][0], num[i], matrice[i][1], matrice[i][2]);
	}
}

void dezalocareMatrice(int** matrice, char** num, int nr) {
	

	for (int i = 0; i < nr; i++) {
		free(num[i]);
		free(matrice[i]);
	}
	free(num);
	free(matrice);

}

int main() {
	int nr;
	printf("\nNo. of students:");
	scanf("%d", &nr);
	/*citireStudent(s, nr);
	afisareStudent(s, nr);
	dezalocare(s, nr);*/

	/*int* id = (int*)malloc(nr * sizeof(int));
	char** nume = (char**)malloc(nr * sizeof(char*));
	float* taxa = (float*)malloc(nr * sizeof(float));
	int* medii = (int*)malloc(nr * sizeof(int));
	citireVcetori(id, nume, taxa, medii,nr);
	afisareVectori(id, nume, taxa, medii, nr);*/

	//int nr;
	//FILE* f = fopen("Text.txt", "r");
	//fscanf(f, "%d", &nr);
	//student* s = (student*)malloc(nr * sizeof(student));
	//char buffer[50];
	//for (int i = 0; i < nr; i++) {
	//	fscanf(f, "%d", &s[i].id);
	//	fscanf(f, "%s", buffer);
	//	s[i].nume = (char*)malloc(nr * (strlen(buffer) + 1));
	//	strcpy(s[i].nume, buffer);
	//	fscanf(f, "%f", &s[i].taxa);
	//	fscanf(f, "%d", &s[i].avg);
	//}

	//for (int i = 0; i < nr; i++) {
	//	printf("\n Id=%d, Nume=%s, Taxa=%5.2f, Media=%d",
	//		s[i].id, s[i].nume, s[i].taxa, s[i].avg);
	//}
	//fclose(f);

	int** matrice = (int**)malloc(nr * sizeof(int*));
	for (int i = 0; i < nr; i++) {
		matrice[i] = (int*)malloc(3* sizeof(int));
	}
	char** numele = (char*)malloc(nr * sizeof(char*));
	citireMatrice(matrice, numele, nr);
	afisareMatrice(matrice, numele, nr);
	dezalocareMatrice(matrice, numele, nr);


}