#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define VETSIZ 1000000

void bucketSort(int * array, int n)
{   
 int i, j;   
 int * count;
 count = malloc(n * sizeof(int));
   
 for(i=0; i < n; i++)
 {   
  count[i] = 0;   
 }     
 for(i=0; i < n; i++)
 {    
  (count[array[i]])++; 
 }     
 for(i=0,j=0; i < n; i++)
 {   
  for(; count[i]>0;(count[i])--) 
  {       
   array[j++] = i; 
  }  
 }
 free(count);   
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
	bucketSort(vet, VETSIZ);
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

