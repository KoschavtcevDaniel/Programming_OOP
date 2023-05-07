#include <iostream>
#include <stdlib.h> // нужен для вызова функции rand(), srand()
#include <time.h> // нужен для вызова функции time()
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
    clock_t tStart = clock();

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

    int k = -1, f = 1, fl = 0, c = 0;
    double s = 0.0;
    // 7. Вывод результата
    for (int i = 1; i <= n; i++)
    {
        s = 0.0;
        for (int j = 1; j <= n; j++)
        {
            if (i != j)
                s += abs(A[i][j]);
        }
        if (abs(A[i][i]) <= s)
            f = 0;
    }
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

            for (int i = 1; i <= MAX_N; i++)
            {
                fl = 1;
                for (int j = 1; j <= n; j++)
                {
                    if (abs(x[j][i] - x[j][i - 1]) >= e)
                    {
                        fl = 0;
            
                    }
                    cout << abs(x[j][i] - x[j][i - 1]) << endl;
                }
                if (fl)
                {
                    k = i;
                    break;
                }
            }
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
    printf("Time taken: %.2fs\n", (double)(clock() - tStart) / CLOCKS_PER_SEC);
    return 0;
}
