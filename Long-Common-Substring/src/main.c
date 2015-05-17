/*
 * In The Name Of God
 * ========================================
 * [] File Name : main.c
 *
 * [] Creation Date : 04-03-2015
 *
 * [] Last Modified : Wed 04 Mar 2015 05:20:36 AM IRST
 *
 * [] Created By : Parham Alvani (parham.alvani@gmail.com)
 * =======================================
*/
#include <stdio.h>

#include "lcs.h"

int main(int argc, char *argv[])
{
	char A[1024];
	char B[1024];

	scanf("%s %s", A, B);

	printf("%d\n", lcs(A, B));
	lcs_fprint(stdout);
}
