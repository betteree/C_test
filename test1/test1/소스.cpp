#include <stdio.h>
#include <iostream>
using namespace std;

int main()
{
	int N = 0;
	int sec[20] ;
	int M=0, Y = 0;
	cin >> N;
	
	for (int i = 0; i < N; i++)
	{
		cin >> sec[i];
	}

	for (int j = 0; j < N; j++)
	{
			int M_div= sec[j] / 60;
			M += 15* M_div+15;
			int Y_div = sec[j] / 30;
			Y += 10 * Y_div+10;
	}
	if (Y == M)
		printf("Y M %d", Y);
	else if (Y < M)
		printf("Y %d", Y);
	else if (Y > M)
		printf("M %d", M);
	
	
}