# TP AEDS II - Labirinto Espada Mágica

<h2> Background </h2>
<p>O jovem Teseu, um bravo guerreiro ateniense, decidiu enfrentar o Minotauro da Ilha de Creta. Para que ele tenha alguma chance de derrotar o Minotouro, ele necessita encontrar uma espada mágica dentro do Labirinto de forma rápida e sem se perder. Para que consiga completar essa difícil e perigosa tarefa com sucesso ele precisa de sua ajuda. Teseu, sabendo de suas incríveis habilidades como programador, precisa que você escreva um programa que, dado o mapa do labirinto e a localização da espada dentro do mesmo, retorne o caminho até ela, se possível.</p>

<h2> O problema </h2>
<p>O labirinto é dado por uma matriz binária N * N onde a entrada e a localização da espada são dados pelas variáveis <i>E</i> e <i>S</i> respectivamente, onde <i>E</i> e <i>S</i> são pares ordenados do formato (x,y). Teseu inicia sua caminhada da entrada <i>E</i> até local <i>S</i> onde a espada se encontra, e com um fio de linha ele vai marcando o caminho para não se perder. Teseu pode mover-se apenas em quatro direções: direita, esquerda, cima e baixo (Note que não há movimento em diagonal). No mapa do labirinto, 1 significa que há uma parede naquela coordenada e 0 significa que há passagem. Dado esse mapa, seu algoritmo deve retornar uma outra matriz binária com as mesmas dimensões do labirinto onde os valores 1 representam o caminho encontrado até a espada.</p>

<h2> Entrada </h2>

<p>A entrada do problema deve ser lida de um arquivo texto com o seguinte formato: <br/>
  
```
N x y sx sy
L(0,0) L(0,2) L(0,3) ... L(0,N-1)
L(1,0) L(1,2) L(0,3) ... L(1,N-1)
...
L(N-1,0) L(N-1,2) L(N-1,3) ... L(N-1, N-1) <br/>
```

<p>Onde N é dimensão do labirinto, x e y são as coordenadas da entrada do labirinto, sx e sy são as coordenadas da espada. As entradas L(i,j) indicam o valor da casa na linha i e coluna j do labirinto. <br/>
Segue um exemplo de arquivo de entrada com dados reais:<br/></p>

```
6 1 0 4 4
1 1 1 1 1 1
0 0 1 1 1 1
1 0 0 1 0 1
1 1 0 1 1 1
1 0 0 0 0 1
1 1 1 1 1 1
```

<h3><b>TODAS AS FIGURAS SE ENCONTRARÃO NA PASTA "IMAGENS"</b><br/></h3>
<p>Note que nesse problema o mapa do labirinto é modelado como um tabuleiro para uma maior abstração do problema. A Figura 1 mostra mais claramente como seria essa abstração. As casas cinzas (valor 1) são as paredes e as brancas (valor 0) são as passagens.</p>

<h2> Saída </h2>
<p>Seu programa deve escrever a solução em um arquivo do seguinte modo:</p>

```
0 0 0 0 0 0
1 1 0 0 0 0
0 1 1 0 0 0
0 0 1 0 0 0
0 0 1 1 1 0
0 0 0 0 0 0
```

<p>Os elementos com valor 1 representam onde Teseu deve passar para que ele chegue até a espada. A Figura 2 ilustra a solução encontrada. Além disso, caso não haja um caminho válido até a espada o programa deve gravar no arquivo de saída um único valor 0.<br/>
É importante observar que para algumas entradas existe mais de uma solução possível. Você não precisa se preocupar em escolher algum caminho específico, desde que sua solução apresentada na saída seja correta (leve Teseu até a espada e sem transpassar paredes).</p>

<h3> Algoritmo </h3>

<p> Para realizar o algoritmo é necessário o mapa do labirinto, a coordenada (x,y) da entrada e a coordenada (sx, sy) do local da espada. Começando pela entrada (x, y), o algoritmo deverá marcar a casa atual com valor 1 e visitar as casas vizinhas. O algoritmo visita a casa da direita e verifica, recursivamente, se esse vizinho leva a uma solução válida. Caso não leve, ele verifica o próximo vizinho até que reste mais nunhum. Se nenhuma das soluções anteriores levarem a um caminho válido o algoritmo retorna falso. <br/>
Abaixo o pseudo-código do algoritmo recursivo para encontrar a espada no labirinto. Você poderá basear sua implementação neste exemplo. </p>

```c
function caminhalabirinto(mapa; x; y; sx; sy; sol)
  if x = sx && y = sy then
    sol[x][y]   1
    return True
  else
    if mapa[x][y] = 0 && sol[x][y] = 0 then
      sol[x][y]   1
      if caminhalabirinto(mapa; x + 1; y; sx; sy; sol) = True then
        return True
      end if
      if caminhalabirinto(mapa; x; y + 1; sx; sy; sol) = True then
        return True
      end if
      if caminhalabirinto(mapa; x 􀀀 1; y; sx; sy; sol) = True then
        return True
      end if
      if caminhalabirinto(mapa; x; y 􀀀 1; sx; sy; sol) = True then
        return True
      end if
      sol[x][y]   0
    end if
  end if
  return True
end function
```

<h3> Estrutura de Dados </h3>

<p> A estrutura de dados a seguir deve ser utilizada para armazenar o mapa do labirinto após a leitura do arquivo. </p> 

```c
typedef struct {
  int N;    // Dimensão do labirinto, lmebre-se que o mesmo é N x N
  int x;    // Coordenada x da entrada
  int y;    // Coordenada y da entrada
  int sx;   // Coordenada x da espada
  int sy;   // Coordenada y da espada
  unsigned char **mapa; // variável para armazenar o mapa (matriz)
} Labirinto;
```

<h2> O que deve ser feito </h2>

<p> 1. Elaborar um programa capaz de ler um arquivo texto com a representação do labirinto e imprimir no arquivo a solução com o trajeto até a espada. <br/>
  
 ```
 ./exec labirinto.txt caminho_espada.txt alg <br/>
```

onde <i>exec</i> é o nome do executável, labirinto.txt contém o mapa do labirinto com as posições de Teseu e da espada, caminho_espada.txt receberá a saída do algoritmo contendo o caminho encontrado até a espada e alg é um inteiro indicando se o algoritmo será recursivo (valor 0) ou, então, iterativo (valor 1).</p>


