#include <stdio.h>
#include <stdlib.h>

    /* RENDIMENTOS -
        O programa arruma casos de empates primeiro (empate -> vitória), pois um caso de empate nos dá sempre um
        rendimento de 3 pontos por gol comprado, enquanto que um caso de derrota nos dá no máximo um rendimento de 1.5 pontos por gol comprado.
        Como uma terceira alternativa, pode-se transformar uma derrota em empate, nos dando um rendimento de um ponto por gol, no máximo.
    */

void shellSort(int *vet, int tam) 
{
    int i , j , valor;
    int vaun = 1;
    while(vaun < tam) {
        vaun = 3*vaun+1;
    }
    while ( vaun > 1) 
    {
        vaun /= 3;
        for(i = vaun; i < tam; i++) 
        {
            valor = vet[i];
            j = i;
            while (j >= vaun && valor < vet[j - vaun])
            {
                vet[j] = vet [j - vaun];
                j = j - vaun;
            }
            vet [j] = valor;
        }
   }
}

int main()
{
    int numJogos, numGolsCompraveis, i, s, r, pontuacao = 0, k=0;
    scanf("%d", &numJogos); // Lê quantidade de partidas
    
    int * saldoGols = malloc(numJogos*sizeof(int)); // aloca espaço para o tamanho de partidas dado

    if (numGolsCompraveis > 100000 && numGolsCompraveis < 0) // se extrapolar as restrições, pare a execução
        return 0;

    scanf("%d", &numGolsCompraveis); // lê quantidade de gols que o time pode comprar

    if (numGolsCompraveis > 1000000 && numGolsCompraveis < 0) // se extrapolar as restrições, pare a execução
        return 0;
    
    for(i=0;i<numJogos;i++)
    {
        scanf("%d %d", &s, &r); // leia s e r
        if (s > r) // Em caso de vitória
        {
            pontuacao = pontuacao + 3; // Vitórias dão 3 pontos 
            continue; // Pule para próximo loop para evitar os ifs abaixo
        }
        else if (s == r) // Em caso de empate
        {
            if(numGolsCompraveis > 0){ 
                numGolsCompraveis--; // Usa um gol para transformar o empate em vitória, nos dando 3 pontos 
                pontuacao = pontuacao + 3;
                continue; // Pula para próximo loop
            }
            else
            {
                pontuacao++; // Caso não hajam mais gols para serem usados, soma-se só o ponto dado por empate
                continue;
            }
        }
        else
        {
            saldoGols[k] = r-s; // Salva o módulo entre s e r
            k++; //Soma número de derrotas
        }    
    }
    saldoGols = realloc(saldoGols, k*sizeof(int)); // Reduz (na grande maioria das vezes) o espaço alocado para saldoGols
    shellSort(saldoGols, k); // Ordena o vetor com shellSort
    for(i = 0; i<k; i++)
    {
            // Quando empates são as únicas possibilidades
        if(numGolsCompraveis - saldoGols[i] == 0 && numGolsCompraveis != 0)
        {
            numGolsCompraveis = numGolsCompraveis - saldoGols[i];
            pontuacao++;
            continue;
        }
            // Se é possível transformar derrotas em vitórias
        else if(numGolsCompraveis - saldoGols[i] > 0 && numGolsCompraveis != 0)
        {
            numGolsCompraveis = numGolsCompraveis - saldoGols[i] -1;
            pontuacao = pontuacao + 3; 
        }
    }
    printf("%d", pontuacao); // Mostra resposta
    free(saldoGols); // Libera memória alocada
    return 0;
}
