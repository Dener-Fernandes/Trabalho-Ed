#include "estruturas.h"

no *criarNo(void *data, float latitude, float longitude);

no *inserirNo(no *raiz, void *data, float latitude, float longitude,
              int profundidade);

void encontrarSucessorEPredecessor(no *raiz, float latitude, float longitude,
                                   no **successor, no **predecessor,
                                   int profundidade);
void freeTree(no *raiz);
