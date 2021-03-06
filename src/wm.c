#include <getopt.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "config.h"
#include "util.h"
#include "wayland.h"
#include "wm.h"

int
main(int argc, char *argv[])
{
	int opt;

	wm.debug = false;
	wm.margins = 0;
	wm.borderwidth = 1;
	wm.bordercolor = 0xffffffff;

	while((opt = getopt(argc, argv, "c:dhv")) != -1) {
		switch (opt) {
		case 'c':
			wm.config = optarg;
			break;
		case 'd':
			wm.debug = true;
			debug("Enabled debug output");
			break;
		case 'h':
			puts("TBD");
			exit(EXIT_SUCCESS);
		case 'v':
			printf("%s %s\n", argv[0], VERSION);
			exit(EXIT_SUCCESS);
		default:
			fprintf(stderr, "Usage: %s [-dhv] [-c config]\n",
			        argv[0]);
			exit(EXIT_FAILURE);
		}
	}

	wm.wl_connection = wayland_init();

	/* Load the default config if no custom one has been loaded */
	if (!wm.config) {
		char *conf = getenv("XDG_CONFIG_HOME");
		strcat(conf, "/.wmrc");
		wm.config = conf;
	}

	load_config(wm.config);

	wayland_run(wm.wl_connection);

	wayland_exit(wm.wl_connection);

	return EXIT_SUCCESS;
}

void
quit(void *data, uint32_t time, uint32_t value, uint32_t state)
{
	exit(EXIT_SUCCESS);
}

