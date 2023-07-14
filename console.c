#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include "libc/event.h"

static void run_command(char a[]);

void main(void) {
	char c;
	char command[256];
	int at = 0;
	printf("Welcome to the console in user space. Please type 'help' for help.\n");
	printf("~> ");
	do {
        c = getchar();
		if (c == '\r' || c == '\n') {
			command[at] = '\0';
			printf("\n");
			run_command(command);
			printf("~> ");
			at = 0;
		}
		else if (c == '\b' || c == 127) {
			// Backspace or "delete"
			if (at > 0) {
				// Erase character 
				printf("\b \b");
				at--;
			}
		}
		else if (c == 0x1B) {
			// Escape sequence
			char esc1 = getchar();
			char esc2 = getchar();
			if (esc1 == 0x5B) {
				switch (esc2) {
					case 0x41:
						printf("UP\n");
					break;
					case 0x42:
						printf("DOWN\n");
					break;
					case 0x43:
						printf("RIGHT\n");
					break;
					case 0x44:
						printf("LEFT\n");
					break;
				}
			}
		}
		else if (c != 255) {
			if (at < 255) {
				command[at++] = c;
				// Echo it back out to the user
				putchar(c);
			}
		}
		else {
			sleep(10);
		}
	} while (1);
}

static void run_command(char command[]) {
	if (!strcmp(command, "help")) {
		printf("Help is coming!\n");
	}
	else if (!strcmp(command, "gev")) {
		InputEvent events[64];
		int num = get_events(events, 64);
		for (int i = 0;i < num;i++) {
			printf("INPUT: [0x%02x:0x%02x:0x%08x]\n", events[i].type, events[i].code, events[i].value);
		}
		printf("Processed %d events.\n", num);
	}
	else if (command[0] != '\0') {
		printf("Unknown command '%s'.\n", command);
	}
}

