//
// Created by Andrew Aberer on 2/16/25.
//

#include <sys/types.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/resource.h>
#include <sys/wait.h>

int main(int argc, char* argv[])
{
    if (argc != 6)
    {
        return 1;
    }

    const char* divisor = argv[1];

    for (int i = 1; i < argc - 1; i++)
    {
        pid_t pid = fork();

        if (pid == -1)
        {
            printf("Coordinator: Fork failed.\n");
        }

        else if (pid == 0)
        {
            execlp("./Checker", "Checker", divisor, argv[i + 1], (char*)NULL);
        }

        else
        {
            printf("Coordinator: forked process with ID %d.\n", pid);
            printf("Coordinator: waiting for process [%d].\n", pid);
            int status;
            wait(&status);
            int result = WEXITSTATUS(status);
            printf("Coordinator: child process %d returned %d.\n", pid, result);
        }
    }
    printf("Coordinator: exiting.\n");
}
