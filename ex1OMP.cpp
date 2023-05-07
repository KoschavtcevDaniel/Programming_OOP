#include <omp.h>
#include <iostream>
#include <stdlib.h> 
#include <time.h>
using namespace std;

int main()
{
	setlocale(LC_ALL, "Russian");
	int s1 = 0, s2 = 0, s3 = 0;
	const double e = 0.0001; //область сходимости
	const int MAX_N = 50; // максимально-допустимая размерность матрицы
	const int MIN_VALUE = -50; // минимальное значение элементов матрицы 
	const int MAX_VALUE = 50; // максимальное значение
	float A[MAX_N][MAX_N]; // исходная матрица
	float b[MAX_N]; //вектор
	double x[MAX_N][MAX_N];
	int n; // текущий размер матрицы n*n
	srand(time(NULL));

	/*
	n = MIN_VALUE + rand() % (MAX_VALUE - MIN_VALUE + 1);

	while ((n <= 1) || (n > MAX_N))
	{
		n = MIN_VALUE + rand() % (MAX_VALUE - MIN_VALUE + 1);
	}

	//генерация массива
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= n; j++)
		{
			// взять случайное число
			A[i][j] = MIN_VALUE + rand() % (MAX_VALUE - MIN_VALUE + 1);
		}

	//генерация вектора
	for (int i = 1; i <= n; i++)
	{
		// взять случайное число
		b[i] = MIN_VALUE + rand() % (MAX_VALUE - MIN_VALUE + 1);
	}
	
	//начальное условие для вектора решений
	for (int i = 1; i <= n; i++)
		for (int j = 0; j <= n; j++)
			{
				x[i][j] = 0;
			}
	*/

	cout << "Input n" << endl;
	cin >> n;

	while ((n <= 1) || (n > MAX_N))
	{
		cout << "Try again" << endl;
		cin >> n;
	}

	cout << "Mass A" << endl;
	//генерация массива    
	for (int i = 1; i <= n; i++)
	{

		for (int j = 1; j <= n; j++)
		{
			cin >> A[i][j];
		}

	}
	//генерация вектора
	cout << endl;
	cout << "b" << endl;
	for (int i = 1; i <= n; i++)
	{
		cin >> b[i];
	}

	//начальное условие для вектора решений
	for (int i = 0; i <= n; i++)
		for (int j = 1; j <= n; j++)
		{
			x[j][i] = 0;
		}

	double t1 = omp_get_wtime();
	int k = -1, f = 1, fl = 0, c = 0;
	double s = 0.0;

#pragma omp parallel num_threads(4) shared(A, b, x, e, n, k) reduction(+: s)
	{
		
		for (int i = 1; i <= n; i++)
		{
			s = 0.0;
			#pragma omp for schedule(static, 1)
			for (int j = 1; j <= n; j++)
			{
				if (i != j)
					s += abs(A[i][j]);
			}
			
			if (abs(A[i][i]) <= s)
				f = 0;
		}
		#pragma omp barrier
		if (f)
		{

			for (int i = 1; i <= MAX_N; i++)
			{
				for (int l = 1; l <= n; l++)
				{
					s = 0.0;
					
					for (int j = 1; j <= n; j++)
					{
						if (l == j) continue;
						s += double(A[l][j] * x[l][i - 1]);
					}
					x[l][i] = double((b[l] - s) / A[l][l]);
				}
			}
			#pragma omp barrier
			#pragma omp single
			for (int i = 1; i <= MAX_N; i++)
			{
				fl = 1;
				
				for (int j = 1; j <= n; j++)
				{
					if (abs(x[j][i] - x[j][i - 1]) >= e)
					{
						fl = 0;

					}
				}
			
				if (fl)
				{
					k = i;
					break;
				}
			}
			#pragma omp single
			if (k > -1)
				for (int i = 1; i <= n; i++)
				{
					cout << x[i][k] << " ";
				}
			else
				cout << "Not found" << endl;
		}
		else
			cout << "not true" << endl;
	}
	double t2 = omp_get_wtime();
	cout << "Time is " << t2 - t1 << endl;
	return 0;
}



