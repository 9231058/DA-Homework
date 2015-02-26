/*
 * In The Name Of God
 * ========================================
 * [] File Name : main.c
 *
 * [] Creation Date : 12-02-2015
 *
 * [] Last Modified : Thu 26 Feb 2015 12:13:18 PM IRST
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
#include "gui.h"

/* Buildings ... */
struct building *buildings;
int number;

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

	frame = gtk_frame_new(NULL);
	gtk_frame_set_shadow_type(GTK_FRAME(frame), GTK_SHADOW_IN);
	gtk_container_add(GTK_CONTAINER(window), frame);

	board = gtk_drawing_area_new();
	/* set a minimum size */
	gtk_widget_set_size_request(board, 800, 600);

	gtk_container_add(GTK_CONTAINER(frame), board);

	/* Signals used to handle the backing surface */
	g_signal_connect(board, "draw",
			G_CALLBACK(draw_handler), NULL);
	g_signal_connect(board, "configure-event",
			G_CALLBACK(configure_event_handler), NULL);

	/* Event signals */
	g_signal_connect(board, "button-press-event",
			G_CALLBACK(button_press_event_handler), NULL);

	/*
	 * Ask to receive events the drawing area doesn't normally
	 * subscribe to. In particular, we need to ask for the
	 * button press and motion notify events that want to handle.
	*/
	gtk_widget_set_events(board,
			gtk_widget_get_events(board) | GDK_BUTTON_PRESS_MASK);

	gtk_widget_show_all(window);

	gtk_main();

	return 0;
}
