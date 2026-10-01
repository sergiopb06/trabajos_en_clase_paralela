#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define NUM_PHILS 11 //number of Philosophers
#define TIMES_TO_EAT 5 //number of times a Philosopher has to eat 

void *philosopher(void *num);
void think(int phil);
void eat(int phil);


sem_t room;  
sem_t chopstick[NUM_PHILS];  // Shared resources



int main(void){

    sem_init(&room,0,NUM_PHILS -1);   // NUM_PHILS -1 max number of phil at the table at the same time

    for(int i = 0; i < NUM_PHILS; i++){
        sem_init(&chopstick[i], 0, 1);
    }

    int ids[NUM_PHILS];
    pthread_t threads[NUM_PHILS]; 

    for(int i = 0; i < NUM_PHILS; i++ ){  //Create NUM_PHILS of threads
        ids[i] = i; 
        pthread_create(&threads[i], NULL, philosopher, &ids[i]);
    }
        
    for(int i = 0; i < NUM_PHILS; i++){
        pthread_join(threads[i], NULL);
    }
    
    sem_destroy(&room);
    for(int i = 0; i < NUM_PHILS; i++){
        sem_destroy(&chopstick[i]);
    }
    return 0; 
}

void think(int phil) {
    printf("Philosopher %d is thinking\n", phil);
    // sleep(1); //Sleep could be useful for showing the parallelism in real time. 
}

void eat(int phil) {
    printf("Philosopher %d is eating\n", phil);
    // sleep(1);
}

void *philosopher(void *num){

    int phil = *(int *) num;

    int left = phil;
    int right = (phil + 1) % NUM_PHILS;

    for (int rounds = 0; rounds < TIMES_TO_EAT; rounds++) { //each philosopher eats exactly TIMES_TO_EAT times, then leaves the room.

        think(phil);
 
        sem_wait(&room); 

        printf("Philosopher %d entered the room\n", phil);
 
        sem_wait(&chopstick[left]); 
        sem_wait(&chopstick[right]);
 
        eat(phil);
        printf("Philosopher %d finished eating\n", phil);
 
        sem_post(&chopstick[right]);
        sem_post(&chopstick[left]);
 
        sem_post(&room); //finished eating, leave the room.
    }

    printf("Philosopher %d has eaten %d times and is leaving the table\n", phil, TIMES_TO_EAT);

    
    return NULL;
}
