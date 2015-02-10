/*
 * In The Name Of God
 * ========================================
 * [] File Name : main.c
 *
 * [] Creation Date : 09-02-2015
 *
 * [] Last Modified : Tue 10 Feb 2015 10:20:56 PM IRST
 *
 * [] Created By : Parham Alvani (parham.alvani@gmail.com)
 * =======================================
*/
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "qsort.h"

int count = 0;

int cmp(const void *a, const void *b)
{
	count++;
	const int *a_i = a;
	const int *b_i = b;

	return *a_i - *b_i;
}

int main(int argc, char *argv[])
{
	clock_t clk;
	time_t t;
	int len;
	int *arr;
	int i = 0;

	scanf("%d", &len);
	arr = malloc(len * sizeof(int));
	srand(time(NULL));
	for (i = 0; i < len; i++)
		arr[i] = rand();

	clk = clock();
	t = time(NULL);
	qsort(arr, len, sizeof(int), cmp);
	clk = clock() - clk;
	t = time(NULL) - t;

	printf("Proceess takes %ld CPU clocks\n", clk);
	printf("Proceess takes %ld sec\n", t);
	printf("Number of compares : %d\n", count);
	for (i = 0; i < len; i++)
		printf("arr[%d] = %d\n", i, arr[i]);

	free(arr);
}
