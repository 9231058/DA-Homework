/*
 * In The Name Of God
 * ========================================
 * [] File Name : main.c
 *
 * [] Creation Date : 12-02-2015
 *
 * [] Last Modified : Thu 12 Feb 2015 03:01:31 AM IRST
 *
 * [] Created By : Parham Alvani (parham.alvani@gmail.com)
 * =======================================
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <gtk/gtk.h>

#include "building.h"
#include "common.h"

/* Buildings ... */
static struct building *buildings;
static int number;

/* Surface to store current scribbles */
static cairo_surface_t *surface;

static void clear_surface(void)
{
	cairo_t *cr;

	cr = cairo_create(surface);

	cairo_set_source_rgb(cr, 1, 1, 1);
	cairo_paint(cr);

	cairo_destroy(cr);
}

/*
 * Create a new surface of the appropriate size to store our scribbles
*/
static gboolean configure_event_handler(GtkWidget *widget,
		GdkEventConfigure *event, gpointer data)
{
	if (surface)
		cairo_surface_destroy(surface);

	surface = gdk_window_create_similar_surface(
			gtk_widget_get_window(widget),
			CAIRO_CONTENT_COLOR,
			gtk_widget_get_allocated_width(widget),
			gtk_widget_get_allocated_height(widget));

	/* Initialize the surface to white */
	clear_surface();

	/* We've handled the configure event, no need for further processing. */
	return TRUE;
}

/*
 * Redraw the screen from the surface. Note that the ::draw
 * signal receives a ready-to-be-used cairo_t that is already
 * clipped to only draw the exposed areas of the widget
*/
static gboolean draw_handler(GtkWidget *widget,
		cairo_t *cr, gpointer data)
{
	/*
	 * This is a convenience function for creating a pattern from surface
	 * and setting it as the source in cr with cairo_set_source().
	 *
	 * The x and y parameters give the user-space coordinate at
	 * which the surface origin should appear. (The surface
	 * origin is its upper-left corner before any transformation
	 * has been applied.) The x and y patterns are negated
	 * and then set as translation values in the pattern matrix.
	*/
	cairo_set_source_surface(cr, surface, 0, 0);
	cairo_paint(cr);

	return FALSE;
}


static void draw_buildings(GtkWidget *widget)
{
	cairo_t *cr;
	int i;

	/* Paint to the surface, where we store our state */
	cr = cairo_create(surface);
	
	for (i = 0; i < number; i++) {
		int start = buildings[i].start_point;
		int end = buildings[i].end_point;
		int height = buildings[i].height;

		cairo_move_to(cr, start, 0);
		cairo_line_to(cr, start, height);
		cairo_line_to(cr, end, height);
		cairo_line_to(cr, end, 0);
	}


	cairo_fill(cr);

	cairo_destroy(cr);

	/* Now invalidate the affected region of the drawing area. */
	gtk_widget_queue_draw_area (widget, 0, 0,
			gtk_widget_get_allocated_width(widget),
			gtk_widget_get_allocated_height(widget));
}

/*
 * Handle button press events by either drawing a skyline
 * or drawing a buildings, depending on which button was pressed.
 * The ::button-press signal handler receives a GdkEventButton
 * struct which contains this information.
*/
static gboolean button_press_event_handler(GtkWidget *widget,
		GdkEventButton *event, gpointer data)
{
	/* paranoia check, in case we haven't gotten a configure event */
	if (surface == NULL)
		return FALSE;

	if (event->button == GDK_BUTTON_PRIMARY) {
		draw_buildings(widget);
	} else if (event->button == GDK_BUTTON_SECONDARY) {
		;
	}

	/* We've handled the event, stop processing */
	return TRUE;
}

static void close_window(void)
{
	if (surface)
		cairo_surface_destroy(surface);

	free(buildings);

	gtk_main_quit ();
}

int main(int argc, char *argv[])
{
	char filename[1024];
	int i = 0;
	FILE *file = NULL;

	printf("Please enter filename:\n");
	fgets(filename, 1024, stdin);
	filename[strlen(filename) - 1] = '\0';

	file = fopen(filename, "r");
	if (!file)
		sdie("fopen()");

	fscanf(file, "%d", &number);
	buildings = malloc(sizeof(struct building) * number);
	for (i = 0; i < number; i++) {
		int height, start, end;

		fscanf(file, "%d %d %d", &height, &start, &end);

		buildings[i].height = height;
		buildings[i].start_point = start;
		buildings[i].end_point = end;
	}
	fclose(file);

	printf("starting GUI ...\n");

	GtkWidget *window;
	GtkWidget *frame;
	GtkWidget *board;

	gtk_init(&argc, &argv);

	window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_window_set_title(GTK_WINDOW(window), "Drawing Area");

	g_signal_connect(window, "destroy", G_CALLBACK(close_window), NULL);

	gtk_container_set_border_width(GTK_CONTAINER(window), 8);

	frame = gtk_frame_new (NULL);
	gtk_frame_set_shadow_type (GTK_FRAME (frame), GTK_SHADOW_IN);
	gtk_container_add (GTK_CONTAINER (window), frame);

	board = gtk_drawing_area_new();
	/* set a minimum size */
	gtk_widget_set_size_request(board, 800, 600);

	gtk_container_add(GTK_CONTAINER(frame), board);

	/* Signals used to handle the backing surface */
	g_signal_connect(board, "draw", G_CALLBACK(draw_handler), NULL);
	g_signal_connect(board,"configure-event", G_CALLBACK(configure_event_handler), NULL);

	/* Event signals */
	g_signal_connect(board, "button-press-event", G_CALLBACK(button_press_event_handler), NULL);

	/*
	 * Ask to receive events the drawing area doesn't normally
	 * subscribe to. In particular, we need to ask for the
	 * button press and motion notify events that want to handle.
	*/
	gtk_widget_set_events(board, gtk_widget_get_events(board) | GDK_BUTTON_PRESS_MASK);

	gtk_widget_show_all (window);

	gtk_main ();

	return 0;
}
