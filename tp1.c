#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "biblio.h"

/*−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−
Prototipo : Labirinto* LeLabirinto(const char*);
Funcao : Recebe o argumento "argv[1]" que contem o labirinto problema e lê
         e aloca todos os dados contidos neste;
Entrada : Recebe um "const char*" que, no caso, é um .txt;
Saida : A saída é um tipo Labirinto* pronto pra uso das outras funções
−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−*/

Labirinto* LeLabirinto(const char* entrada) {
    int i = 0, j = 0;
    char* aux;
    FILE* arq;
    Labirinto* lab_aux;

    arq = fopen(entrada, "rt");
    if(arq == NULL){
        printf("\n\t Erro ao abrir arquivo!\n");
        return NULL;
    }

    lab_aux = (Labirinto *)malloc(sizeof(Labirinto));
    aux = (char*)malloc(1000*sizeof(char));
    fscanf(arq, "%d %d %d %d %d", &(lab_aux->N), &(lab_aux->x), &(lab_aux->y), &(lab_aux->sx), &(lab_aux->sy));

    alocaLabirinto(lab_aux);
    for(i = 0; i < lab_aux->N; i++){
        for(j = 0; j < lab_aux->N; j++){
            fscanf(arq, "%s", aux);
            lab_aux->mapa[i][j] = (char)atoi(aux);
        }
    }

    fclose(arq);
    free(aux);

    return lab_aux;
}

/*−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−
Prototipo : int CaminhaLabirintoRecursivo(Labirinto*, int, int, int**);
Funcao : Calcula/Encontra o caminho que Teseu deverá seguir para encontrar a
         espada mágica de modo Recursivo;
Entrada : Recebe uma estruturado tipo Labirinto*, dois inteiros (x e y)
          e a matriz de saída (int**);
Saida : Retorna um numero inteiro, 1 ou 0.
        "1" se o caminho até a espada foi encontrado e "0" se não foi;
−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−*/

int CaminhaLabirintoRecursivo(Labirinto* lab, int x, int y, int** sol) {

    if (x == lab->sx && y == lab->sy){
        sol[x][y] = 1;
        return 1;
    }
    else {
        if(lab->mapa[x][y] == 0 && sol[x][y] == 0){
            sol[x][y] = 1;

            if((CaminhaLabirintoRecursivo(lab, x + 1, y, sol) == 1))
                return 1;

            if((CaminhaLabirintoRecursivo(lab, x, y + 1, sol) == 1))
                return 1;

            if((CaminhaLabirintoRecursivo(lab, x - 1, y, sol) == 1))
                return 1;

            if((CaminhaLabirintoRecursivo(lab, x, y - 1, sol) == 1))
                return 1;

            sol[x][y] = 0;
        }
    }

    return 0;
}

/*−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−
Prototipo : int CaminhaLabirintoIterativo(Labirinto*, int, int, int**, TipoPilha*)
Funcao : Calcula/Encontra o caminho que Teseu deverá seguir para encontrar a
         espada mágica de modo Iterativo;
Entrada : Recebe uma estruturado tipo Labirinto*, dois inteiros (x e y),
          a matriz de saída (int**) e um TipoPilha*;
Saida : Retorna um numero inteiro, 1 ou 0.
        "1" se o caminho até a espada foi encontrado e "0" se não foi;
−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−*/

int CaminhaLabirintoIterativo(Labirinto* lab, int x, int y, int** sol, TipoPilha* pilha) {
    int i = 0, j = 0, k = 0;

    i = x;
    j = y;

    while((i != lab->sx) || (j != lab->sy)) {

        sol[i][j] = 1;

        if(i == 0 && j == 0){   // (0,0)
            if(lab->mapa[i+1][j] == 0){
                Empilha(pilha, i, j);
                i++;
            }
            else if(lab->mapa[i][j+1] == 0){
                Empilha(pilha, i, j);
                j++;
            }
        }

        else if(i == 0){ //Borda superior
            if(lab->mapa[i+1][j] == 0){
                Empilha(pilha, i, j);
                i++;
            }
            else if(lab->mapa[i][j+1] == 0){
                Empilha(pilha, i, j);
                j++;
            }
            else if(lab->mapa[i][j-1] == 0){
                Empilha(pilha, i, j);
                j--;
            }
        }

        else if(j == 0){ //Borda esquerda
            if(lab->mapa[i+1][j] == 0){
                Empilha(pilha, i, j);
                i++;
            }
            else if(lab->mapa[i][j+1] == 0){
                Empilha(pilha, i, j);
                j++;
            }
            else if(lab->mapa[i-1][j] == 0){
                Empilha(pilha, i, j);
                i--;
            }
        }

        else if(i == lab->N-1 && j == lab->N-1){ //(N-1, N-1)
            if(lab->mapa[i-1][j] == 0){
                Empilha(pilha, i, j);
                i--;
            }
            else if(lab->mapa[i][j-1] == 0){
                Empilha(pilha, i, j);
                j--;
            }
        }

        else if(i == lab->N-1){     //Borda inferior
            if(lab->mapa[i][j+1] == 0){
                Empilha(pilha, i, j);
                j++;
            }
            else if(lab->mapa[i-1][j] == 0){
                Empilha(pilha, i, j);
                i--;
            }
            else if(lab->mapa[i][j-1] == 0){
                Empilha(pilha, i, j);
                j--;
            }
        }

        else if(j == lab->N-1){     //Borda direita
            if(lab->mapa[i+1][j] == 0){
                Empilha(pilha, i, j);
                i++;
            }
            else if(lab->mapa[i-1][j] == 0){
                Empilha(pilha, i, j);
                i--;
            }
            else if(lab->mapa[i][j-1] == 0){
                Empilha(pilha, i, j);
                j--;
            }
        }

        else{   // "Meio" da matriz
            if(lab->mapa[i+1][j] == 0){
                Empilha(pilha, i, j);
                i++;
            }
            else if(lab->mapa[i][j+1] == 0){
                Empilha(pilha, i, j);
                j++;
            }
            else if(lab->mapa[i-1][j] == 0){
                Empilha(pilha, i, j);
                i--;
            }
            else if(lab->mapa[i][j-1] == 0){
                Empilha(pilha, i, j);
                j--;
            }
      }
    }

    if(i == lab->sx && j == lab->sy){
      Empilha(pilha, i, j);
      k = pilha->tamanho;
      while(k > 0){
          Desempilha(pilha, sol);
          k--;
      }
      return 1;
    }
    else {
      printf("0\n");
      return 0;
    }
}

