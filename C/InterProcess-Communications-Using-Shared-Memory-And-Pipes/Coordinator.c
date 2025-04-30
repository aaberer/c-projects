//
// Created by Andrew Aberer on 2/26/25.
//

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/wait.h>

int main(int argc, char *argv[])
{
  if (argc != 6)
  {
    return 1;
  }

  const char *divisor = argv[1];

  for (int i = 1; i < argc - 1; i++)
  {
    // Create shared memory pipe
    int sharedMemoryId = shmget(IPC_PRIVATE, sizeof(int), IPC_CREAT | 0666);

    int fd[2];
    pipe(fd);

    // Fork
    pid_t pid = fork();

    if (pid < 0)
    {
      printf("Coordinator: Fork failed.\n");
    }

    // Parent Process Handling
    else if (pid > 0)
    {
      // Pipe stuff
      printf("Coordinator: forked process with ID %d.\n", pid);

      close(fd[0]);
      write(fd[1], &sharedMemoryId, sizeof(sharedMemoryId));
      printf("Coordinator: wrote shm ID %d to pipe (4 bytes)\n", sharedMemoryId);
      close(fd[1]);

      // Wait for the child to finish
      printf("Coordinator: waiting for process [%d].\n", pid);
      int status;
      wait(&status);
      int result = WEXITSTATUS(status);
      printf("Coordinator: child process %d returned %d.\n", pid, result);

      // Attatch to the shared memory segment
      int *sharedMemoryPointer = (int *)shmat(sharedMemoryId, NULL, 0); // Pointer in memory to where shared segment beings

      // Read from the shared memory segment
      int cpResult = *sharedMemoryPointer;
      if (cpResult == 0)
      {
        printf("Coordinator: result 0 read from shared memory: %s is not divisible by %s.\n", argv[i + 1], divisor);
      }
      else if (cpResult == 1)
      {
        printf("Coordinator: result 1 read from shared memory: %s is not divisible by %s.\n", argv[i + 1], divisor);
      }
      else
      {
        printf("Coordinator: Something went wrong in a child process.\n");
      }

      // Destroy the shared memory segment
      shmctl(sharedMemoryId, IPC_RMID, NULL);
    }

    // Child Process
    else
    {
      // Get the sharedMemoryId to the child somehow
      // Using pipes
      // Using execlp
      close(fd[1]);
      char buffer[8];
      sprintf(buffer, "%d", fd[0]);
      execlp("./checker", "checker", buffer, divisor, argv[i + 1], (char *)NULL);
    }
  }
  return 0;
}