#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>

#define MESSAGE "Hello from parent!"

int main() {
  int fd[2];
  pipe(fd);
  pid_t pids[3];
  for (int i = 0; i < 3; i++) {
    pids[i] = fork();
    if (pids[i] == 0) {
      close(fd[0]);
      
      kill(getppid(), SIGUSR1);
      char buf[100];
      read(fd[1], buf, 100);
      printf("Child %d received message: %s\n", i, buf);

      exit(0);
    }
  }
  close(fd[1]);
  write(fd[0], MESSAGE, strlen(MESSAGE));
  for (int i = 0; i < 3; i++) {
    waitpid(pids[i], NULL, 0);
  }

  return 0;
}

--->
