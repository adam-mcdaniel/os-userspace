#include "os.h"

enum SYSCALL_NOS
{
    SYS_EXIT = 0,
    SYS_PUTCHAR,
    SYS_GETCHAR,
    SYS_YIELD,
    SYS_SLEEP,
    SYS_OLD_GET_EVENTS,
    SYS_OLD_GET_FB,
    SYS_OPEN,
    SYS_CLOSE,
    SYS_READ,
    SYS_WRITE,
    SYS_STAT,
    SYS_SEEK
};


void yield(void) {
    asm volatile("mv a7, %0\necall" : : "r"(SYS_YIELD) : "a7");
}

void sleep(int tm) {
    asm volatile("mv a7, %0\nmv a0, %1\necall" : : "r"(SYS_SLEEP), "r"(tm) : "a0", "a7");
}

int open(const char *path, int flags) {
    int fd;
    asm volatile("mv a7, %1\nmv a0, %2\nmv a1, %3\necall\nmv %0, a0" : "=r"(fd) : "r"(SYS_OPEN), "r"(path), "r"(flags) : "a0", "a1", "a7");
    return fd;
}
void close(int fd)
{
    asm volatile("mv a7, %0\nmv a0, %1\necall" : : "r"(SYS_CLOSE), "r"(fd) : "a0", "a7");
}
int read(int fd, char *buffer, int max_size)
{
    int bytes_read;
    asm volatile("mv a7, %1\nmv a0, %2\nmv a1, %3\nmv a2, %4\necall\nmv %0, a0" : "=r"(bytes_read) : "r"(SYS_READ), "r"(fd), "r"(buffer), "r"(max_size) : "a0", "a1", "a2", "a7");
    return bytes_read;
}
int write(int fd, const char *buffer, int bytes)
{
    int bytes_written;
    asm volatile("mv a7, %1\nmv a0, %2\nmv a1, %3\nmv a2, %4\necall\nmv %0, a0" : "=r"(bytes_written) : "r"(SYS_WRITE), "r"(fd), "r"(buffer), "r"(bytes) : "a0", "a1", "a2", "a7");
    return bytes_written;
}

