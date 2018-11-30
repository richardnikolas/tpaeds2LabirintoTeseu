#ifndef BIBLIO_H_INCLUDED
#define BIBLIO_H_INCLUDED

typedef struct TipoCelula *Apontador;

typedef struct {
    int N; // Dimensão do labirinto, lmebre-se que o mesmo é N x N
    int x; // Coordenada x da entrada
    int y; // Coordenada y da entrada
    int sx; // Coordenada x da espada
    int sy; // Coordenada y da espada
    unsigned char **mapa; // variável para armazenar o mapa (matriz)
} Labirinto;

typedef struct {
    int i; //Coordenada x do caminho a ser percorrido
    int j; //Coordenada y do caminho a ser percorrido
} TipoPosicao;

typedef struct TipoCelula {
    TipoPosicao ponto;
    Apontador prox;
} TipoCelula;

typedef struct {
    Apontador Topo, Fundo;
    int tamanho;
} TipoPilha;

Labirinto* LeLabirinto(const char*);
int CaminhaLabirintoRecursivo(Labirinto*, int, int, int**);
int CaminhaLabirintoIterativo(Labirinto*, int, int, int**, TipoPilha*);
void alocaLabirinto(Labirinto*);
void desalocaLabirinto(Labirinto*);
void desalocaMatrizSaida(Labirinto*, int**);
void PilhaVazia(TipoPilha*);
void Empilha(TipoPilha*, int, int);
void Desempilha(TipoPilha*, int**);
int Vazia(TipoPilha*);

#endif // BIBLIO_H_INCLUDED