/*−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−
Prototipo : void alocaLabirinto(Labirinto*);
Funcao : Alocar memória para uma estrutura do tipo Labirinto*;
Entrada : Uma estrutura do tipo Labirinto*;
Saida : Nao tem saida, aloca o que é necessario e finaliza;
−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−*/

void alocaLabirinto(Labirinto* lab) {
    int i;
    lab->mapa = (unsigned char**)malloc(lab->N * sizeof(unsigned char*));
    for(i = 0; i < lab->N; i++)
        lab->mapa[i] = (unsigned char*)malloc(lab->N * sizeof(unsigned char));
}

/*−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−
Prototipo : void desalocaLabirinto(Labirinto*);
Funcao : Desalocar a memoria alocada em uma estrutura do tipo Labirinto*;
Entrada : Uma estrutura do tipo Labirinto*;
Saida : Nao tem saida, desaloca tudo que está alocado no Labirinto* e finaliza;
−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−*/

void desalocaLabirinto(Labirinto* lab) {
    int i = 0;
    for(i = 0; i < lab->N; i++)
        free(lab->mapa[i]);
    free(lab->mapa);
    free(lab);
}

/*−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−
Prototipo : void PilhaVazia(TipoPilha*);
Funcao : Criar uma pilha vazia, alocando os espaços necessarios e setando o
         tamanho para zero;
Entrada : Uma estrutura do TipoPilha*;
Saida : Não tem saída, aloca tudo que é necessario para uma pilha e finaliza;
−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−*/

void PilhaVazia(TipoPilha* pilha) {
    pilha->Topo = (Apontador)malloc(sizeof(TipoCelula));
    pilha->Fundo = pilha->Topo;
    pilha->Topo->prox = NULL;
    pilha->tamanho = 0;
}

/*−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−
Prototipo : void Empilha(TipoPilha*, int, int);
Funcao : Coloca as coordenadas recebidas em um TipoCelula* que ficará no topo
         da pilha, muda a posição do "Topo" e aumenta o contador de tamanho
         da pilha;
Entrada : Recebe uma estrutura do TipoPilha* e dois inteiros (coordenadas);
Saida : Não tem saída, empilha o que tiver de ser empilhado e finaliza;
−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−*/

void Empilha(TipoPilha* pilha, int x, int y) {
    Apontador Aux;
    Aux = (Apontador)malloc(sizeof(TipoCelula));

    Aux->ponto.i = x;
    Aux->ponto.j = y;
    Aux->prox = pilha->Topo;
    pilha->Topo = Aux;
    pilha->tamanho++;
}

/*−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−
Prototipo : void Desempilha(TipoPilha*, int**);
Funcao : Pega os valores que estão no topo da pilha, coloca as coordenadas
         na matriz de saída, desempilha (desaloca) o antigo topo e diminui
         o contador de tamanho da pilha;
Entrada : Recebe uma estrutura TipoPilha* e a matriz de saída (int**);
Saida : Não tem saída, desempilha a pilha em questão e finaliza;
−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−*/

void Desempilha(TipoPilha* pilha, int** sol) {
    int x, y;
    Apontador auxiliar;

    auxiliar = pilha->Topo;
    x = pilha->Topo->ponto.i;
    y = pilha->Topo->ponto.j;
    sol[x][y] = 1;
    pilha->Topo = auxiliar->prox;
    free(auxiliar);
    pilha->tamanho--;
}

/*−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−
Prototipo : void desalocaMatrizSaida(Labirinto*, int**);
Funcao : Desalocar o espaço alocado para a matriz de saída (int**);
Entrada : Uma estrutura tipo Labirinto* e a matriz de saída em questão (int**);
Saida : Não tem saída. Desaloca a matriz e finaliza;
−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−*/

void desalocaMatrizSaida(Labirinto* lab, int** sol) {
    int i = 0;

    for(i = 0; i < lab->N; i++)
        free(sol[i]);
    free(sol);
}

/*−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−
Prototipo : int Vazia(TipoPilha*);
Funcao : Verificar se a pilha esta vazia ou nao;
Entrada : Uma estrutura TipoPilha*;
Saida : Um número inteiro. 1 se a pilha estiver vazia, 0 se não estiver;
−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−*/

int Vazia(TipoPilha* pilha) {
    if(pilha->tamanho == 0)
        return 1;
    else
        return 0;
}
