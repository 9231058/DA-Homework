/*
 * In The Name Of God
 * ========================================
 * [] File Name : main.c
 *
 * [] Creation Date : 10-03-2015
 *
 * [] Last Modified : Tue 10 Mar 2015 12:57:18 AM IRST
 *
 * [] Created By : Parham Alvani (parham.alvani@gmail.com)
 * =======================================
*/
#include <stdio.h>

#include "diset.h"

int main(int argc, char *argv[])
{
	struct diset *d = diset_new(10);

	printf("%d\n", diset_find(d, 1));
	diset_merge(d, 1, 4);
	printf("%d\n", diset_find(d, 4));
	printf("%d\n", diset_find(d, 1));
}
