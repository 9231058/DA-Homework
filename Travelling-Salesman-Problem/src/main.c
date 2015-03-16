/*
 * In The Name Of God
 * ========================================
 * [] File Name : main.c
 *
 * [] Creation Date : 16-03-2015
 *
 * [] Last Modified : Mon 16 Mar 2015 03:17:02 AM IRST
 *
 * [] Created By : Parham Alvani (parham.alvani@gmail.com)
 * =======================================
*/
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#include "tsp.h"

int main(int argc, char *argv[])
{
	int i, j;
	int **W;
	int n;
	int m;

	scanf("%d %d", &n, &m);

	W = malloc(n * sizeof(int *));
	for (i = 0; i < n; i++)
		W[i] = malloc(n * sizeof(int));

	for (i = 0; i < n; i++) {
		for (j = 0; j < n; j++) {
			if (i != j)
				W[i][j] = INT_MAX;
			else
				W[i][j] = 0;
		}
	}

	for (i = 0; i < m; i++) {
		int start;
		int end;
		int weight;

		scanf("%d %d %d", &start, &end, &weight);

		W[start - 1][end - 1] = weight;
	}

	int minlength;

	travel(n, W, NULL, &minlength);

	printf("%d\n", minlength);

	for (i = 0; i < n; i++)
		free(W[i]);
	free(W);
}
