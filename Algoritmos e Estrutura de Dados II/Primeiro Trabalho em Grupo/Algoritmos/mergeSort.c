#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define VETSIZ 1000000

void intercala(int p, int q, int r, long int * v)
{
	int i, j, k, *w;
	w = malloc((r-p) * sizeof(int));
	i = p;
	j = q;
	k = 0;
	while (i < q && j < r)
	{
		if(v[i] <= v[j])
			w[k++] = v[i++];
		else w[k++] = v[j++];
	}
	while (i < q)
		w[k++] = v[i++];
	while(j < r)
		w[k++] = v[j++];
	
	for(i = p; i < r; i++)
		v[i] = w[i-p];
	free(w);
}

void mergeSort(int p, int r, long int * v)
{
	if ( p < r-1 )
	{
		int q = (p+r)/2;
		mergeSort(p, q, v);
		mergeSort(q, r, v);
		intercala(p, q, r, v);
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
	mergeSort(0, VETSIZ, vet);
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
