#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>

#define READ_END 0
#define WRITE_END 1


int main(int argc, char *argv[]) {
  
    if(argc != 3) {
        printf("please enter the name of file to be copied and the name of copied file\n");
        return -1;
    }

    int fd[2];
    int file_size = 0;
    pid_t pid;

    if(pipe(fd) == -1) {
        printf("pipe creation failed\n");
        return -1;
    }

    /* open the file which is to be copied and calculate the file size in order to allocate buffer memory */
    FILE *file_to_read = fopen(argv[1], "r");
    fseek(file_to_read, 0, SEEK_END);
    file_size = ftell(file_to_read);
    rewind(file_to_read);

    pid = fork();

    if(pid < 0) {
        printf("child process creation failed\n");
        return -1;
    } else if(pid == 0) {  /* Child process */

        /* close unused pipe */
        close(fd[WRITE_END]);

        /* allocate buffer to store file content which is read from pipe */
        char *temp_file_content = (char *)malloc(sizeof(char) * file_size);
        read(fd[READ_END], temp_file_content, file_size);

        /* open or create the file to write */
        FILE *file_to_write = fopen(argv[2], "w+");
        fwrite(temp_file_content, sizeof(char), file_size, file_to_write);
        fclose(file_to_write);
        close(fd[READ_END]);

    } else { /* parent process */

        /* close unused pipe */
        close(fd[READ_END]);
        
        /* allocate buffer to store file content which is read from the file to be copied */
        char *temp_file_content = (char *)malloc(file_size * sizeof(char));
        fread(temp_file_content, sizeof(char), file_size, file_to_read);
        write(fd[WRITE_END], temp_file_content, file_size);
        fclose(file_to_read);
        close(fd[WRITE_END]);

    }

    return 0;

}