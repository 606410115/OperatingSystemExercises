#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include<unistd.h>
#include<time.h>
#include "barrier_test.h"

pthread_mutex_t mutex, mutex2;
pthread_cond_t cond;
int arrival_count = 0, max;

int init(int);
int barrier_point(void);

int main() {
  
    srand(time(NULL));
    test(5, 15, init, barrier_point);
    return 0;
    
}

int init(int n) {
    
    max = n;
    int error_code = pthread_mutex_init(&mutex, NULL);
    if(!error_code) return error_code;
    error_code = pthread_cond_init(&cond, NULL);
    if(!error_code) return error_code;
    return (error_code == 0) ? 0 : error_code;
  
}

int barrier_point() {
  
    pthread_mutex_lock(&mutex);
    printf("count is now: %d\n", arrival_count);  
    if(arrival_count+1 == max) {
        printf("I'm the last one!\n");  
        pthread_cond_broadcast(&cond);
        arrival_count = 0;
    } else {
        printf("waiting\n");  
        ++arrival_count;
        pthread_cond_wait(&cond, &mutex);
    }
    pthread_mutex_unlock(&mutex);
  
}