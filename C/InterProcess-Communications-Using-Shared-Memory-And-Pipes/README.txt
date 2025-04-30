Parent (Coordinator.c) gets a shared memory id, call fork, parent process does things with the pipe to write the shared memory id to the pipe, 
the child (Checker.c) process then does something to actually pass a reference to the read end of that pipe to the child calls execlp, the child process receives
the read end of that pipe does some pipe stuff to put the sharedMemoryId reference (from pipe) into a local variable, then uses that to attach to a shared 
memory segment, child then does some math stuff and due to the result its going to write either a 1 or 0 to the shared memory segment, detach itself from 
shared memory segment and return, which at this point the parent is going to wait for the children to finish, then attach to the shared memory segment, read 
in the values that were written to the shared memory segment, and then finally destroy the shared memory segment