/*
 * In The Name Of God
 * ========================================
 * [] File Name : main.c
 *
 * [] Creation Date : 12-02-2015
 *
 * [] Last Modified : Thu 12 Feb 2015 01:53:17 AM IRST
 *
 * [] Created By : Parham Alvani (parham.alvani@gmail.com)
 * =======================================
*/
#include <stdio.h>
#include <stdlib.h>

#include "building.h"

int main(int argc, char *argv[])
{
	char filename[1024];
	int i = 0;
	int number;
	struct building *buildings;

	printf("Please enter filename:\n");
	fgets(filename, 1024, stdin);

	scanf("%d\n", &number);
	buildings = malloc(sizeof(struct building) * number);
	for (i = 0; i < number; i++){
		int height, start, end;
		scanf("%d %d %d", &height, &start, &end);
		buildings[i].height = height;
		buildings[i].start_point = start;
		buildings[i].end_point = end;
	}
}
