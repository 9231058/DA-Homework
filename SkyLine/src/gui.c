/*
 * In The Name Of God
 * ========================================
 * [] File Name : gui.c
 *
 * [] Creation Date : 26-02-2015
 *
 * [] Last Modified : Fri 27 Feb 2015 12:04:05 AM IRST
 *
 * [] Created By : Parham Alvani (parham.alvani@gmail.com)
 * =======================================
*/
#include <stdlib.h>

#include <gtk/gtk.h>

#include "building.h"
#include "gui.h"

extern int number;
extern struct building *buildings;

/* Surface to store current scribbles */
static cairo_surface_t *surface;

void clear_surface(void)
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
gboolean configure_event_handler(GtkWidget *widget,
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
gboolean draw_handler(GtkWidget *widget,
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

void draw_buildings(GtkWidget *widget)
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
	gtk_widget_queue_draw_area(widget, 0, 0,
			gtk_widget_get_allocated_width(widget),
			gtk_widget_get_allocated_height(widget));
}

/*
* Handle button press events by either drawing a skyline
* or drawing a buildings, depending on which button was pressed.
* The ::button-press signal handler receives a GdkEventButton
* struct which contains this information.
*/
gboolean button_press_event_handler(GtkWidget *widget,
		GdkEventButton *event, gpointer data)
{
	/* paranoia check, in case we haven't gotten a configure event */
	if (surface == NULL)
		return FALSE;
	if (event->button == GDK_BUTTON_PRIMARY)
		draw_buildings(widget);
	else if (event->button == GDK_BUTTON_SECONDARY)
		;
	/* We've handled the event, stop processing */
	return TRUE;
}

void close_window(void)
{
	if (surface)
		cairo_surface_destroy(surface);
	free(buildings);
	gtk_main_quit();
}
