#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include<unistd.h>
#include<time.h>

pthread_mutex_t mutex, mutex2;
pthread_cond_t cond;
int thread_count = 0;

void test(int, int, int (*init)(int), int (*barrier_point)(void));
void threads_create(pthread_t*, int,  int (*barrier_point)(void));
void threads_join(pthread_t*, int);
void *test_thread(void*);


/*
 * used for creating n threads
 */
void threads_create(pthread_t *threads, int n, int (*barrier_point)(void)) {
    int i;  
    for(i=0; i<n; i++) {
        pthread_create(&(threads[i]), NULL, test_thread, barrier_point);
    }
}

/*
 * used for waiting for n threads to complete
 */
void threads_join(pthread_t *threads, int n) {
    int i;  
    for(i=0; i<n; i++) {
        pthread_join(threads[i], NULL);
    }
}

/*
 * function for simulation
 */
void test(int barrier_max, int thread_number, int (*init)(int), int (*barrier_point)(void)) {
  
    pthread_t threads[thread_number];
    if(init(barrier_max) != 0) {
        printf("Error occurred in pthread_mutex_init or pthread_cond_init !\n");
        return;
    }
    threads_create(threads, thread_number, barrier_point);
    threads_join(threads, thread_number);
    printf("test complete\n");
  
}

/*
 *  function for each thread
 */
void *test_thread(void* param) {
    
    int (*barrier_point)(void) = param;
    pthread_mutex_lock(&mutex2);
    int no = ++thread_count;
    pthread_mutex_unlock(&mutex2);
    printf("#%d start running\n", no);
    int sleep_time = rand() % 10 + 1;
    sleep(sleep_time);
    printf("#%d has arrived at barrier point!\n", no);
    barrier_point();
    printf("#%d has left barrier point!\n", no);
    pthread_exit(0); 
  
}