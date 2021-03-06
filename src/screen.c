#include <stdlib.h>

#include "util.h"
#include "wayland.h"
#include "wm.h"

void
new_screen(struct swc_screen *swc)
{
	debug("Adding new screen");
	struct screen *screen = malloc(sizeof(struct screen));
	if (!screen)
		die("Failed to allocate screen");

	screen->swc = swc;
	screen->num_windows = 0;
	wl_list_init(&screen->windows);
	swc_screen_set_handler(swc, &screen_handler, screen);
	wm.active_screen = screen;
}

void
screen_usable_geometry_changed(void *data)
{
	debug("Screen geometry changed");
	struct screen *screen = data;

	if (screen) {} /* FIXME shut up the compiler */
	/*
	 * TODO
	 * - perhaps rearrange windows
	 */
}

void
screen_entered(void *data)
{
	debug("Screen entered");
	struct screen *screen = data;

	wm.active_screen = screen;
}

void
screen_add_window(struct screen *screen, struct window *window)
{
	debug("Window added to screen");
	window->screen = screen;
	wl_list_insert(&screen->windows, &window->link);
	screen->num_windows += 1;
	swc_window_show(window->swc);
}

void
screen_remove_window(struct screen *screen, struct window *window)
{
	debug("Window removed from screen");
	window->screen = NULL;
	wl_list_remove(&window->link);
	screen->num_windows -= 1;
	swc_window_hide(window->swc);
}

struct swc_rectangle *
get_screen_geometry(struct screen *screen)
{
	return &screen->swc->usable_geometry;
}

