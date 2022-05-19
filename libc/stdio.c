#include "stdio.h"
#include "event.h"

char getchar(void) {
    char ret;
    asm volatile("mv a7, %1\necall\nmv %0, a0" : "=r"(ret) : "r"(2) : "a0", "a7");
    return ret;
}

void putchar(char c) {
    asm volatile("mv a7, %0\nmv a0, %1\necall" : : "r"(1), "r"(c) : "a0", "a7");
}

unsigned int get_events(InputEvent event_buffer[], unsigned int max_events) {
    unsigned int ret;
    asm volatile("mv a7, %1\nmv a0, %2\nmv a1, %3\necall\nmv %0, a0" : "=r"(ret) : "r"(5), "r"(event_buffer), "r"(max_events) : "a0", "a1", "a7");
    return ret;
}
