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
void get_memory_size(unsigned int* kb_low, unsigned int* kb_high);
void print_hardware_info(void);

#endif