#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define N_THREADS 4

int respond;
int request;
int sum;

void *ClientProcess(void *p){
    //non-critical section
    int i = *((int *) p);
    while(1){
        
        while(respond != i){
            request = i;
        }
        printf("Thread %d entrando na seção crítica...\n",i);
        int local = sum;
        sleep(rand()%2);
        sum = local + 1;
        printf("Thread %d saindo da seção crítica...\n",i);
        respond = 0;
    }
}

void *ServerProcess(void *p)
{
    while(1){
        while(request == 0);
        respond = request;
        while(respond != 0);
        request = 0;
    }
}

int main(){
    pthread_t threads[N_THREADS];
    int clientsId[N_THREADS];
    pthread_t server;
    pthread_create(&server,NULL,ServerProcess,NULL);
    respond = 0, request = 0;
    
    //create the clients
    for(int i = 0;i<N_THREADS;i++){
        clientsId[i] = i+1;
        pthread_create(&threads[i],NULL,ClientProcess,(void*)&clientsId[i]);
    }

    pthread_join(server,NULL);
    return 0;
}