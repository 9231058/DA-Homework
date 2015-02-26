/*
 * In The Name Of God
 * ========================================
 * [] File Name : skyliner.c
 *
 * [] Creation Date : 26-02-2015
 *
 * [] Last Modified : Thu 26 Feb 2015 05:58:06 PM IRST
 *
 * [] Created By : Parham Alvani (parham.alvani@gmail.com)
 * =======================================
*/
#include <stdlib.h>
#include <stdio.h>

#include "building.h"

static void skyliner_r(const struct building *buildings,
		int i, int j,
		struct building **out_buildings,
		int *out_size)
{
	if (i > j) {
		return;
	} else if (i == j) {
		*out_size = 2;
		*out_buildings = malloc(sizeof(struct building) * 2);
		(*out_buildings)->start_point = buildings[i].start_point;
		(*out_buildings)->height = buildings[i].height;
		(*out_buildings + 1)->start_point = buildings[i].end_point;
		(*out_buildings + 1)->height = 0;
		return;
	} else {
		struct building *left_buildings, *right_buildings;
		int left_size, right_size;
		int m = (i + j) / 2;

		skyliner_r(buildings, i, m, &left_buildings, &left_size);
		skyliner_r(buildings, m + 1, j, &right_buildings, &right_size);


		*out_buildings = malloc((left_size + right_size) * sizeof(struct building));
		*out_size = 0;

		int index_left = 0;
		int index_right = 0;	
		int curH1 = 0, curH2 = 0, curX = 0;

		while (index_left < left_size && index_right < right_size) {
			if (left_buildings[index_left].start_point <
					right_buildings[index_right].start_point) {
				
				curX = left_buildings[index_left].start_point;
				curH1 = left_buildings[index_left].height;
				
				index_left++;
				
				if (curH1 > curH2) {
					(*out_buildings + *out_size)->start_point
						= curX;
					(*out_buildings + *out_size)->height
						= curH1;
					(*out_size)++;
				}
			} else if (left_buildings[index_left].start_point >
					right_buildings[index_right].start_point) {

				curX = right_buildings[index_right].start_point;
				curH2 = right_buildings[index_right].height;

				index_right++;
				
				if (curH2 > curH1) {
					(*out_buildings + *out_size)->start_point
						= curX;
					(*out_buildings + *out_size)->height
						= curH2;
					(*out_size)++;
				}
			} else {
				curX = right_buildings[index_right].start_point;
				curH1 = left_buildings[index_left].height;
				curH2 = right_buildings[index_right].height;
	
				index_right++;
				index_left++;
				
				(*out_buildings + *out_size)->start_point
					= curX;
				(*out_buildings + *out_size)->height
					= (curH1 > curH2) ? curH1 : curH2;

				(*out_size)++;

			}
		}
		if (index_right == right_size) {
			while (index_left < left_size) {
					(*out_buildings + *out_size)->start_point
						= left_buildings[index_left].start_point;
					(*out_buildings + *out_size)->height
						= left_buildings[index_left].height;

					index_left++;
					(*out_size)++;
			}
		} else if (index_left == left_size) {
			while (index_right < right_size) {
					(*out_buildings + *out_size)->start_point
						= right_buildings[index_right].start_point;
					(*out_buildings + *out_size)->height
						= right_buildings[index_right].height;

					index_right++;
					(*out_size)++;
			}
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
