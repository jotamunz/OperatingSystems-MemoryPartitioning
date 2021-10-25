#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "Initiator/Initiator.h"

int main(void){
   int shmid;
   int shmid2;
   int f1;
   struct ProcessArray* processArrayp;
   char * keyFile = "../Shared key/SharedKey";
   int arraySize = 10;
   while (1){
      printf("1) Crear memoria compartida.\n");
      printf("2) Inicializar puntero a memoria compartida\n");
      printf("3) Printear memoria compartida\n");
      printf("4) Escribir a memoria compartida\n");
      printf("5) Desadjuntar memoria\n");
      printf("6) Remover arreglo de memoria\n");
      printf("7) Remover arreglo de procesos\n");
      printf("8) Programa inicializador\n");
      printf("9) Cerrar el programa\n");
      printf("Ingrese su opción: ");
      if (scanf("%d", &f1) != 1)
         break;
      printf("\n");
      switch (f1){
         case 1:
            printf("Creando memoria\n\n");
            if((newSharedProcessArray(arraySize, keyFile)) > -1){
               printf("Memoria creada\n\n");       
            }
            break;
         case 2:
            printf("Inicializar memoria\n\n");
            shmid = getSharedProcessArrayId(keyFile);
            if(shmid > -1){
               printf("Id de memoria obtenido\n\n");
               processArrayp = attachSharedProcessArray(shmid);
               if(processArrayp != NULL){
                  printf("Memoria adjuntada\n\n");
               }         
            }
            break;
         case 3:
            printf("Printeando memoria\n\n");
            printProcessArray(processArrayp);
            break;
         case 4:
            printf("Escribir a memoria\n\n");
            int f2;
            int f3;
            printf("Que Id desea escribir en memoria: ");
            scanf("%d", &f2);
            printf("Con cuál algoritmo: ");
            scanf("%d", &f3);
            insertProcess(processArrayp, newLocalProcess(f2, f3));
            break;
         case 5: 
            printf("Desadjuntando memoria\n\n");
            if (detachSharedProcessArray(processArrayp) > -1){
                  printf("Memoria desadjuntada\n\n");
            }
            break;
         case 6: 
            printf("Removiendo arreglo de memoria\n\n");
            if (removeSharedMemoryArray(shmid2) > -1){
                  printf("Memoria removida\n\n");
            }
            break;
         case 7: 
            printf("Removiendo arreglo de procesos\n\n");
            if (removeSharedProcessArray(shmid) > -1){
                  printf("Memoria removida\n\n");
            }
            break;            
         case 8:
            initializerMenu(&shmid2, &shmid);
            break;  
         case 9:
            printf("Terminando programa\n\n");
            exit(0);
            break;  
         default:
            printf("Comando desconocido\n\n");
            break;
      }
   }
   return 0;
}
