#include <stdint.h>

void init_malloc(void *start, uint32_t size);

void *malloc(uint32_t size);
void free(void *ptr);

