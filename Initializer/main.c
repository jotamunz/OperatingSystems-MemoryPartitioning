#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "../Process_Generator/ProcessArray/ProcessArray.h"
#include "../Process_Generator/MemoryArray/MemoryArray.h"

int main(void){
   int shmid;
   int f1;
   struct MemoryArray* memoryArrayp;
   char * keyFile = "../Shared key/SharedKey";
   int arraySize = 10;
   while (1){
      printf("1) Crear memoria compartida.\n");
      printf("2) Inicializar puntero a memoria compartida\n");
      printf("3) Printear memoria compartida\n");
      printf("4) Escribir a memoria compartida\n");
      printf("5) Desadjuntar memoria\n");
      printf("6) Remover memoria compartida\n");
      printf("7) Cerrar el programa\n");
      printf("Ingrese su opción: ");
      if (scanf("%d", &f1) != 1)
         break;
      printf("\n");
      switch (f1){
         case 1:
            printf("Creando memoria\n\n");
            if((newSharedMemoryArray(arraySize, keyFile)) > -1){
               printf("Memoria creada\n\n");       
            }
            break;
         case 2:
            printf("Inicializar memoria\n\n");
            shmid = getSharedMemoryArrayId(keyFile);
            if(shmid > -1){
               printf("Id de memoria obtenido\n\n");
               memoryArrayp = attachSharedMemoryArray(shmid);
               if(memoryArrayp != NULL){
                  printf("Memoria adjuntada\n\n");
               }         
            }
            break;
         case 3:
            printf("Printeando memoria\n\n");
            printMemoryArray(memoryArrayp);
            break;
         case 4:
            printf("Escribir a memoria\n\n");
            int f2;
            int f3;
            int f4;
            printf("Que Id desea escribir en memoria: ");
            scanf("%d", &f2);
            printf("Durante cuantas celdas: ");
            scanf("%d", &f3);
            printf("Posición de inicio: ");
            scanf("%d", &f4);
            insertProcessIntoMemory(memoryArrayp, f2, f3, f4);
            break;
         case 5: 
            printf("Desadjuntando memoria\n\n");
            if (detachSharedMemoryArray(memoryArrayp) > -1){
                  printf("Memoria desadjuntada\n\n");
            }
            break;
         case 6: 
            printf("Removiendo memoria\n\n");
            if (removeSharedMemoryArray(shmid) > -1){
                  printf("Memoria removida\n\n");
            }
            break;
         case 7:
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
