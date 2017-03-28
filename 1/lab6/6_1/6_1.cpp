//Дано N кубиков.Требуется определить каким количеством способов можно выстроить из этих кубиков
//пирамиду.
//Формат входных данных :
//На вход подается количество кубиков N.
//Формат выходных данных :
//Вывести число различных пирамид из N кубиков.
//
//6_1.​ Высокая пирамида.​Каждый вышележащий слой пирамиды должен быть не больше нижележащего.
//N <= 200.

#include <cassert>
#include <iostream>

using namespace std;

long GetAmount(long N)
{
	N++;
	long **A = new long*[N];
	assert(A != NULL);

	for (long i = 0; i < N; i++)
	{
		A[i] = new long[N];
		assert(A[i] != NULL);

		for (long j = 0; j < N; j++)
		{
			A[i][j] = 0;
		}
		A[i][1] = 1;
		A[i][i] = 1;
	}

	// i: amount of blocks
	// j: amount of blocks in lowest lvl

	for (long i = 3; i < N; i++) // fields before are already filled
	{
		for (long j = 2; j < i; j++)
		{
			
			for (long k = 1; k <= j; k++)
			{
				if (k > i - j)
				{
					break;
				}
				A[i][j] += A[i - j][k];
			}
		}
	}

	long amount = 0;
	for (long i = 1; i < N; i++)
	{
		amount += A[N-1][i];
	}

	return amount;
}

int main()
{
	long N = 0;
	cin >> N;
	assert(N >= 0);

	long res = GetAmount(N);	
	assert(res >= 0);

	cout << res;
    return 0;
}
