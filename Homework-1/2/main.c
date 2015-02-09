/*
 * In The Name Of God
 * ========================================
 * [] File Name : main.c
 *
 * [] Creation Date : 09-02-2015
 *
 * [] Last Modified : Mon 09 Feb 2015 09:18:41 PM IRST
 *
 * [] Created By : Parham Alvani (parham.alvani@gmail.com)
 * =======================================
*/
#include <stdio.h>

#include "qsort.h"

int cmp(const void *a, const void *b)
{
	const int* a_i = a;
	const int* b_i = b;
	return *b_i - *a_i;
}

int main(int argc, char *argv[])
{
	int arr[] = {1, 2, 10, 3, 123, 12, -10};
	int len = sizeof(arr) / sizeof(int);
	int i = 0;

	qsort(arr, len, sizeof(int), cmp);
	
	for (i = 0; i < len; i++) {
		printf("arr[%d] = %d\n", i, arr[i]);
	}
}
