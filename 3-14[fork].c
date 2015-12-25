#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<ctype.h>
#include<string.h>

int validate_input(char *);

int main(int argc, char* argv[]) {
    
    if(argc < 2) {
        printf("Please input a positive integer\n");
        return -1;
    }
  
    int input_number = validate_input(argv[1]);
    if(input_number == -1) {
        printf("Please input a positive integer\n");
        return -1;
    }
  
    pid_t pid = fork();
    if(pid < 0) {
        printf("Error creating child process\n");
    } else if(pid == 0) {
        int n = input_number;
        while(n != 1) {
            n = (n % 2 == 0) ? (n / 2) : (n * 3 + 1);
            printf("%d ", n);
        }
    } else {
        wait(NULL);
        printf("\n");
    }
  
    return 0;
  
}

int validate_input(char* str) {
    int i;
    for(i=0; i<strlen(str); i++) {
        if(!isdigit(str[i])) return -1;
    }
    i = atoi(str);
    return (i == 0) ? -1 : i;
}