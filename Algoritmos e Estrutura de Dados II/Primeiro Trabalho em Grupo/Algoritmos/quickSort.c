#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define VETSIZ 1000000


	// Rearranja v tal que v[p..j-1] <= v[j] < v[j+1..r].
int separa (int j, int r, int * v)
{
	int pivo, k, trocaAux;
	pivo = v[r]; //Define r como o pivô
	for (k = j; k < r; k++)
		if(v[k] <= pivo) 
			trocaAux = v[j], v[j++] = v[k], v[k] = trocaAux; // Troca v[j] e v[k] e adiciona um a j.		
			
	v[r] = v[j], v[j] = pivo; // Ultima troca
	return j;
}

void quickSort (int inicio, int fim, int * v)
{
	if (inicio < fim) 
	{
		int part = separa(inicio, fim, v);
		quickSort(inicio, part-1, v);
		quickSort(part+1, fim, v);
	}
}

int main(void)
{
	FILE *fP = fopen("input", "r");;
	int * vet = malloc(sizeof(int) * VETSIZ);
	double tempoGasto;
	FILE * fSort = fopen("sorted", "w+");
	int i;
	time_t inicio, fim;
	
	for(i=0;i<VETSIZ;i++) 
	    fscanf(fP, "%d", &vet[i]);

	inicio = clock();
	quickSort(0, VETSIZ-1, vet);
	fim = clock();	

	for(i=0; i<VETSIZ; i++)
		fprintf(fSort, "%d\n", vet[i]);
	
	tempoGasto = ((double)fim - inicio) / CLOCKS_PER_SEC * 1000;
	printf("Tempo gasto: %f ms.\n", tempoGasto);
	
	free(vet);
	fclose(fP);
	fclose(fSort);
	return 0;
}
