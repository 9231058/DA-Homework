/*
 * In The Name Of God
 * ========================================
 * [] File Name : fknapsack.c
 *
 * [] Creation Date : 08-04-2015
 *
 * [] Last Modified : Wed 08 Apr 2015 12:49:33 PM IRDT
 *
 * [] Created By : Parham Alvani (parham.alvani@gmail.com)
 * =======================================
*/
#include <stdlib.h>

#include "object.h"
#include "fknapsack.h"

static int object_cmp_v(const void *a, const void *b)
{
	return object_cmp((const struct object *)a,
			(const struct object *)b);
}

void fknapsack(int n, struct object *obj, int W,
		int *n_out, struct object **obj_out)
{
	int sum = 0;
	int i = n - 1;

	*obj_out = malloc(n * sizeof(struct object));
	*n_out = 0;
	qsort(obj, sizeof(struct object), n, object_cmp_v);
	while (sum <= W) {
		if (sum + obj[i].weight < W) {
			sum += obj[i].weight;
			*obj_out[*n_out] = obj[i];
			(*n_out)++;
			i++;
		} else {
			*obj_out[*n_out] = obj[i];
			(*obj_out[*n_out]).weight = W - sum;
			sum += (W - sum);
			(*n_out)++;
		}
	}
}
