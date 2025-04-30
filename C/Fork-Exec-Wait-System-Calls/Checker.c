//
// Created by Andrew Aberer on 2/16/25.
//

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>

int main(int argc, char* argv[])
{
    const int divisor = atoi(argv[1]);
    const int dividend = atoi(argv[2]);
    pid_t pid = getpid();
    printf("Checker process [%d]: Starting.\n", pid);
    if (dividend % divisor == 0)
    {
        printf("Checker process [%d]: %d *IS* divisible by %d.\n", pid, dividend, divisor);
        printf("Checker process [%d]: Returning 1.\n", pid);
        exit(1);
    }
    else
    {
        printf("Checker process [%d]: %d *IS NOT* divisible by %d.\n", pid, dividend, divisor);
        printf("Checker process [%d]: Returning 0.\n", pid);
        exit(0);
    }
}
