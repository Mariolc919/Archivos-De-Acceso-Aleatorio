#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define NUM_ELEMENTOS 5

struct direc{
  char nombre[30];
  char calle[40];
  char ciudad[20];
  char estado[20];
  char codigo[10];
}dinfo;

void rapido_disco(FILE *fp, int cont);
void qs_disco(FILE *fp, int izq,int der);
void cambiar_campos(FILE *fp, int i, int d);
char *obtener_codigo(FILE *fp, int rec);

int main(){
  FILE *fp;

  if((fp = fopen("listac","r+")) == 0){
    printf("No se puede abrir el archivo para leer\escrbir");
    return -1;
  }

  rapido_disco(fp, NUM_ELEMENTOS);

  fclose(fp);

  printf("Lista Ordenada\n");
  return 0;
}

void rapido_disco(FILE *fp, int cont){/*Ordenacion rapida de ficheros de acceso aleatorio*/
  qs_disco(fp, 0, cont -1);
}

void qs_disco(FILE *fp, int izq, int der){/*quicksort para ficherps de acceso aleatorio*/

  int i,j;
  char x[100], *y, *obtener_codigo();

  i = izq; j = der;

  strcpy(x, obtener_codigo(fp, (i+j)/2));/*Obtener el codigo medio*/

  do {
    while(strcmp(obtener_codigo(fp,i),x) < 0 && i < der) i++;
    while(strcmp(obtener_codigo(fp,j),x) > 0 && j > izq) j--;

    if(i <= j){
      cambiar_campos(fp, i, j);
      i++;j--;
    }


  } while(i<=j);

  if(izq < j) qs_disco(fp, izq, j);
  if(i < der) qs_disco(fp, i, der);
}


void cambiar_campos(FILE *fp, int i, int j){
    char a[sizeof(dinfo)], b[sizeof(dinfo)];

    register int t;

    /*Primero lee los registros i y j*/
    fseek(fp, sizeof(dinfo) *i,0);
    for(t = 0; t < sizeof(dinfo);++t)
      a[t] = getc(fp);

    fseek(fp, sizeof(dinfo) * j, 0);
    for(t = 0; t < sizeof(dinfo);++t)
        b[t] = getc(fp);

    /*Despues los escribe en sentido contrario*/
    fseek(fp, sizeof(dinfo) * j,0);
    for(t = 0; t < sizeof(dinfo);++t)
      putc(a[t],fp);

    fseek(fp, sizeof(dinfo)*i,0);
    for(t = 0; t < sizeof(dinfo);++t)
        putc(b[t], fp);
}

char *obtener_codigo(FILE *fp, int rec){
  char *p;
  register int t;

  //p = &dinfo;

  fseek(fp, rec * sizeof(dinfo), 0);
  fread(&dinfo, sizeof(dinfo),1,fp);


  return dinfo.codigo;
}
