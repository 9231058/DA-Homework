/*
 * In The Name Of God
 * ========================================
 * [] File Name : edge.c
 *
 * [] Creation Date : 10-03-2015
 *
 * [] Last Modified : Tue 10 Mar 2015 01:13:38 AM IRST
 *
 * [] Created By : Parham Alvani (parham.alvani@gmail.com)
 * =======================================
*/
#include "edge.h"

int edge_cmp(const struct edge *e1,
		const struct edge *e2)
{
	return e1->weight - e2->weight;
}
