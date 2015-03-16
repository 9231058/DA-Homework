/*
 * In The Name Of God
 * ========================================
 * [] File Name : tsp.c
 *
 * [] Creation Date : 16-03-2015
 *
 * [] Last Modified : Mon 16 Mar 2015 03:35:54 AM IRST
 *
 * [] Created By : Parham Alvani (parham.alvani@gmail.com)
 * =======================================
*/
#include <stdlib.h>
#include <stdio.h>
#include <limits.h>

#include "set.h"
#include "tsp.h"

void travel(int n, int **const W, int **P, int *minlength)
{
	int i, j, k, l;
	int **D;
	struct set *V;

	V = set_new();
	for (i = 1; i < n; i++)
		set_add(V, i);

	D = malloc(n * sizeof(int *));
	for (i = 0; i < n; i++)
		D[i] = malloc((1 << n) * sizeof(int));

	for (i = 1; i < n; i++)
		D[i][0] = W[i][0];

	for (k = 1; k <= n - 2; k++) {
		struct set **A;
		int A_n;

		set_subset(V, k, &A, &A_n);
		for (l = 0; l < A_n; l++) {
			for (i = 1; i < n; i++) {
				if (!set_get(A[l], i)) {
					int min = INT_MAX;

					for (j = 0; j < n; j++) {
						if (set_get(A[l], j)) {
							struct set *t;

							t = set_new();
							*t = *(A[l]);
							set_remove(t, j);
							if (D[j][t->set_t] + W[i][j] > 0 && min > D[j][t->set_t] + W[i][j]) {
								min = D[j][t->set_t] + W[i][j];
								printf("%d %d : %d\n", j, t->set_t, D[j][t->set_t]);
							}
							set_free(t);
						}
					}
					D[i][A[l]->set_t] = min;
					printf("%d\n", min);
				}
			}
		}
		for (l = 0; l < A_n; l++)
			set_free(A[l]);
		free(A);
	}

	int min = INT_MAX;

	for (i = 1; i < n; i++) {
		struct set *t;

		t = set_new();
		*t = *V;
		set_remove(t, i);
		if (D[i][t->set_t] + W[0][i] >= 0
				&& min > D[i][t->set_t] + W[0][i])
			min = D[i][t->set_t] + W[0][i];
		set_free(t);
	}

	*minlength = min;

	for (i = 0; i < n; i++)
		free(D[i]);
	free(D);

	set_free(V);
}
