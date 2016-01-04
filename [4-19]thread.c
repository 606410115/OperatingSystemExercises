#include<stdio.h>
#include<pthread.h>

void* runner(void *param);

int main(int argc, char* argv[]) {
    
    pthread_t tid;
    pthread_attr_t attr;
  
    if(argc < 2) {
        printf("Please input a positive integer.\n");
        return -1;
    }
  
    if(atoi(argv[1]) <= 0) {
        printf("Input error! Please input a positive integer.\n");
        return -1;
    }
  
    pthread_attr_init(&attr);
    pthread_create(&tid, &attr, runner, argv[1]);
    pthread_join(tid, NULL);
    
    return 0;
}

void* runner(void *param) {
    
    int n = atoi(param), i, j, count;
    for(i=2; i<=n; i++) {
        count = 0;
        for(j=1; j<=i; j++) {
            if(i % j == 0) count++;
        }
        if(count == 2) printf("%d ", i);
    }
    printf("\n");
    pthread_exit(0);
  
}

