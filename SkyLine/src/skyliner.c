/*
 * In The Name Of God
 * ========================================
 * [] File Name : skyliner.c
 *
 * [] Creation Date : 26-02-2015
 *
 * [] Last Modified : Thu 26 Feb 2015 04:46:14 PM IRST
 *
 * [] Created By : Parham Alvani (parham.alvani@gmail.com)
 * =======================================
*/
#include <stdlib.h>

#include "building.h"

static void skyliner_r(const struct building *buildings,
		int i, int j,
		struct building **out_buildings,
		int *out_size)
{
	if (i > j) {
		return;
	} else if (i == j) {
		*out_size = 1;
		*out_buildings = malloc(sizeof(struct building));
		**out_buildings = buildings[i];
		return;
	} else {
		struct building *left_buildings, *right_buildings;
		int left_size, right_size;
		int m = (i + j) / 2;

		skyliner_r(buildings, i, m, &left_buildings, &left_size);
		skyliner_r(buildings, m + 1, j, &right_buildings, &right_size);

		int index_left = 0;
		int index_right = 0;
		
		while (index_left < left_size && index_right < right_size) {		
		}
		while (index_left < left_size) {
		}
		while (index_right < right_size) {
		}

		free(left_buildings);
		free(right_buildings);

	}
}

void skyliner(const struct building *buildings, int size,
		struct building **out_buildings,
		int *out_size)
{
	skyliner_r(buildings, 0, size - 1, out_buildings, out_size);
}
