#include "funcoes.h"
#include <stdio.h>
#include <stdlib.h>

// Função para criar um novo nó da KD-Tree
no *criarNo(void *data, float latitude, float longitude) {
  no *novoNo = (no *)malloc(sizeof(no));
  novoNo->data = data;
  novoNo->pontoNo = (ponto *)malloc(sizeof(ponto));
  novoNo->pontoNo->latitude = latitude;
  novoNo->pontoNo->longitude = longitude;
  novoNo->esquerda = NULL;
  novoNo->direita = NULL;
  return novoNo;
}

// Função para inserir um nó na KD-Tree
no *inserirNo(no *raiz, void *data, float latitude, float longitude,
              int profundidade) {
  if (raiz == NULL) {
    return criarNo(data, latitude, longitude);
  }

  int dimensaoAtual =
      profundidade %
      2; // Alternando entre latitude (0) e longitude (1) para pontos 2D
  ponto *pontoAtual = raiz->pontoNo;

  if (dimensaoAtual == 0) {
    if (latitude < pontoAtual->latitude) {
      raiz->esquerda = inserirNo(raiz->esquerda, data, latitude, longitude,
                                 profundidade + 1);
    } else {
      raiz->direita =
          inserirNo(raiz->direita, data, latitude, longitude, profundidade + 1);
    }
  } else {
    if (longitude < pontoAtual->longitude) {
      raiz->esquerda = inserirNo(raiz->esquerda, data, latitude, longitude,
                                 profundidade + 1);
    } else {
      raiz->direita =
          inserirNo(raiz->direita, data, latitude, longitude, profundidade + 1);
    }
  }

  return raiz;
}

// Função para encontrar o sucessor e o predecessor mais próximos na KD-Tree
void encontrarSucessorEPredecessor(no *raiz, float latitude, float longitude,
                                   no **successor, no **predecessor,
                                   int profundidade) {
  if (raiz == NULL) {
    return;
  }

  ponto *pontoAtual = raiz->pontoNo;

  // Atualiza o sucessor e o predecessor com base no nó atual
  if (pontoAtual->latitude <= latitude && pontoAtual->longitude <= longitude) {
    *predecessor = raiz;
    encontrarSucessorEPredecessor(raiz->direita, latitude, longitude, successor,
                                  predecessor, profundidade + 1);
  } else if (pontoAtual->latitude >= latitude &&
             pontoAtual->longitude >= longitude) {
    *successor = raiz;
    encontrarSucessorEPredecessor(raiz->esquerda, latitude, longitude,
                                  successor, predecessor, profundidade + 1);
  }

  // Verifica se a busca deve continuar para a esquerda ou direita da árvore
  int dimensaoAtual =
      profundidade %
      2; // Alternando entre latitude (0) e longitude (1) para pontos 2D
  if (dimensaoAtual == 0) {
    if (latitude < pontoAtual->latitude) {
      encontrarSucessorEPredecessor(raiz->esquerda, latitude, longitude,
                                    successor, predecessor, profundidade + 1);
    } else {
      encontrarSucessorEPredecessor(raiz->direita, latitude, longitude,
                                    successor, predecessor, profundidade + 1);
    }
  } else {
    if (longitude < pontoAtual->longitude) {
      encontrarSucessorEPredecessor(raiz->esquerda, latitude, longitude,
                                    successor, predecessor, profundidade + 1);
    } else {
      encontrarSucessorEPredecessor(raiz->direita, latitude, longitude,
                                    successor, predecessor, profundidade + 1);
    }
  }
}

// Função para liberar a memória ocupada pela KD-Tree
void freeTree(no *raiz) {
  if (raiz == NULL) {
    return;
  }
  freeTree(raiz->esquerda);
  freeTree(raiz->direita);
  free(raiz->pontoNo);
  free(raiz);
}

