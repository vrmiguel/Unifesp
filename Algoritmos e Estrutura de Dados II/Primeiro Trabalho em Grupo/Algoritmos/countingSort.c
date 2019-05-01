#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define VETSIZ 1000000

void countingSort(int *vet, int n, int min, int max)
{
  int i, j, z;
 
  int alcance = max - min + 1;
  int *contagem = malloc(VETSIZ * sizeof(int));
 
  for(i = 0; i < alcance; i++)
    contagem[i] = 0;
  
  for(i = 0; i < n; i++)
    contagem[vet[i] - min]++;
  
  for(i = min, z = 0; i <= max; i++) 
    for(j = 0; j < contagem[i - min]; j++) 
    {
      vet[z] = i;
      z++;
    } 
 
  free(contagem);
}

int main(void)
{
	FILE *fP = fopen("input", "r");;
	int * vet = (int *) malloc(sizeof(int) * VETSIZ);
	double tempoGasto;
	FILE * fSort = fopen("sorted", "w+");
	int i;
	time_t inicio, fim;
	
	for(i=0;i<VETSIZ;i++)
	    fscanf(fP, "%d", &vet[i]);

	inicio = clock();
	countingSort(vet, VETSIZ, 343, 499999);
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
