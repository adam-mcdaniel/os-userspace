#include <stdint.h>

typedef struct Rectangle {
    uint32_t x;
    uint32_t y;
    uint32_t width;
    uint32_t height;
} Rectangle;

typedef struct Pixel {
    uint8_t r;
    uint8_t g;
    uint8_t b;
    uint8_t a;
} Pixel;

typedef struct VirtioInputEvent {
    uint16_t type;
    uint16_t code;
    uint32_t value;
} VirtioInputEvent;

int get_env(char *name, char *value);
int put_env(char *name, char *value);

int get_pid(void);
int next_pid(int);

int pid_get_env(int pid, char *name, char *value);
int pid_put_env(int pid, char *name, char *value);
int screen_draw_rect(Pixel *buf, Rectangle *rect, uint64_t x_scale, uint64_t y_scale);
int screen_get_dims(Rectangle *rect);
// void screen_flush(void);
void screen_flush(Rectangle *rect);

uint64_t get_time(void);

int get_keyboard_event(VirtioInputEvent *event);
int get_tablet_event(VirtioInputEvent *event);

