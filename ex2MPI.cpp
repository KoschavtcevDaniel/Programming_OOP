#include "mpi.h"
#include <stdio.h>
#include <vector>
#include <iostream>
using namespace std;

int main(int argc, char** argv)
{
	cout << "0" << endl;
	setlocale(LC_ALL, "Russian");
	int w_size, rank, ibeg, iend, k;
	MPI_Status stats;
	double startwtime = 0.0, endwtime;

	const int MAX_N = 10; // максимально-допустимая размерность матрицы
	const int MIN_VALUE = -50; // минимальное значение элементов матрицы 
	const int MAX_VALUE = 50; // максимальное значение

	int n; // текущий размер матрицы n*n
	srand(time(NULL));
	cout << "1" << endl;


	MPI_Init(&argc, &argv);
	MPI_Comm_size(MPI_COMM_WORLD, &w_size);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);

	n = MIN_VALUE + rand() % (MAX_VALUE - MIN_VALUE + 1);
	vector<vector<float>> a(n, vector<float>(n));
	vector<vector<float>> b(n, vector<float>(n));

	cout << "2" << endl;
	if (rank == 0)
	{
		cout << "3" << endl;
		while ((n <= 1) || (n > MAX_N))
		{
			n = MIN_VALUE + rand() % (MAX_VALUE - MIN_VALUE + 1);
		}

		//генерация массива
		for (int i = 0; i < n; i++)
		{
			for (int j = 0; j < n; j++)
			{
				// взять случайное число
				a[i][j] = (MIN_VALUE + rand() % (MAX_VALUE - MIN_VALUE + 1));
				cout << a[i][j];
			}
			cout << endl;
		}
		cout << "4" << endl;
	}

	if (w_size > n * n) w_size = n * n;

	MPI_Bcast(&a, n * n, MPI_FLOAT, 0, MPI_COMM_WORLD);
	cout << "5" << endl;
	k = n / w_size;
	ibeg = k * rank;
	iend = k * (rank + 1);

	if (rank == w_size - 1)
		iend = n;

	startwtime = MPI_Wtime();
	for (int i = 0; i < n; i++)
	{
		for (int j = ibeg; j < iend; j++)
		{
			if (i - 1 < 0 || i + 1 > n - 1 || j - 1 < 0 || j + 1 > n - 1)
			{
				b[i][j] = a[i][j];
			}
			else
			{
				b[i][j] = (a[i][j - 1] + a[i][j + 1]) / 2;
			}
		}
		cout << "6" << endl;
	}
	if (rank == 0)
	{
		for (int i = 0; i < n; i++)
		{
			for (int j = 0; j < n; j++)
			{
				cout << b[i][j] << " ";
			}
			cout << endl;
		}
		cout << "7" << endl;
	}
	endwtime = MPI_Wtime();
	cout << "time is" << endwtime - startwtime << endl;
	MPI_Finalize();
	return 0;
}
