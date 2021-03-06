#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <wayland-client.h>

#include "wm.h"

void
debug(char *msg)
{
	if (!wm.debug)
		return;

	fprintf(stdout, "DEBUG: %s.\n", msg);
}

void
warn(char *warn)
{
	fprintf(stderr, "WARNING: %s.\n", warn);
}

void
die(char *err)
{
	fprintf(stderr, "ERROR: %s.\n", err);
	exit(EXIT_FAILURE);
}

void
spawn(void *data, uint32_t time, uint32_t value, uint32_t state)
{
	char *command[] = { data, NULL };

	if (state != WL_KEYBOARD_KEY_STATE_PRESSED)
		return;

	if (fork() == 0) {
		printf("starting %s\n", command[0]);
		execvp(command[0], command);
		exit(EXIT_SUCCESS);
	}
}

