#include "hardware.h"
#include "screen.h"
#include "strings.h"
#include "tools.h"

// CPUID wrapper function
static inline void cpuid(unsigned int code, unsigned int* a, unsigned int* b, unsigned int* c, unsigned int* d) {
    asm volatile("cpuid" : "=a"(*a), "=b"(*b), "=c"(*c), "=d"(*d) : "a"(code));
}

static int check_cpu_features(void) {
    // Check if CPUID is supported
    unsigned int flags;
    asm volatile(
        "pushfl\n\t"           // Save EFLAGS
        "pushfl\n\t"           // Store EFLAGS
        "xorl $0x200000, (%%esp)\n\t" // Invert ID bit in stored EFLAGS
        "popfl\n\t"            // Load stored EFLAGS (with ID bit inverted)
        "pushfl\n\t"           // Store EFLAGS again
        "popl %%eax\n\t"       // Get stored EFLAGS
        "xorl (%%esp), %%eax\n\t"  // Compare with saved EFLAGS
        "popfl\n\t"            // Restore EFLAGS
        : "=a"(flags)
        :: "cc"
    );
    
    // If we couldn't flip ID bit, CPUID isn't supported
    if (!(flags & (1 << 21))) {
        return 0;
    }

    // Check for extended CPUID functions
    unsigned int eax, ebx, ecx, edx;
    cpuid(0x80000000, &eax, &ebx, &ecx, &edx);
    if (eax < 0x80000004) {
        return 0;  // Extended functions not supported
    }

    return 1;  // All required features supported
}

void get_cpu_info(struct cpu_info* info) {
    unsigned int eax, ebx, ecx, edx;
    
    // Get vendor string
    cpuid(0, &eax, &ebx, &ecx, &edx);
    ((unsigned int*)info->vendor)[0] = ebx;
    ((unsigned int*)info->vendor)[1] = edx;
    ((unsigned int*)info->vendor)[2] = ecx;
    info->vendor[12] = '\0';

    // Get family/model/stepping
    cpuid(1, &eax, &ebx, &ecx, &edx);
    info->family = (eax >> 8) & 0xf;
    info->model = (eax >> 4) & 0xf;
    info->stepping = eax & 0xf;

    // Get brand string
    unsigned int brand[12];
    for(int i = 0; i < 3; i++) {
        cpuid(0x80000002 + i, &eax, &ebx, &ecx, &edx);
        brand[i*4+0] = eax;
        brand[i*4+1] = ebx;
        brand[i*4+2] = ecx;
        brand[i*4+3] = edx;
    }
    for(int i = 0; i < 48; i++) {
        info->brand[i] = ((char*)brand)[i];
    }
    info->brand[48] = '\0';
}

void print_hardware_info(void) {
    if (!check_cpu_features()) {
        printf("\nError: CPU does not support required CPUID functions\n");
        return;
    }

    struct cpu_info cpu;
    get_cpu_info(&cpu);

    clear_screen();
    print_b_logo();

    set_offset(32, 7);
    printf("CPU Vendor: ");
    printf(cpu.vendor);
    set_offset(32, 8);
    printf("CPU Brand: ");
    printf(cpu.brand);
    set_offset(32, 9);
    printf("CPU Family: ");
    char family[8];
    int_to_string(cpu.family, family);
    printf(family);
    set_offset(32, 10);
    printf("CPU Model: ");
    char model[8];
    int_to_string(cpu.model, model);
    printf(model);
    set_offset(32, 11);
    printf("CPU Stepping: ");
    char stepping[8];
    int_to_string(cpu.stepping, stepping);
    printf(stepping);
    set_offset(0, 22);
}

unsigned long long get_time(void) {
    unsigned int low, high;
    asm volatile("rdtsc" : "=a"(low), "=d"(high));
    return ((unsigned long long)high << 32) | low;
}