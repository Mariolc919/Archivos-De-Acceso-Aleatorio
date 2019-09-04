/*Escribiremos datos en un archivo db*/
#include<stdio.h>
#include<string.h>
#define NUM_ELEMENTOS 5

struct direc{
  char nombre[30];
  char calle[40];
  char ciudad[20];
  char estado[20];
  char codigo[10];
}dinfo;

int main(){
  FILE *fd;
  struct direc registros[NUM_ELEMENTOS];
  int i = 0;

  while(i < NUM_ELEMENTOS){
    printf("%i. Nombre: ",i+1);
    fgets(registros[i].nombre,30,stdin);
    printf("    Calle: ");
    fgets(registros[i].calle,40,stdin);
    printf("    Ciudad: ");
    fgets(registros[i].ciudad,20,stdin);
    printf("    Estado: ");
    fgets(registros[i].estado,20,stdin);
    printf("    Codigo: ");
    fgets(registros[i].codigo,30,stdin);
    i++;
  }
  fd = fopen("listac", "w");

  if(fd){
    fwrite(registros, sizeof(struct direc),NUM_ELEMENTOS,fd);
  }



  return 0;
}
