#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "biblio.h"

int main(int argc, char* argv[]){
    int **sol, resultado = 0, alg, i = 0, j = 0, inicio_x = 0, inicio_y = 0;
    FILE* arq;
    Labirinto* entrada;
    TipoPilha* pilha;

    entrada = LeLabirinto(argv[1]);
    alg = atoi(argv[3]);

    inicio_x = entrada->x;
    inicio_y = entrada->y;

    sol = (int**)malloc(entrada->N * sizeof(int*));

    for(i = 0; i < entrada->N; i++)
        sol[i] = (int*)malloc(entrada->N * sizeof(int));

    for (i = 0; i < entrada->N; i++) {
        for(j = 0; j < entrada->N; j++)
            sol[i][j] = 0;
    }

    pilha = (TipoPilha*)malloc(sizeof(TipoPilha));
    PilhaVazia(pilha);

    switch (alg) {
        case 0:
            resultado = CaminhaLabirintoRecursivo(entrada, inicio_x, inicio_y, sol);
            break;

        case 1:
            resultado = CaminhaLabirintoIterativo(entrada, inicio_x, inicio_y, sol, pilha);
            break;

        default:
            printf("\n\t\t Algarismo invalido! \n\n");
            resultado = 0;
            break;
    }

    arq = fopen(argv[2], "wt");

    if (resultado == 1) {
        for (i = 0; i < entrada->N; i++) {
            for (j = 0; j < entrada->N; j++)
                fprintf(arq, "%d ", sol[i][j]);
            fprintf(arq, "\n");
        }
    }
    else
      printf("\t\nCaminho nao encontrado! Teseu provavelmente vai morrer.\n*** MINOTAURO WINS ***\n\n");

    fclose(arq);
    free(pilha->Topo);
    free(pilha);
    desalocaMatrizSaida(entrada, sol);
    desalocaLabirinto(entrada);

    return 0;
}
