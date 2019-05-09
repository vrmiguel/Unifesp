#include <stdio.h>
#include <stdlib.h>

int main (int argc, char ** argv)
{
  int i, j, n, aux, contTrocas=0;
  
  int * p; //ponteiro para vetor dinâmico

  scanf("%d", &n); //lê n, que indicará a quantidade de números a ser lida

  p = (int*) calloc (n, sizeof(int)); //Usa o calloc() para alocar um vetor dinâmicamente

  for(i=0; i<n; i++)
  {
    scanf("%i", (p+i)); //Lê cada elemento do vetor alocado dinâmicamente
  }

  for (i = 1; i < n; i++) {
        for (j = 0; j < n - 1; j++) {
            if (p[j] > p[j+1]) { //Realiza troca
                aux = p[j];
                p[j] = p[j+1];
                p[j+1] = aux;
                contTrocas++; //Registra que mais uma troca aconteceu
            }
        }
    }


  if(contTrocas % 2 == 0) //Verifica paridade
    printf("Carlos"); // Se o número de trocas for par, o segundo a jogar ganha
  else
    printf("Marcelo"); // Se o número de trocas for ímpar, o primeiro a jogar ganha

  free(p); //Libera a memória utilizada pelo vetor dinâmico
  return(0);
}
