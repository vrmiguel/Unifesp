#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define VETSIZ 1000000

void insertion_sort (long int *vet, int n){
  int i, procura, chave;

  for (i = 1; i < n; i++){
    chave = vet[i];
    procura = i - 1;
    while (procura >= 0 && chave < vet[procura]){
      vet[procura + 1] = vet [procura];
      procura--;
    }
    vet[procura + 1] = chave;
  }
}

int main(void)
{
	FILE *fP = fopen("input", "r");;
	long int * vet = (long int *) malloc(sizeof(long int) * VETSIZ);
	double tempoGasto;
	FILE * fSort = fopen("sorted", "w+");
	int i;
	time_t inicio, fim;
	
	for(i=0;i<VETSIZ;i++)
	    fscanf(fP, "%ld", &vet[i]);

	inicio = clock();
	insertion_sort(vet, VETSIZ);
	fim = clock();	

	for(i=0; i<VETSIZ; i++)
		fprintf(fSort, "%ld\n", vet[i]);
	
	tempoGasto = ((double)fim - inicio) / CLOCKS_PER_SEC * 1000;
	printf("Tempo gasto: %f ms.\n", tempoGasto);
	
	free(vet);
	fclose(fP);
	fclose(fSort);
	return 0;
}
