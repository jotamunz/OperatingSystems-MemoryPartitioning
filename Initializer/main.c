#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "../Process_Generator/ProcessArray/ProcessArray.h"
#include "../Process_Generator/MemoryArray/MemoryArray.h"

int main(void){
   int f1;
   while (1){
      printf("1) Crear memoria compartida.\n");
      printf("2) Inicializar puntero a memoria compartida\n");
      printf("3) Printear memoria compartida\n");
      printf("4) Escribir a memoria compartida\n");
      printf("5) Remover memoria compartida\n");
      printf("6) Cerrar el programa\n");
      printf("Ingrese su opción: ");
      if (scanf("%d", &f1) != 1)
         break;
      printf("\n");
      switch (f1){
         case 1:
            printf("Crear memoria\n");
            break;
         case 2:
            printf("Inicializar memoria\n");
            break;
         case 3:
            printf("Printear memoria\n");
            break;
         case 4:
            printf("Escribir a memoria\n");
            break;
         case 5: 
            printf("Remover memoria\n");
            break;
         case 6:
            printf("Terminando programa\n");
            exit(0);
            break;  
         default:
            printf("Comando desconocido\n");
            break;
      }
   }
   return 0;
}
