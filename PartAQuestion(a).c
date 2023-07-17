#include <iostream>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <cstring>
#include <signal.h>

#define PIPE_READ_END 0
#define PIPE_WRITE_END 1

void signalHandler(int signum) {
    std::cout << "Received SIGUSR1 signal" << std::endl;
}

int main() {

    int pipe_parent_child1[2];
    int pipe_parent_child2[2];
    int pipe_parent_child3[2];

    pipe(pipe_parent_child1);
    pipe(pipe_parent_child2);
    pipe(pipe_parent_child3);
    pid_t child1_pid = fork();

    if (child1_pid == 0) {  
        close(pipe_parent_child1[PIPE_WRITE_END]);
        close(pipe_parent_child2[PIPE_READ_END]);
        close(pipe_parent_child3[PIPE_READ_END]);

        char message[256];
        read(pipe_parent_child1[PIPE_READ_END], message, sizeof(message));
        std::cout << "Child 1 received message: " << message << std::endl;
        char response[] = "Child 1: Message received";
        write(pipe_parent_child2[PIPE_WRITE_END], response, strlen(response) + 1);

        close(pipe_parent_child1[PIPE_READ_END]);
        close(pipe_parent_child2[PIPE_WRITE_END]);
        close(pipe_parent_child3[PIPE_WRITE_END]);

        return 0;
    }

    pid_t child2_pid = fork();

    if (child2_pid == 0) {  
        close(pipe_parent_child1[PIPE_READ_END]);
        close(pipe_parent_child2[PIPE_WRITE_END]);
        close(pipe_parent_child3[PIPE_READ_END]);

        char message[256];
        read(pipe_parent_child2[PIPE_READ_END], message, sizeof(message));
        std::cout << "Child 2 received message: " << message << std::endl;

        char response[] = "Child 2: Message received";
        write(pipe_parent_child3[PIPE_WRITE_END], response, strlen(response) + 1);

        close(pipe_parent_child2[PIPE_READ_END]);
        close(pipe_parent_child3[PIPE_WRITE_END]);

        return 0;
    }

    pid_t child3_pid = fork();

    if (child3_pid == 0) {  
      
        close(pipe_parent_child1[PIPE_READ_END]);
        close(pipe_parent_child2[PIPE_READ_END]);
        close(pipe_parent_child3[PIPE_WRITE_END]);

        char message[256];
        read(pipe_parent_child3[PIPE_READ_END], message, sizeof(message));
        std::cout << "Child 3 received message: " << message << std::endl;

        kill(getppid(), SIGUSR1);

        close(pipe_parent_child3[PIPE_READ_END]);
        close(pipe_parent_child1[PIPE_WRITE_END]);
        close(pipe_parent_child2[PIPE_WRITE_END]);

        return 0;
    }

    if (child1_pid > 0 && child2_pid > 0 && child3_pid > 0) {  // Parent process
  
        close(pipe_parent_child1[PIPE_READ_END]);
        close(pipe_parent_child2[PIPE_READ_END]);
        close(pipe_parent_child3[PIPE_READ_END]);

        char message[] = "Parent: Hello Child 1";
        write(pipe_parent_child1[PIPE_WRITE_END], message, strlen(message) + 1);

        char response2[256];
        read(pipe_parent_child2[PIPE_READ_END], response2, sizeof(response2));
        std::cout << "Parent received response from Child 2: " << response2 << std::endl;

        char response3[256];
        read(pipe_parent_child3[PIPE_READ_END], response3, sizeof(response3));
        std::cout << "Parent received response from Child 3: " << response3 << std::endl;

       
        signal(SIGUSR1, signalHandler);

        
        close(pipe_parent_child1[PIPE_WRITE_END]);
        close(pipe_parent_child2[PIPE_WRITE_END]);
        close(pipe_parent_child3[PIPE_WRITE_END]);

        wait(NULL);
        wait(NULL);
        wait(NULL);

        return 0;
    }
}
