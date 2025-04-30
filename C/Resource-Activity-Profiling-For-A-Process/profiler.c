//
// Created by Andrew Aberer on 4/23/25.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        fprintf(stderr, "Usage: %s <PID>\n", argv[0]);
        return 1;
    }

    char *end;
    long pid_val = strtol(argv[1], &end, 10);
    if (*end != '\0' || pid_val <= 0)
    {
        fprintf(stderr, "Invalid PID: %s\n", argv[1]);
        return 1;
    }

    // File path buffer and FILE pointer
    char path[256];
    FILE *file;

    // proc/[pid]/comm
    snprintf(path, sizeof(path), "/proc/%ld/comm", pid_val);
    file = fopen(path, "r");
    if (!file)
    {
        // proc/[pid]/comm file cant be opened
        printf("Process with PID %ld is not currently active.\n", pid_val);
        return 1;
    }
    char exec_name[256];
    if (!fgets(exec_name, sizeof(exec_name), file))
    {
        exec_name[0] = '\0'; // empty string if read fails
    }
    fclose(file);
    size_t len = strlen(exec_name);
    if (len > 0 && exec_name[len - 1] == '\n')
    {
        exec_name[len - 1] = '\0';
    }

    // proc/[pid]/stat
    snprintf(path, sizeof(path), "/proc/%ld/stat", pid_val);
    file = fopen(path, "r");
    if (!file)
    {
        printf("Process with PID %ld is not currently active.\n", pid_val);
        return 1;
    }
    char stat_line[1024];
    if (!fgets(stat_line, sizeof(stat_line), file))
    {
        fclose(file);
        printf("Process with PID %ld is not currently active.\n", pid_val);
        return 1;
    }
    fclose(file);

    char state = '\0';
    long ppid_long = 0;
    long pgrp_long = 0;
    unsigned long utime_ticks = 0;
    unsigned long stime_ticks = 0;
    unsigned long maj_faults = 0;

    // out prep
    char *paren_start = strchr(stat_line, '(');
    char *paren_end = strrchr(stat_line, ')');
    if (paren_start && paren_end && paren_end > paren_start)
    {
        state = *(paren_end + 2);
        char *numbers_start = paren_end + 4;
        // tokenize
        char *token = strtok(numbers_start, " ");
        if (token)
            ppid_long = atol(token);
        token = strtok(NULL, " ");
        if (token)
            pgrp_long = atol(token);
        token = strtok(NULL, " ");
        token = strtok(NULL, " ");
        token = strtok(NULL, " ");
        token = strtok(NULL, " ");
        token = strtok(NULL, " ");
        token = strtok(NULL, " ");
        token = strtok(NULL, " ");
        if (token)
            maj_faults = strtoul(token, NULL, 10);
        token = strtok(NULL, " ");
        token = strtok(NULL, " ");
        if (token)
            utime_ticks = strtoul(token, NULL, 10);
        token = strtok(NULL, " ");
        if (token)
            stime_ticks = strtoul(token, NULL, 10);
    }
    else
    {
        snprintf(path, sizeof(path), "/proc/%ld/stat", pid_val);
        file = fopen(path, "r");
        if (file)
        {
            pid_t dummy;
            char comm_buf[256];
            fscanf(file, "%d %255s %c %ld %ld", &dummy, comm_buf, &state, &ppid_long, &pgrp_long);
            fscanf(file, "%*d %*d %*d %*u");
            fscanf(file, "%*lu %*lu");
            fscanf(file, "%lu", &maj_faults);
            fscanf(file, "%*lu");
            fscanf(file, "%lu %lu", &utime_ticks, &stime_ticks);
            fclose(file);
        }
    }

    // memory proc/[pid]/statm
    snprintf(path, sizeof(path), "/proc/%ld/statm", pid_val);
    long total_pages = 0, resident_pages = 0, shared_pages = 0;
    file = fopen(path, "r");
    if (file)
    {
        fscanf(file, "%ld %ld %ld", &total_pages, &resident_pages, &shared_pages);
        fclose(file);
    }

    long ticks_per_sec = sysconf(_SC_CLK_TCK);
    long page_size = sysconf(_SC_PAGESIZE);
    double user_secs = (double)utime_ticks / ticks_per_sec;
    double kernel_secs = (double)stime_ticks / ticks_per_sec;
    unsigned long virt_bytes = (unsigned long)total_pages * page_size;

    printf("[%s] checking pid %ld\n", argv[0], pid_val);
    printf("Executable: (%s)\n", exec_name);
    printf("ppid: %ld\n", ppid_long);
    printf("pgrp: %ld\n", pgrp_long);
    printf("State: %c\n", state);
    printf("User mode: %.3f sec\n", user_secs);
    printf("Kernel mode: %.3f sec\n", kernel_secs);
    printf("Virtual memory: %lu bytes\n", virt_bytes);
    printf("Resident pages: %ld\n", resident_pages);
    printf("Shared pages: %ld\n", shared_pages);
    printf("Page faults: %lu\n", maj_faults);

    return 0;
}
