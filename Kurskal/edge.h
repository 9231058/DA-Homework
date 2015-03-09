/*
 * In The Name Of God
 * ========================================
 * [] File Name : edge.h
 *
 * [] Creation Date : 10-03-2015
 *
 * [] Last Modified : Tue 10 Mar 2015 01:13:28 AM IRST
 *
 * [] Created By : Parham Alvani (parham.alvani@gmail.com)
 * =======================================
*/
#ifndef EDGE_H
#define EDGE_H

struct edge {
	int start;
	int end;
	int weight;
};

int edge_cmp(const struct edge *e1,
		const struct edge *e2);

#endif
