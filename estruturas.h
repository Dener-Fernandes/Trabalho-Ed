struct municipio {
  int codigoIBGE;
  char nomeMunicipio[50];
  float latitude;
  float longitude;
  char capital[20];
  int codigoUF;
  char UF[3];
  int codigoSiafi;
  char regiao[20];
  int DDD;
  char fusoHorario[10];
};

struct fastFood {
  char address[100];
  char categories[100];
  char city[50];
  char country[50];
  float latitude;
  float longitude;
  char name[100];
  char postalCode[20];
  char province[50];
  char websites[100];
} fastFood;

typedef struct ponto {
  float latitude;
  float longitude;
} ponto;

typedef struct no {
  void *data;
  ponto *pontoNo;
  struct no *esquerda;
  struct no *direita;
} no;
