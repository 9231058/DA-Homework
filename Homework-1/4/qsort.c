/*
 * In The Name Of God
 * ========================================
 * [] File Name : qsort.c
 *
 * [] Creation Date : 09-02-2015
 *
 * [] Last Modified : Tue 10 Feb 2015 10:34:33 PM IRST
 *
 * [] Created By : Parham Alvani (parham.alvani@gmail.com)
 * =======================================
*/
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "qsort.h"

void swap(void *a, void *b, size_t size)
{
	if (a == b)
		return;

	char *temp = NULL;

	temp = malloc(size);

	memcpy(temp, a, size);
	memcpy(a, b, size);
	memcpy(b, temp, size);

	free(temp);
}

size_t partition(void *base, size_t size,
		int (*compar)(const void *, const void *),
		size_t low, size_t high)
{
	size_t i, j;
	void *item;

	item = base + low * size;
	j = low;
	for (i = low + 1; i <= high; i++) {
		if (compar(base + i * size, item) < 0) {
			j++;
			swap(base + i * size,
					base + j * size, size);
		}
	}
	swap(base + low * size,
			base + j * size, size);
	return j;

}

void qsort_r(void *base, size_t size,
		int (*compar)(const void *, const void *),
		size_t low, size_t high)
{
	size_t pivot;

	if (high > low) {
		pivot = partition(base, size, compar, low, high);
		qsort_r(base, size, compar, low, pivot - 1);
		qsort_r(base, size, compar, pivot + 1, high);
	}
}

void qsort(void *base, size_t nmemb, size_t size,
		int (*compar)(const void *, const void *))
{
	qsort_r(base, size, compar, 0, nmemb - 1);
}

