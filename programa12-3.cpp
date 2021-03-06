/* Este programa muestra la sincronizaciòn en la impresion de dos hilos */

#include <pthread.h>
#include <stdio.h>
#include <semaphore.h>
#include <stdlib.h>

int i = 10; /* Variable compartida */
sem_t mutex1;
sem_t mutex2;
sem_t mutex3;

void* Hilo1(void *);
void* Hilo2(void *);
void* Hilo3(void *);

int main(void){
   pthread_t th1, th2 ,thextra;
   
   // Inicializa los semaforos
   /*sem_init(&mutex1, 0, 1);
   sem_init(&mutex2, 0, 0);
   sem_init(&mutex3, 0, 2);*/
	
   sem_init(&mutex1, 0, 1);
   sem_init(&mutex2, 0, 0);
   sem_init(&mutex3, 0, 0);
   
   
   // Crea hilos
   pthread_create(&th1, NULL, &Hilo1, NULL);
   pthread_create(&th2, NULL, &Hilo2, NULL);
   pthread_create(&thextra, NULL, &Hilo3, NULL);
   
   // Esperar a que los hilos terminen
   pthread_join(th1, NULL);
   pthread_join(th2, NULL);
   pthread_join(thextra, NULL);

   exit(0);
}

void* Hilo1(void *)
{
   
   while(i > 0) {
      sem_wait(&mutex1);
      printf("Soy el hIlo 1 (%d) y esta es la impresion %d \n", (int) pthread_self(), i--);
      sem_post(&mutex2);
   }
   pthread_exit(0);
}

void* Hilo2(void *)
{
   
   while(i > 0) {
      sem_wait(&mutex2);
      printf("Soy el hIlo 2 (%d) y esta es la impresion %d \n", (int) pthread_self(), i--);
      //sem_post(&mutex1);
      sem_post(&mutex3);
   }
   pthread_exit(0);
}
void* Hilo3(void *)
{
	
   while(i > 0) {
      sem_wait(&mutex3);
	 if(i<0){		
 		  break;}
      printf("Soy el hIlo extra (%d) y esta es la impresion %d \n", (int) pthread_self(), i--);
      sem_post(&mutex1);
   }
   pthread_exit(0);
}

