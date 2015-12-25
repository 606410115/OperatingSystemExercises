#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>

int average, max, min;
void* average_thread(void *param);
void* max_thread(void *param);
void* min_thread(void *param);

typedef struct Input_Data {
    int* numbers;
    int length;
} Input_Data;

int main(int argc, char* argv[]) {
    
    pthread_t average_tid, max_tid, min_tid;
    pthread_attr_t average_attr, max_attr, min_attr;
  
    if(argc < 2) {
        printf("Please input a series of numbers.\n");
        return -1;
    }
    
    Input_Data input_data;
    input_data.length = argc - 1;
    input_data.numbers = (int *)malloc(sizeof(int) * input_data.length);
    int i;
    for(i=0; i<input_data.length; i++) (input_data.numbers)[i] = atoi(argv[i+1]);
  
    pthread_attr_init(&average_attr);
    pthread_attr_init(&max_attr);
    pthread_attr_init(&min_attr);
  
    pthread_create(&average_tid, &average_attr, average_thread, &input_data);
    pthread_create(&max_tid, &max_attr, max_thread, &input_data);
    pthread_create(&min_tid, &min_attr, min_thread, &input_data);
  
    pthread_join(average_tid, NULL);
    pthread_join(max_tid, NULL);
    pthread_join(min_tid, NULL);
  
    printf("The average value id %d\n", average);
    printf("The minimum value id %d\n", min);
    printf("The maximum value id %d\n", max);
    
    return 0;
}

void* average_thread(void *param) {
    
    int sum = 0, i;
    Input_Data *d = (data *)param;
    for(i=0; i<d->length; i++) {
      sum += (d->numbers)[i];
    }
    average = sum / d->length;
    pthread_exit(0);
  
}

void* max_thread(void *param) {
    
    int first = 1, _max, temp, i;
    Input_Data *d = (data *)param;
    for(i=0; i<d->length; i++) {
        temp = (d->numbers)[i];
        if(first) {
            first = 0;
            _max = temp;
        } else if(temp > _max) {
            _max = temp;
        }
    }
    max = _max;
    pthread_exit(0);
  
}

void* min_thread(void *param) {
    
    int first = 1, _min, temp, i;
    Input_Data *d = (data *)param;
    for(i=0; i<d->length-1; i++) {
        temp = (d->numbers)[i];
        if(first) {
            first = 0;
            _min = temp;
        } else if(temp < _min) {
            _min = temp;
        }
    }
    min = _min;
    pthread_exit(0);
  
}

