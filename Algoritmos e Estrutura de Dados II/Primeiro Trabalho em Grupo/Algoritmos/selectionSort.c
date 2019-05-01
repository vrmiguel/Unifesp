#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define troca(x,y) {x = x+y; y = x - y; x = x-y; }
#define VETSIZ 100000

void selectionSort(long int * p, int n)
{
    int aux;
    for(int i=0; i<n; i++)
        for(int j=i+1; j<n; j++)
            // Compara v[i] como todos os valores a sua direita, trocando-os quando maior.
            if (p[i] > p[j])
		     troca(p[i], p[j]);
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
	selectionSort(vet, VETSIZ);
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
