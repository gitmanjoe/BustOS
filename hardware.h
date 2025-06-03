#ifndef HARDWARE_H
#define HARDWARE_H

// CPU info structure
struct cpu_info {
    char vendor[13];
    char brand[49];
    unsigned int family;
    unsigned int model;
    unsigned int stepping;
};

// Function declarations
void get_cpu_info(struct cpu_info* info);
void print_hardware_info(void);

unsigned long long get_time(void);

#endif