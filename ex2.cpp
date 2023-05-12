#include <iostream>
using namespace std;

int main()
{
    setlocale(LC_ALL, "Russian");
    int w_size, rank, ibeg, iend, k;

    const int MAX_N = 8; // максимально-допустимая размерность матрицы
    const int MIN_VALUE = -50; // минимальное значение элементов матрицы 
    const int MAX_VALUE = 50; // максимальное значение
    double a[MAX_N][MAX_N]; // исходная матрица
    double b[MAX_N][MAX_N];
    int n; // текущий размер матрицы n*n
    srand(time(NULL));

    n = MIN_VALUE + rand() % (MAX_VALUE - MIN_VALUE + 1);

    while ((n <= 1) || (n > MAX_N))
    {
        n = MIN_VALUE + rand() % (MAX_VALUE - MIN_VALUE + 1);
    }

        //генерация массива
    for (int k = 0; k < n; k++)
    {
        for (int l = 0; l < n; l++)
        {
            // взять случайное число
            a[k][l] = double(MIN_VALUE + rand() % (MAX_VALUE - MIN_VALUE + 1));
            
            cout << a[k][l] << " ";
        }
        cout << endl;
    }


    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            float x = 0;
            if (i - 1 < 0 || i + 1 > n - 1 || j - 1 < 0 || j + 1 > n - 1)
            {
                b[i][j] = a[i][j];
            }
            else
            {
                b[i][j] = (a[i][j - 1] + a[i][j + 1]) / 2;
            }
        }
    }
    cout << endl;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            cout << b[i][j] << " ";
        }
        cout << endl;
    }
    return 0;
}

