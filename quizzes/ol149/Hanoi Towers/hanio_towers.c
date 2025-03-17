#include <stdio.h>


void HanoiTowers(int n, char from, char to, char mid_p)
{
	if (n == 1)
	{
		printf("\n Move disk 1 from rod %c to rod %c", from, to);
		return;
	}
	HanoiTowers(n-1, from, mid_p, to);
	printf("\n Move disk %d from rod %c to rod %c", n, from, to);
	HanoiTowers(n-1, mid_p, to, from);
}

int main()
{
	int n = 5; /* Number of disks*/
	HanoiTowers(n, 'A', 'C', 'B'); /* A, B and C are names of rods*/
	return 0;
}