int main() {
  // Exemplo de uso da KD-Tree com nós 2D

  struct municipio municipios[10] = {
      {1, "Sao Paulo", 2.5, 3.8, "Sim", 35, "SP", 7107, "Sudeste", 11, "GMT-3"},
      {2, "Rio de Janeiro", 1.2, 4.6, "Sim", 33, "RJ", 6001, "Sudeste", 21,
       "GMT-3"},
      {3, "Belo Horizonte", 5.1, 2.9, "Sim", 31, "MG", 4123, "Sudeste", 31,
       "GMT-3"},
      {4, "Salvador", 3.7, 1.5, "Sim", 29, "BA", 3849, "Nordeste", 71, "GMT-3"},
      {5, "Fortaleza", 4.0, 3.2, "Sim", 23, "CE", 1389, "Nordeste", 85,
       "GMT-3"},
      {6, "Recife", 4.7, 3.9, "Sim", 26, "PE", 2491, "Nordeste", 81, "GMT-3"},
      {7, "Manaus", 2.2, 4.9, "Sim", 13, "AM", 1306, "Norte", 92, "GMT-4"},
      {8, "Porto Alegre", 5.5, 3.5, "Sim", 43, "RS", 8801, "Sul", 51, "GMT-3"},
      {9, "Curitiba", 3.2, 4.5, "Sim", 41, "PR", 4120, "Sul", 41, "GMT-3"},
      {10, "Brasilia", 2.9, 3.1, "Sim", 53, "DF", 9705, "Centro-Oeste", 61,
       "GMT-3"}};

  struct fastFood fastfoods[10] = {{1, "FastFood 1", 10, "UF 1", 'N', -23.5505,
                                    -46.6333, "Região 1", 100, 11, "Fuso 1"},
                                   {2, "FastFood 2", 20, "UF 2", 'S', -22.9068,
                                    -43.1729, "Região 2", 200, 21, "Fuso 2"},
                                   {3, "FastFood 3", 30, "UF 3", 'N', -27.5969,
                                    -48.5495, "Região 3", 300, 31, "Fuso 3"},
                                   {4, "FastFood 4", 40, "UF 4", 'N', -15.7801,
                                    -47.9292, "Região 4", 400, 41, "Fuso 4"},
                                   {5, "FastFood 5", 50, "UF 5", 'N', -23.5505,
                                    -46.6333, "Região 5", 500, 51, "Fuso 5"},
                                   {6, "FastFood 6", 60, "UF 6", 'S', -22.9068,
                                    -43.1729, "Região 6", 600, 61, "Fuso 6"},
                                   {7, "FastFood 7", 70, "UF 7", 'N', -27.5969,
                                    -48.5495, "Região 7", 700, 71, "Fuso 7"},
                                   {8, "FastFood 8", 80, "UF 8", 'N', -15.7801,
                                    -47.9292, "Região 8", 800, 81, "Fuso 8"},
                                   {9, "FastFood 9", 90, "UF 9", 'N', -23.5505,
                                    -46.6333, "Região 9", 900, 91, "Fuso 9"},
                                   {10, "FastFood 10", 100, "UF 10", 'S',
                                    -22.9068, -43.1729, "Região 10", 1000, 101,
                                    "Fuso 10"}};

  no *raiz = NULL;
  for (int i = 0; i < 10; i++) {
    raiz = inserirNo(raiz, &municipios[i], municipios[i].latitude,
                     municipios[i].longitude, 0);
  }

  float latitude = 1.2;
  float longitude = 4.6;

  no *successor = NULL;
  no *predecessor = NULL;
  encontrarSucessorEPredecessor(raiz, latitude, longitude, &successor,
                                &predecessor, 0);

  if (successor) {
    struct municipio *sucMunicipio = (struct municipio *)successor->data;
    printf("Sucessor mais próximo: %s\n", sucMunicipio->nomeMunicipio);
  }

  if (predecessor) {
    struct municipio *predMunicipio = (struct municipio *)predecessor->data;
    printf("Predecessor mais próximo: %s\n", predMunicipio->nomeMunicipio);
  }

  for (int i = 0; i < 10; i++) {
    raiz = inserirNo(raiz, &fastfoods[i], fastfoods[i].latitude,
                     fastfoods[i].longitude, 0);
  }

  float latitude02 = -23.5505;
  float longitude02 = -46.6333;

  no *successor02 = NULL;
  no *predecessor02 = NULL;

  encontrarSucessorEPredecessor(raiz, latitude02, longitude02, &successor02,
                                &predecessor02, 0);

  if (successor02) {
    struct fastFood *sucFastFood = (struct fastFood *)successor02->data;
    printf("Sucessor mais próximo: %s\n", sucFastFood->city);
  }

  if (predecessor02) {
    struct fastFood *predFastFood = (struct fastFood *)predecessor02->data;
    printf("Predecessor mais próximo: %s\n", predFastFood->city);
  }

  freeTree(raiz);

  return 0;
}
