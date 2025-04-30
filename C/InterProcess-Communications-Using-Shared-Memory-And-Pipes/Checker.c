//
// Created by Andrew Aberer on 2/26/25.
//

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/types.h>

int main(int argc, char** argv) {

    pid_t pid = getpid();
    printf("Checker process [%d]: Starting.\n", pid);

    // Pipe stuff
    int fd = atoi(argv[1]);
    int sharedMemoryId;

    // Arg retrieval
    const int divisor = atoi(argv[2]);
    const int dividend = atoi(argv[3]);

    read(fd, &sharedMemoryId, sizeof(sharedMemoryId));
    printf("Checker process [%d]: read 4 bytes containing shm ID %d\n", pid, sharedMemoryId);

    // Get a pointer to the shared memory
    int *sharedMemoryPointer = (int*)shmat(sharedMemoryId, NULL, 0); // Pointer in memory to where shared segment beings

    int result = -1; // Init to false value
    if (dividend % divisor == 0)
    {
        printf("Checker process [%d]: %d *IS* divisible by %d.\n", pid, dividend, divisor);
        printf("Checker process [%d]: Returning 1.\n", pid);
        result = 1;
    }
    else
    {
        printf("Checker process [%d]: %d *IS NOT* divisible by %d.\n", pid, dividend, divisor);
        printf("Checker process [%d]: Returning 0.\n", pid);
        result = 0;
    }

    // Write to shared memory
    *sharedMemoryPointer = result; // Storing value 1 in shared memory segment
    printf("Checker process [%d]: Wrote result (%d) to shared memory.\n", pid, result);

    // Detach from shared memory segment
    shmdt(sharedMemoryPointer);

    return 0;
}