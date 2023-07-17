#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>

#define MESSAGE "Hello from parent!"

int main() {
  // Create a pipe for communication between parent and child processes.
  int fd[2];
  pipe(fd);

  // Fork 3 child processes.
  pid_t pids[3];
  for (int i = 0; i < 3; i++) {
    pids[i] = fork();
    if (pids[i] == 0) {
      // This is the child process.
      close(fd[0]);

      // Send a signal to the parent process.
      kill(getppid(), SIGUSR1);

      // Read a message from the parent process.
      char buf[100];
      read(fd[1], buf, 100);
      printf("Child %d received message: %s\n", i, buf);

      exit(0);
    }
  }

  // Close the writing end of the pipe.
  close(fd[1]);

  // Write the message to the pipe.
  write(fd[0], MESSAGE, strlen(MESSAGE));

  // Wait for all child processes to finish.
  for (int i = 0; i < 3; i++) {
    waitpid(pids[i], NULL, 0);
  }

  return 0;
}

--->
