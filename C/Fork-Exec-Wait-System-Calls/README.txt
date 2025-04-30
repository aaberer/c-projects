Makefile:
Contains everything needed to run this program. Including make clean and make all
to compile the project.

Scheduler:
Main file of this project that implements different CPU scheduling algorithms. Simulates 
First-Come-First-Serve (FCFS), Shortest Job First Preemptive (SJFP), and Priority Preemptive 
scheduling algorithms. It calculates and outputs the average turnaround time, average waiting
time, and throughput for each algorithm.

Checker:
This file takes in inputs from Coordinator and returns 1 if the two numbers are divisible,
and 0 if they are not and returns to the parent (coordinator).

To Run:
Prerequisites - Have gcc installed

Unzip and "cd" to project directory and run make all to build the project. Then
to run simply type in your terminal
./coordinator <divisor> <dividend> <dividend> <dividend> <dividend>

To Clean:
Run "make clean" in the project directory
a
